#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "camera.h"
#include "camerathread.h"
#include "visualizer.h"
#include "ui_visualizer.h"
#include <QLabel>

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
}
