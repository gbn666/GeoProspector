// camerathread.h
#pragma once

#include <QThread>
#include <QImage>
#include <linux/videodev2.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 设备名
#define DEV_NAME0 "/dev/video2"
#define DEV_NAME1 "/dev/video3"

#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480
#define CLEAR(x) memset(&(x), 0, sizeof(x))

// V4L2 缓冲区描述
struct buffer {
    void   *start;
    size_t  length;
};

class cameraThread : public QThread
{
    Q_OBJECT

public:
    explicit cameraThread(QObject *parent = nullptr);
    ~cameraThread() override;

    // 切换开始/停止采集
    void startCapture();

signals:
    // 返回每帧图像
    void imageReady(const QImage &img);
    // 初始化失败
    void errorshow();

protected:
    // 线程主循环
    void run() override;

private:
    // V4L2 初始化步骤
    int  openAndInitDevice();
    int  queryVideoCap();
    int  setVideoFmt();
    int  requestVideoBufsAndMmap();

    // 采集与释放
    int  readFrame();
    int  storeImage();
    int  stopCaptureInternal();
    int  uninitVideo();

    // 格式转换
    int  yuyv_to_rgb888(const unsigned char *yuyv, unsigned char *rgb);

    // V4L2 辅助
    void getVideoFmt();
    void closeVideo(int fd);

    // 成员变量
    int                videofd = -1;
    bool               capturing = false;
    struct buffer     *buffers = nullptr;
    unsigned int       nbuffers = 0;
    unsigned char     *rgbBuffer = nullptr;

    // 缺少的 V4L2 缓冲区存储结构
    struct v4l2_buffer tV4L2buf;
};
