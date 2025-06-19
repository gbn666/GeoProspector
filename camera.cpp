#include "camera.h"
#include "ui_camera.h"
#include <stdlib.h>

camera::camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);

    camerathread = new cameraThread();

    connect(camerathread, SIGNAL(errorshow()), this, SLOT(errorshowslot()));

    connect(this,SIGNAL(Show_complete()),camerathread,SLOT(startCapture()));
    connect(camerathread,SIGNAL(Collect_complete(unsigned char*)),this,SLOT(videoDisplay(unsigned char*)));
    camerathread->start();
}

camera::~camera()
{
    delete ui;
}

void camera::errorshowslot()
{
    ui->cameraLabel->setText(tr("摄像头初始化失败，请检查是否插好，并重新启动！"));
}

void camera::videoDisplay(unsigned char *pp)
{
//    QImage frame = QImage(pp,IMAGE_WIDTH,IMAGE_HEIGHT,QImage::Format_RGB888).mirrored(false, true);
//    ui->cameraLabel->setPixmap(QPixmap::fromImage(frame));
    QImage frame = QImage(pp,IMAGE_WIDTH,IMAGE_HEIGHT,QImage::Format_RGB888).mirrored(false, false);
    ui->cameraLabel->setPixmap(QPixmap::fromImage(frame));
}

void camera::on_startButton_clicked()
{
    cameraflag = cameraflag ? false : true;
    if(cameraflag == true)
    {
         ui->startButton->setText(tr("暂停"));
        emit this->Show_complete();
    }
    else
    {
       ui->startButton->setText(tr("播放"));
       emit this->Show_complete();
    }
}
