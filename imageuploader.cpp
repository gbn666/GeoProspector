#include "imageuploader.h"
#include "serialcomm.h"
#include <QBuffer>
#include <QThread>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>

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

    // 1. 退出透传
    m_serial->send("+++", 3);
    QThread::msleep(1500);

    // 通用事件循环和超时器
    QEventLoop loop;
    QTimer     timeout;
    timeout.setSingleShot(true);
    connect(&timeout, &QTimer::timeout, &loop, &QEventLoop::quit);

    // 捕获关键回复
    auto catcher = connect(m_serial, &SerialComm::lineReceived,
        this, [&](const QByteArray &data) {
            *m_responseBuffer += data;
            if (m_responseBuffer->contains("OK") ||
                m_responseBuffer->contains("FAIL") ||
                m_responseBuffer->contains("WIFI GOT IP") ||
                m_responseBuffer->contains("WIFI CONNECTED")) {
                loop.quit();
            }
        }
    );

    // 2. AT 测试
    bool ok = false;
    for (int i = 0; i < 3; ++i) {
        m_responseBuffer->clear();
        m_serial->send("AT\r\n", 4);
        timeout.start(1500);
        loop.exec();
        if (m_responseBuffer->contains("OK")) {
            ok = true;
            break;
        }
        QThread::msleep(500);
    }
    if (!ok) {
        disconnect(catcher);
        emit errorOccurred(tr("AT 命令无响应"));
        return false;
    }

    // 3. 设置 STA 模式
    m_responseBuffer->clear();
    m_serial->send("AT+CWMODE=1\r\n", 14);
    timeout.start(1500);
    loop.exec();
    if (!m_responseBuffer->contains("OK")) {
        disconnect(catcher);
        emit errorOccurred(tr("设置 STA 模式失败"));
        return false;
    }

    // 4. 连接 Wi-Fi
    m_responseBuffer->clear();
    QString wifiCmd = QString("AT+CWJAP=\"%1\",\"%2\"\r\n")
                      .arg(m_ssid).arg(m_password);
    m_serial->send(wifiCmd.toUtf8().constData(), wifiCmd.length());
    timeout.start(10000);
    loop.exec();
    if (!(m_responseBuffer->contains("WIFI CONNECTED") ||
          m_responseBuffer->contains("WIFI GOT IP") ||
          m_responseBuffer->contains("OK"))) {
        disconnect(catcher);
        emit errorOccurred(tr("连接 Wi‑Fi 失败"));
        return false;
    }

    // 5. 建立 TCP 连接
    m_responseBuffer->clear();
    QByteArray startCmd = QString("AT+CIPSTART=\"TCP\",\"%1\",%2\r\n")
                          .arg(m_serverHost).arg(m_serverPort)
                          .toUtf8();
    m_serial->send(startCmd.constData(), startCmd.size());
    timeout.start(5000);
    loop.exec();
    if (!(m_responseBuffer->contains("OK") ||
          m_responseBuffer->contains("ALREADY CONNECT"))) {
        disconnect(catcher);
        emit errorOccurred(tr("连接服务器失败"));
        return false;
    }

    // 6. 进入透传模式
    m_serial->send("AT+CIPMODE=1\r\n", 16);
    QThread::msleep(300);
    m_serial->send("AT+CIPSEND\r\n", 12);
    QThread::msleep(300);

    disconnect(catcher);
    return true;
}

void ImageUploader::checkNetworkAndUpload(const QImage &image)
{
    if (!ensureConnection()) return;
    if (!uploadImage(image)) {
        emit errorOccurred(tr("图像上传失败"));
    }
}

bool ImageUploader::uploadImage(const QImage &image)
{
    if (!m_serial || !m_serial->isOpen() || image.isNull())
        return false;

    // 压缩 JPEG
    QByteArray imageData;
    QBuffer buf(&imageData);
    buf.open(QIODevice::WriteOnly);
    image.save(&buf, "JPG", 50);

    // 构造 multipart body
    QString boundary = "----WebKitFormBoundaryQtEsp8266";
    QByteArray body;
    body.append("--" + boundary.toUtf8() + "\r\n");
    body.append("Content-Disposition: form-data; name=\"image\"; filename=\"image.jpg\"\r\n");
    body.append("Content-Type: image/jpeg\r\n\r\n");
    body.append(imageData);
    body.append("\r\n--" + boundary.toUtf8() + "--\r\n");

    // 构造 HTTP 请求
    QByteArray httpReq;
    httpReq.append("POST /upload HTTP/1.1\r\n");
    httpReq.append("Host: " + m_serverHost.toUtf8() + ":" + m_serverPort.toUtf8() + "\r\n");
    httpReq.append("Content-Type: multipart/form-data; boundary=" + boundary.toUtf8() + "\r\n");
    httpReq.append("Content-Length: " + QByteArray::number(body.size()) + "\r\n\r\n");
    httpReq.append(body);

    // 分块并可重试发送
    const int  chunkSize = 256;
    const char* data      = httpReq.constData();
    int         total     = httpReq.size();
    int         sent      = 0;

    while (sent < total) {
        int remain = total - sent;
        int len    = qMin(chunkSize, remain);
        int offset = 0;
        int retry  = 0;
        const int maxRetry = 5;

        while (offset < len) {
            int written = m_serial->send(data + sent + offset, len - offset);
            if (written > 0) {
                offset += written;
                retry = 0;
            } else if (written == 0) {
                if (++retry > maxRetry) {
                    emit errorOccurred(tr("写入超时"));
                    return false;
                }
                QThread::msleep(20);
            } else {
                emit errorOccurred(tr("写入错误"));
                return false;
            }
        }

        sent += offset;
        QThread::msleep(20);
    }

    // 等待并提取纯 JSON
    m_responseBuffer->clear();
    QEventLoop respLoop;
    QTimer     respTimeout;
    respTimeout.setSingleShot(true);
    connect(&respTimeout, &QTimer::timeout, &respLoop, &QEventLoop::quit);

    auto respConn = connect(m_serial, &SerialComm::lineReceived,
        this, [&](const QByteArray &data) {
            *m_responseBuffer += data;
            if (m_responseBuffer->contains("200 OK") &&
                m_responseBuffer->contains("\r\n\r\n"))
            {
                respLoop.quit();
            }
        }
    );

    respTimeout.start(10000);
    respLoop.exec();
    disconnect(respConn);

    // 提取第一个 { … } 之间的 JSON
    const QByteArray &bufAll = *m_responseBuffer;
    int start = bufAll.indexOf('{');
    int end   = bufAll.lastIndexOf('}');
    if (start < 0 || end < 0 || end <= start) {
        emit errorOccurred(tr("未能解析返回内容"));
        return false;
    }
    QByteArray jsonBytes = bufAll.mid(start, end - start + 1);
    emit recognitionResult(QString::fromUtf8(jsonBytes));
    return true;
}

void ImageUploader::connectSignals()
{
    connect(m_serial, &SerialComm::errorOccurred,
            this, &ImageUploader::errorOccurred);
}
