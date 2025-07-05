#include "imageuploader.h"
#include <QBuffer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QThread>
#include <QEventLoop>
#include <QTimer>

ImageUploader::ImageUploader(SerialComm *serial,
                             const QString &serverHost,
                             const QString &serverPort,
                             const QString &ssid,
                             const QString &password,
                             QObject *parent)
    : QObject(parent)
    , m_serial(serial)
    , m_serverHost(serverHost)
    , m_serverPort(serverPort)
    , m_ssid(ssid)
    , m_password(password)
    , m_responseBuffer(new QByteArray)
{
    if (!m_serial) {
        qDebug() << "[Uploader] Error: SerialComm pointer is null";
        emit errorOccurred(tr("串口对象未初始化"));
        return;
    }
    connectSignals();
}

ImageUploader::~ImageUploader()
{
    delete m_responseBuffer;
}

bool ImageUploader::ensureConnection()
{
    if (!m_serial || !m_serial->isOpen()) {
        emit errorOccurred(tr("串口未打开或未初始化"));
        return false;
    }

    // 退出透传
    m_serial->send("+++", 3);
    QThread::msleep(1500);

    QByteArray atResp;
    bool got = false;
    QEventLoop loop;
    QTimer timeout;
    timeout.setSingleShot(true);
    connect(&timeout, &QTimer::timeout, &loop, &QEventLoop::quit);
    auto catcher = connect(m_serial, &SerialComm::lineReceived, this,
                           [&](const QByteArray &data) {
                               atResp += data;
                               got = true;
                               loop.quit();
                           });

    // 测试AT
    for (int i = 0; i < 3; ++i) {
        atResp.clear(); got = false;
        m_serial->send("AT\r\n", 4);
        timeout.start(1500);
        loop.exec();
        if (got && atResp.contains("OK")) {
            qDebug() << "[Uploader] AT响应正常";
            break;
        }
        QThread::msleep(500);
    }
    if (!got || !atResp.contains("OK")) {
        disconnect(catcher);
        emit errorOccurred(tr("AT命令无响应"));
        return false;
    }

    // 设置为 STA 模式
    atResp.clear(); got = false;
    m_serial->send("AT+CWMODE=1\r\n", 14);
    timeout.start(1000); loop.exec();
    if (!got || !atResp.contains("OK")) {
        disconnect(catcher);
        emit errorOccurred(tr("设置为STA模式失败"));
        return false;
    }

    // 连接 WiFi
    atResp.clear(); got = false;
    QString wifiCmd = QString("AT+CWJAP=\"%1\",\"%2\"\r\n")
                      .arg(m_ssid)
                      .arg(m_password);
    m_serial->send(wifiCmd.toUtf8().constData(), wifiCmd.length());
    timeout.start(8000); loop.exec();
    if (!got || !(atResp.contains("WIFI GOT IP") || atResp.contains("OK"))) {
        disconnect(catcher);
        emit errorOccurred(tr("连接Wi-Fi失败"));
        return false;
    }

    // 启动 TCP 连接
    atResp.clear(); got = false;
    QByteArray cmd = QString("AT+CIPSTART=\"TCP\",\"%1\",%2\r\n")
                     .arg(m_serverHost)
                     .arg(m_serverPort)
                     .toUtf8();
    m_serial->send(cmd.constData(), cmd.size());
    timeout.start(3000); loop.exec();
    disconnect(catcher);
    if (!got || (!atResp.contains("OK") && !atResp.contains("ALREADY CONNECT"))) {
        emit errorOccurred(tr("连接服务器失败"));
        return false;
    }

    // 启用透传
    m_serial->send("AT+CIPMODE=1\r\n", 16);
    QThread::msleep(300);
    m_serial->send("AT+CIPSEND\r\n", 14);
    QThread::msleep(300);

    return true;
}

void ImageUploader::checkNetworkAndUpload(const QImage &image)
{
    if (!ensureConnection()) return;
    if (!uploadImage(image)) emit errorOccurred(tr("图像上传失败"));
}

bool ImageUploader::uploadImage(const QImage &image)
{
    if (!m_serial || !m_serial->isOpen()) return false;
    if (image.isNull()) return false;

    QByteArray imageData;
    QBuffer buf(&imageData);
    buf.open(QIODevice::WriteOnly);
    image.save(&buf, "JPG", 50);

    QString boundary = "----WebKitFormBoundaryQtEsp8266";
    QByteArray body;
    body.append("--" + boundary.toUtf8() + "\r\n");
    body.append("Content-Disposition: form-data; name=\"image\"; filename=\"image.jpg\"\r\n");
    body.append("Content-Type: image/jpeg\r\n\r\n");
    body.append(imageData);
    body.append("\r\n--" + boundary.toUtf8() + "--\r\n");

    QByteArray httpReq;
    httpReq.append("POST /upload HTTP/1.1\r\n");
    httpReq.append("Host: " + m_serverHost.toUtf8() + ":" + m_serverPort.toUtf8() + "\r\n");
    httpReq.append("Content-Type: multipart/form-data; boundary=" + boundary.toUtf8() + "\r\n");
    httpReq.append("Content-Length: " + QByteArray::number(body.size()) + "\r\n\r\n");
    httpReq.append(body);

    int chunkSize = 512;
    int totalSize = httpReq.size();
    int sent = 0;
    while (sent < totalSize) {
        int len = qMin(chunkSize, totalSize - sent);
        int written = m_serial->send(httpReq.constData() + sent, len);
        if (written != len) {
            emit errorOccurred(tr("写入失败: %1/%2").arg(written).arg(len));
            return false;
        }
        sent += written;
        QThread::msleep(10);
    }
    return true;
}

void ImageUploader::connectSignals()
{
    connect(m_serial, &SerialComm::lineReceived, this, [this](const QByteArray &data) {
        m_responseBuffer->append(data);
        if (m_responseBuffer->contains("HTTP/1.1 200 OK")) {
            qDebug() << "[Uploader] 收到服务器响应: OK";
        }
    });
    connect(m_serial, &SerialComm::errorOccurred, this, &ImageUploader::errorOccurred);
}
