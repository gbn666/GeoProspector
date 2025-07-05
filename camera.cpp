// camera.cpp
#include "camera.h"
#include "ui_camera.h"

camera::camera(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::camera)
{
    ui->setupUi(this);

    // 1. 摄像头线程，异步获取 QImage
    camerathread = new cameraThread(this);
    connect(camerathread, &cameraThread::errorshow,
            this, &camera::errorshowslot);
    connect(this, &camera::Show_complete,
            camerathread, &cameraThread::startCapture);
    connect(camerathread, &cameraThread::imageReady,
            this, &camera::videoDisplay);
    camerathread->start();
}

camera::~camera()
{
    delete ui;
}

void camera::errorshowslot()
{
    ui->cameraLabel->setText(
        tr("摄像头初始化失败，请检查是否插好，并重新启动！")
    );
}

void camera::videoDisplay(const QImage &frame)
{
    // 直接在 QLabel 显示最新帧
    ui->cameraLabel->setPixmap(
        QPixmap::fromImage(frame
            .scaled(ui->cameraLabel->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation))
    );
}

void camera::on_startButton_clicked()
{
    // 切换播放/暂停
    cameraflag = !cameraflag;
    ui->startButton->setText(
        cameraflag ? tr("暂停") : tr("播放")
    );
    emit Show_complete();
}
