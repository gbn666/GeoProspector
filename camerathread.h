#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QThread>
#include <QWidget>
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

#define DEV_NAME0 "/dev/video2"      //摄像头设备名
#define DEV_NAME1 "/dev/video3"      //摄像头设备名(备用)
//#define IMAGE_WIDTH 320//视频图像宽度
//#define IMAGE_HEIGHT 240//视频图像高度
#define IMAGE_WIDTH 640//视频图像宽度
#define IMAGE_HEIGHT 480//视频图像高度
//#define IMAGE_WIDTH 1280//视频图像宽度
//#define IMAGE_HEIGHT 720//视频图像高度
#define CLEAR(x) memset(&(x), 0, sizeof(x)) //空间清零

struct buffer {
        void *                  start;
        size_t                  length;
};

class cameraThread: public QThread
{
    Q_OBJECT

    public:
        explicit cameraThread(QObject *parent = 0);
        ~cameraThread();

protected:
    void run();

public:
    int videofd;            //摄像头文件描述符
    unsigned int fileLength; //视频图像的大小
    unsigned int nbuffers;

public:
    struct buffer *buffers;
    struct v4l2_buffer tV4L2buf;

signals:
    void Collect_complete(unsigned char *pp);
    void errorshow();

protected:
    bool startflag;

private slots:
    void startCapture();

public:
    int openVideo(const char *dev_name);    //打开摄像头设备
    void closeVideo(int fd);   //close the open device
    void getVideoFmt();     //获取当前视频设备支持的视频格式
    int queryVideoCap();    // 查询视频设备的功能
    int setVideoFmt();      //设置视频设备的视频数据格式
    int requestVideoBufsAndMmap(); //请求V4L2驱动分配视频缓冲区（申请V4L2视频驱动分配内存）
    int readFrame();        //从视频缓冲区的输出队列中取得一个已经保存有一帧视频数据的视频缓冲区
    int storeImage();       //将从视频缓冲区取出的数据存入文件中
    int stopCapture();      //停止视频采集
    int uninitVideo();      //取消映射
    void myTimerStart();    //start myTimer
    void myTimerStop();     //stop myTimer
    int  encode_jpeg(unsigned char *lpbuf,int width,int height);  //图片转换
    int yuyv_2_rgb888(unsigned char *buffers, unsigned char *frame_buffer);//yuyv to rgb888
    int yuyv_to_rgb888(unsigned char *buffers, unsigned char *frame_buffer);//yuyv to rgb888
};

#endif // WORKTHREAD_H
