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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->viewButton->setText("可视化");
    ui->viewlabel->setText("相机画面");
    camThread = new cameraThread(this);
    connect(camThread, &cameraThread::Collect_complete,
            this, &MainWindow::displayFrame);
    ui->label_5->setText("0.0摄氏度，0.0RH");
    ui->label_6->setText("正常");
    ui->label_3->setText("0.0cm");
    ui->label_4->setText("0.0lux");





}
void MainWindow::displayFrame(unsigned char *buffer)
{
    QImage img(buffer, 640, 480, 640*3, QImage::Format_RGB888);
    ui->viewlabel->setPixmap(QPixmap::fromImage(img.scaled(480, 360, Qt::KeepAspectRatio)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onFrameReady(unsigned char *rgbBuffer)
{
    // 把 cameraThread 转成 480*360 的 QImage
    QImage img(rgbBuffer,
               480,              // FRAME_WIDTH
               360,              // FRAME_HEIGHT
               480 * 3,          // bytesPerLine
               QImage::Format_RGB888);

    // 直接设置，不做 scaled()，也不用 setScaledContents(true)
    ui->viewlabel->setScaledContents(false);
    ui->viewlabel->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_viewButton_clicked()
{
    this->close();
    visualizer *ui=new visualizer;
    ui->show();






}

void MainWindow::on_startButton_clicked()
{
    camThread->startCapture();
    camThread->start();
    //加载驱动
    auto *thTempHum = new DataProcessThread(ProcessMode::TempHumidity, this);//温湿度
    auto *thGas = new DataProcessThread(ProcessMode::BroadGas, this);//广谱气体
    auto *thLight = new DataProcessThread(ProcessMode::LightLevel, this);//光照强度
    auto *thUltra = new DataProcessThread(ProcessMode::Ultrasonic, this);//超声波
    auto *thLed = new DataProcessThread(ProcessMode::LedBuzzer, this); // LED 蜂鸣器

    //温湿度槽函数
    connect(thTempHum, &DataProcessThread::tempHumDetected,
               this, [&] (const QString &info) {
           ui->label_5->setText(info); //设置温湿度数值
       });
     thTempHum->moveToThread(&thTempHum->m_thread);
     thTempHum->m_thread.start();

     //广谱气体槽函数
       connect(thGas, &DataProcessThread::gasWarning, this, &MainWindow::onGasUpdate);
       thGas->moveToThread(&thGas->m_thread);
       thGas->m_thread.start();

      //光照强度槽函数
        connect(thLight, &DataProcessThread::lightDetected,this, &MainWindow::onLightUpdate);
        thLight->moveToThread(&thLight->m_thread);
        thLight->m_thread.start();

       //超声波槽函数
        connect(thUltra, &DataProcessThread::distanceWarning,this, &MainWindow::onDistanceUpdate);
        thUltra->moveToThread(&thUltra->m_thread);
        thUltra->m_thread.start();

        //LED蜂鸣器
        connect(thLed, &DataProcessThread::ledBuzzerTriggered,this, &MainWindow::onLedTriggered);
        thLed->moveToThread(&thLed->m_thread);
        thLed->m_thread.start();



}
void MainWindow::onGasUpdate(int gasValue) {
    QString status = (gasValue == 0) ? "正常" : "异常";
    QString color = (gasValue == 0) ? "green" : "red";
    ui->label_6>setStyleSheet("QLabel { color : " + color + "; }");
    ui->label_6>setText(status);
}


void MainWindow::onDistanceUpdate(float dist) {
    ui->label_3>setText(QString::number(dist) + " cm");
}

void MainWindow::onLightUpdate(int lightVal) {
    ui->label_4>setText(QString::number(lightVal));
}

void MainWindow::onTempHumUpdate(float temp, float hum) {
    ui->label_5->setText(QString::number(temp) + " °C,"+QString::number(hum) + " %");

}

void MainWindow::onLedTriggered() {
    // 可以做LED/Buzzer状态指示
    ui->label_led->setText("Triggered");
}


