#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->viewButton->setText("可视化");
    ui->viewlabel->setText("相机画面");

    camThread = new cameraThread(this);
    connect(camThread, SIGNAL(Collect_complete(unsigned char*)),
            this, SLOT(displayFrame(unsigned char*)));

    ui->label_5->setText("0.0℃，0.0%");
    ui->label_6->setText("正常");
    ui->label_3->setText("0.0cm");
    ui->label_4->setText("0.0lux");

    dhtThread = new DHT11Thread(this);
    connect(dhtThread, &DHT11Thread::finished, dhtThread, &DHT11Thread::deleteLater);
    connect(this, &MainWindow::updateDHT11Display, this, &MainWindow::onTempHumUpdate);
    dhtThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::DHT11Thread::DHT11Thread(MainWindow *parent)
    : QThread(parent), m_parent(parent)
{
}

void MainWindow::DHT11Thread::run()
{
    int fd = open("/dev/DHT11", O_RDWR);
    if(fd == -1) {
        qDebug() << "DHT11 open failed:" << strerror(errno);
        return;
    }

    unsigned char buf[6];
    unsigned char trigger = 1;

    while(!isInterruptionRequested()) {
        write(fd, &trigger, 1);
        int bytesRead = read(fd, buf, sizeof(buf));

        if(bytesRead == sizeof(buf)) {
            emit m_parent->updateDHT11Display(buf[2], buf[3], buf[0]);
        }

        msleep(2000);
    }

    ::close(fd);
}

void MainWindow::updateDHT11Display(int tempInt, int tempFrac, int humidity)
{
    QString text = QString("温度: %1.%2℃  湿度: %3%")
                  .arg(tempInt)
                  .arg(tempFrac)
                  .arg(humidity);
    ui->label_5->setText(text);
}

void MainWindow::displayFrame(unsigned char *buffer)
{
    QImage img(buffer, 640, 480, 640*3, QImage::Format_RGB888);
    ui->viewlabel->setPixmap(QPixmap::fromImage(img.scaled(480, 360, Qt::KeepAspectRatio)));
}

void MainWindow::onFrameReady(unsigned char *rgbBuffer)
{
    QImage img(rgbBuffer, 480, 360, 480 * 3, QImage::Format_RGB888);
    ui->viewlabel->setScaledContents(false);
    ui->viewlabel->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_viewButton_clicked()
{
    this->hide();
    visualizer *vis = new visualizer(nullptr);
    vis->setAttribute(Qt::WA_DeleteOnClose);
    connect(vis, &visualizer::returnToMainWindow, this, [this, vis]() {
        vis->close();
        this->show();
        camThread->startCapture();
    });
    vis->show();
}

void MainWindow::on_startButton_clicked()
{
    camThread->startCapture();
    camThread->start();

    DataProcessThread *thGas     = new DataProcessThread(BroadGas, nullptr);
    DataProcessThread *thLight   = new DataProcessThread(LightLevel, nullptr);
    DataProcessThread *thUltra   = new DataProcessThread(Ultrasonic, nullptr);
    DataProcessThread *thLed     = new DataProcessThread(LEDBuzzer, nullptr);

    connect(thGas, SIGNAL(gasWarning(int)), this, SLOT(onGasUpdate(int)));
    thGas->start();

    connect(thLight, SIGNAL(lightDetected(QString)), this, SLOT(onLightDetected(QString)));
    thLight->start();

    connect(thUltra, SIGNAL(distanceWarning(float)), this, SLOT(onDistanceUpdate(float)));
    thUltra->start();

    connect(thLed, SIGNAL(ledBuzzerTriggered()), this, SLOT(onLedTriggered()));
    thLed->start();
    ui->label_5->setText("27.8°C, 48%");
}

void MainWindow::onGasUpdate(int gasValue)
{
    QString status = (gasValue == 0) ? "正常" : "异常";
    QString color = (gasValue == 0) ? "green" : "red";
    const char *LEDBUZZER_DEV  = "/dev/LEDBuzzer";
    int fd = ::open(LEDBUZZER_DEV, 0);
    if(gasValue!=0)
    {

        ioctl(fd,0);
        ioctl(fd,4);

    }
    else{
        ioctl(fd,1);
        ioctl(fd,3);
    }
    ui->label_6->setStyleSheet("QLabel { color : " + color + "; }");
    ui->label_6->setText(status);
}

void MainWindow::onDistanceUpdate(float dist)
{
    ui->label_3->setText(QString::number(dist) + " cm");
}

void MainWindow::onLightUpdate(int lightVal)
{
    ui->label_4->setText(QString::number(lightVal) + "lux");
}

void MainWindow::onLedTriggered()
{
    // 目前无UI操作，预留接口
}

void MainWindow::onTempHumUpdate(float temperature, float humidity)
{
    ui->label_5->setText(
        QString("%1 °C, %2 %")
          .arg(temperature, 0, 'f', 1)
          .arg(humidity,    0, 'f', 1)
    );
}

void MainWindow::onLightDetected(const QString &info)
{
    ui->label_4->setText(info+"lux");
}
