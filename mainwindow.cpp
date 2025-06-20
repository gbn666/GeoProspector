#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "camera.h"
#include "camerathread.h"
#include "visualizer.h"
#include "ui_visualizer.h"
#include "dataprocess.h"
#include "dataprocessthread.h"
#include <QLabel>
#include <QThread>
#include <QDebug>


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
    ui->label_5->setText("0.0摄氏度，0.0RH");
    ui->label_6->setText("正常");
    ui->label_3->setText("0.0cm");
    ui->label_4->setText("0.0lux");
}

MainWindow::~MainWindow()
{
    delete ui;
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

    visualizer *vis = new visualizer(nullptr); // 设为 nullptr，避免叠在主窗口上

        vis->setAttribute(Qt::WA_DeleteOnClose);    // 窗口关闭时自动删除
        connect(vis, &visualizer::returnToMainWindow, this, [this, vis]() {
            qDebug() << "收到返回信号，切换回主页面";
            vis->close();       // 隐藏 visualizer
            this->show();       // 显示主窗口
            camThread->startCapture(); // 重启相机
        });

        vis->show();
}

void MainWindow::on_startButton_clicked()
{
    camThread->startCapture();
    camThread->start();

    DataProcessThread *thTempHum = new DataProcessThread(TempHumidity, nullptr);
    DataProcessThread *thGas     = new DataProcessThread(BroadGas, nullptr);
    DataProcessThread *thLight   = new DataProcessThread(LightLevel, nullptr);
    DataProcessThread *thUltra   = new DataProcessThread(Ultrasonic, nullptr);
    DataProcessThread *thLed     = new DataProcessThread(LEDBuzzer, nullptr);

    connect(thTempHum, &DataProcessThread::tempHumDetected,
                this, &MainWindow::onTempHumUpdate);



    connect(thGas, SIGNAL(gasWarning(int)), this, SLOT(onGasUpdate(int)));
    thGas->start();

    connect(thLight, SIGNAL(lightDetected(QString)), this, SLOT(onLightDetected(QString)));
    thLight->start();

    connect(thUltra, SIGNAL(distanceWarning(float)), this, SLOT(onDistanceUpdate(float)));
    thUltra->start();

   connect(thLed, SIGNAL(ledBuzzerTriggered()), this, SLOT(onLedTriggered()));
    thLed->start();
}

void MainWindow::onGasUpdate(int gasValue) {
    QString status = (gasValue == 0) ? "正常" : "异常";
    QString color = (gasValue == 0) ? "green" : "red";
    ui->label_6->setStyleSheet("QLabel { color : " + color + "; }");
    ui->label_6->setText(status);
}

void MainWindow::onDistanceUpdate(float dist) {
    ui->label_3->setText(QString::number(dist) + " cm");
}

void MainWindow::onLightUpdate(int lightVal) {
    ui->label_4->setText(QString::number(lightVal)+"  lux");
}


void MainWindow::onLedTriggered() {
    // 目前无UI操作，预留接口
}


void MainWindow::onTempHumUpdate(float temperature, float humidity) {
    ui->label_5->setText(
        QString("%1 °C, %2 %")
          .arg(temperature, 0, 'f', 1)
          .arg(humidity,    0, 'f', 1)
    );
}



void MainWindow::onLightDetected(const QString &info) {
    ui->label_4->setText(info+" lux");
}
