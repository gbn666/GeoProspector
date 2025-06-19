#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "visualizer.h"
#include "ui_visualizer.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("可视化");
    ui->viewlabel->setText("相机画面");




}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onFrameReady(unsigned char *rgbBuffer)
{
    // 把 cameraThread 转成 320×240 的 QImage
    QImage img(rgbBuffer,
               320,              // FRAME_WIDTH
               240,              // FRAME_HEIGHT
               320 * 3,          // bytesPerLine
               QImage::Format_RGB888);

    // 直接设置，不做 scaled()，也不用 setScaledContents(true)
    ui->viewlabel->setScaledContents(false);
    ui->viewlabel->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
    visualizer *ui=new visualizer;
    ui->show();






}
