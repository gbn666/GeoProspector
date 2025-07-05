#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "netconfigwidget.h"
#include "visualizer.h"
#include <QMessageBox>
#include <QPixmap>
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , camThread(nullptr)
    , dhtThread(nullptr)
    , m_serverHost()
    , m_serverPort()
    , m_serial(new SerialComm(this))
{
    ui->setupUi(this);

    // 检查 m_serial 是否成功初始化
    if (!m_serial) {
        qDebug() << "[MainWindow] Error: Failed to initialize SerialComm";
        QMessageBox::critical(this, tr("错误"), tr("串口初始化失败"));
    }

    // 摄像头线程
    camThread = new cameraThread(this);
    connect(camThread, &cameraThread::imageReady,
            this, &MainWindow::displayFrame);
    camThread->start();

    // DHT11线程
    dhtThread = new DHT11Thread(this);
    connect(dhtThread, &DHT11Thread::newTempHum,
            this, &MainWindow::updateDHT11Display);
    connect(dhtThread, &QThread::finished,
            dhtThread, &QObject::deleteLater);
    dhtThread->start();

    // 初始UI
    ui->label_5->setText("0.0℃，0.0%");
    ui->label_6->setText("正常");
    ui->label_3->setText("0.0cm");
    ui->label_4->setText("0.0lux");
}

MainWindow::~MainWindow()
{
//    if (camThread) {
//        camThread->stop(); // 调用 stop 方法
//        camThread->wait();
//        delete camThread;
//    }
//    if (dhtThread) {
//        dhtThread->quit();
//        dhtThread->wait();
//    }
//    if (m_serial) {
//        if (m_serial->isOpen()) {
//            m_serial->close();
//        }
//        delete m_serial;
//    }
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
        qDebug() << "[MainWindow] Error: Received null image from cameraThread";
        return;
    }
    m_lastFrame = img.copy(); // 深拷贝，确保图像有效
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
    auto thGas = new DataProcessThread(BroadGas, this);
    auto thLight = new DataProcessThread(LightLevel, this);
    auto thUltra = new DataProcessThread(Ultrasonic, this);
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
    ui->label_3->setText(
        QString::number(dist, 'f', 1) + " cm");
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
            this, [this, w](){
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
    qDebug() << "[MainWindow] Server configured: " << host << ":" << port;
    QMessageBox::information(this, tr("提示"),
                             tr("服务器已设置为 %1:%2")
                             .arg(host).arg(port));
}

void MainWindow::on_recognitionButton_clicked()
{
    // 1. 检查串口对象是否初始化
    if (!m_serial) {
        qDebug() << "[MainWindow] Error: m_serial is null";
        QMessageBox::critical(this, tr("错误"), tr("串口对象未初始化"));
        return;
    }

    // 2. 检查图像有效性
    if (m_lastFrame.isNull()) {
        qDebug() << "[MainWindow] Error: m_lastFrame is null";
        QMessageBox::warning(this, tr("警告"), tr("尚未获取到图像帧"));
        return;
    }

    // 3. 检查服务器配置
    if (m_serverHost.isEmpty() || m_serverPort.isEmpty()) {
        qDebug() << "[MainWindow] Error: Server host or port is empty";
        QMessageBox::warning(this, tr("警告"), tr("请先通过 WiFi 设置配置服务器"));
        return;
    }

    // 4. 确保串口已打开
    if (!m_serial->isOpen()) {
        qDebug() << "[MainWindow] Opening serial port /dev/ttymxc1 at 115200";
        if (!m_serial->openPort("/dev/ttymxc1", 115200)) {
            qDebug() << "[MainWindow] Error: Failed to open serial port";
            QMessageBox::critical(this, tr("错误"), tr("打开串口失败"));
            return;
        }
    }

    // 5. 创建 ImageUploader
    m_ssid="MONSTER";
    m_password="12345678";
    ImageUploader *uploader = new ImageUploader(m_serial, m_serverHost, m_serverPort, m_ssid, m_password, this);

    connect(uploader, &ImageUploader::recognitionResult, this, [this](const QString &res) {
        qDebug() << "[MainWindow] Recognition result: " << res;
        QMessageBox::information(this, tr("识别结果"), tr("识别结果: %1").arg(res));
    });
    connect(uploader, &ImageUploader::errorOccurred, this, [this](const QString &err) {
        qDebug() << "[MainWindow] Error occurred: " << err;
        QMessageBox::critical(this, tr("错误"), err);
    });

    // 6. 检查网络连接并发起上传
    qDebug() << "[MainWindow] Starting network check and upload";
    uploader->checkNetworkAndUpload(m_lastFrame);

    // 7. 延迟删除 uploader
    uploader->deleteLater();
}
