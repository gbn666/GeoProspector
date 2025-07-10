// MainWindow.cpp

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "netconfigwidget.h"
#include "visualizer.h"
#include "imageuploader.h"
#include "serialcomm.h"

#include <QMessageBox>
#include <QPixmap>
#include <QThread>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtConcurrent/QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , camThread(nullptr)
    , dhtThread(nullptr)
    , m_serial(new SerialComm(this))
{
    ui->setupUi(this);

    // 检查串口对象
    if (!m_serial) {
        qDebug() << "[MainWindow] Error: SerialComm 初始化失败";
        QMessageBox::critical(this, tr("错误"), tr("串口初始化失败"));
    }

    // 启动摄像头线程
    camThread = new cameraThread(this);
    connect(camThread, &cameraThread::imageReady,
            this, &MainWindow::displayFrame);
    camThread->start();

    // 启动 DHT11 温湿度线程
    dhtThread = new DHT11Thread(this);
    connect(dhtThread, &DHT11Thread::newTempHum,
            this, &MainWindow::updateDHT11Display);
    connect(dhtThread, &QThread::finished,
            dhtThread, &QObject::deleteLater);
    dhtThread->start();

    // 初始 UI 状态
    ui->label_5->setText("0.0℃，0.0%");
    ui->label_6->setText("正常");
    ui->label_3->setText("0.0cm");
    ui->label_4->setText("0.0lux");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDHT11Display(const QString &tempInt,
                                    const QString &tempFrac,
                                    const QString &humidity)
{
    ui->label_5->setText(
        QStringLiteral("温度: %1.%2℃  湿度: %3%")
            .arg(tempInt).arg(tempFrac).arg(humidity));
}

void MainWindow::onTempHumDetected(float temperature, float humidity)
{
    int ti = int(temperature);
    int tf = int((temperature - ti) * 10);
    ui->label_5->setText(
        QStringLiteral("温度: %1.%2℃  湿度: %3%")
            .arg(ti).arg(tf).arg(int(humidity)));
}

void MainWindow::displayFrame(const QImage &img)
{
    if (img.isNull()) {
        qDebug() << "[MainWindow] Error: 接收到空图像";
        return;
    }
    m_lastFrame = img.copy();
    ui->viewlabel->setPixmap(
        QPixmap::fromImage(
            m_lastFrame.scaled(ui->viewlabel->size(),
                               Qt::KeepAspectRatio,
                               Qt::SmoothTransformation)));
}

void MainWindow::on_viewButton_clicked()
{
    hide();
    visualizer *vis = new visualizer(nullptr);
    vis->setAttribute(Qt::WA_DeleteOnClose);
    connect(vis, &visualizer::returnToMainWindow, this, [this, vis]() {
        vis->close();
        show();
        camThread->startCapture();
    });
    vis->show();
}

void MainWindow::on_startButton_clicked()
{
    camThread->startCapture();
    auto thGas     = new DataProcessThread(BroadGas, this);
    auto thLight   = new DataProcessThread(LightLevel, this);
    auto thUltra   = new DataProcessThread(Ultrasonic, this);
    auto thTempHum = new DataProcessThread(TempHumidity, this);

    connect(thGas, &DataProcessThread::gasWarning,
            this, &MainWindow::onGasUpdate);
    connect(thLight, &DataProcessThread::lightDetected,
            this, &MainWindow::onLightDetected);
    connect(thUltra, &DataProcessThread::distanceWarning,
            this, &MainWindow::onDistanceUpdate);
    connect(thTempHum, &DataProcessThread::tempHumDetected,
            this, &MainWindow::onTempHumDetected);
}

void MainWindow::onGasUpdate(int gasValue)
{
    QString status = (gasValue == 0 ? "正常" : "异常");
    QString color  = (gasValue == 0 ? "green" : "red");
    WarningGas(gasValue);
    ui->label_6->setStyleSheet(
        QString("QLabel{color:%1;}").arg(color));
    ui->label_6->setText(status);
}

void MainWindow::onDistanceUpdate(float dist)
{
    ui->label_3->setText(QString::number(dist, 'f', 1) + " cm");
}

void MainWindow::onLightDetected(const QString &info)
{
    ui->label_4->setText(info + " lux");
}

void MainWindow::on_saveButton_clicked()
{
    QMessageBox::information(this, tr("提示"), tr("保存成功"));
}

void MainWindow::on_wifiButton_clicked()
{
    auto *w = new NetConfigWidget;
    w->setAttribute(Qt::WA_DeleteOnClose);
    connect(w, &NetConfigWidget::serverConfigured,
            this, &MainWindow::onServerConfigured);
    connect(w, &NetConfigWidget::returnToMainWindow,
            this, [this, w]() {
        w->close();
        show();
        camThread->startCapture();
    });
    hide();
    w->show();
}

void MainWindow::onServerConfigured(const QString &host,
                                    const QString &port)
{
    m_serverHost = host;
    m_serverPort = port;
    qDebug() << "[MainWindow] 服务器已设置为" << host << ":" << port;
    QMessageBox::information(this, tr("提示"),
                             tr("服务器已设置为 %1:%2")
                             .arg(host).arg(port));
}

void MainWindow::on_recognitionButton_clicked()
{
    // 1. 基础校验
    if (!m_serial) {
        QMessageBox::critical(this, tr("错误"), tr("串口对象未初始化"));
        return;
    }
    if (m_lastFrame.isNull()) {
        QMessageBox::warning(this, tr("警告"), tr("尚未获取到图像帧"));
        return;
    }
    if (m_serverHost.isEmpty() || m_serverPort.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请先通过 WiFi 设置服务器"));
        return;
    }

    // 2. 打开串口（如尚未打开）
    if (!m_serial->isOpen()) {
        if (!m_serial->openPort("/dev/ttymxc1", 115200)) {
            QMessageBox::critical(this, tr("错误"), tr("打开串口失败"));
            return;
        }
    }

    // 3. 创建 uploader 并连接信号
    auto *uploader = new ImageUploader(
        m_serial,
        m_serverHost,
        m_serverPort,
        QStringLiteral("MONSTER"),
        QStringLiteral("12345678"),
        this
    );

    connect(uploader, &ImageUploader::recognitionResult,
            this, [this, uploader](const QString &jsonStr) {
        // 解析 JSON 并显示
        QJsonParseError err;
        auto doc = QJsonDocument::fromJson(jsonStr.toUtf8(), &err);
        if (err.error != QJsonParseError::NoError) {
            QMessageBox::critical(this, tr("错误"),
                                  tr("解析识别结果失败: %1").arg(err.errorString()));
        } else {
            auto obj = doc.object();
            auto arr = obj.value("results").toArray();
            QString msg = tr("识别结果：\n");
            for (const auto &v : arr) {
                auto itm = v.toObject();
                QString lbl = itm.value("label").toString();
                double  cf  = itm.value("confidence").toDouble();
                msg += QStringLiteral("  • %1 （%2%）\n")
                           .arg(lbl)
                           .arg(cf * 100, 0, 'f', 2);
            }
            QMessageBox::information(this, tr("识别完成"), msg);
        }
        uploader->deleteLater();
    }, Qt::QueuedConnection);

    connect(uploader, &ImageUploader::errorOccurred,
            this, [this, uploader](const QString &err) {
        QMessageBox::critical(this, tr("错误"), err);
        uploader->deleteLater();
    }, Qt::QueuedConnection);

    // 4. 异步执行上传和识别
    QtConcurrent::run([uploader, this]() {
        uploader->checkNetworkAndUpload(m_lastFrame);
    });
}

