#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QMovie>
#include <QTimer>
#include<QImage>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>
#include <linux/videodev2.h>
#include "camerathread.h"


namespace Ui {
class camera;
}

class camera : public QWidget
{
    Q_OBJECT

public:
    explicit camera(QWidget *parent = 0);
    ~camera();

private slots:
    void on_startButton_clicked();

private:
    Ui::camera *ui;

public:
    bool cameraflag;

public:
    cameraThread *camerathread;

signals:
       void Show_complete();


private slots:
    void videoDisplay(unsigned char *pp);
    void errorshowslot();


};

#endif // CAMERA_H
