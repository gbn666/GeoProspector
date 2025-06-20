// camerathread.cpp

#include "camerathread.h"

#include <QDebug>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>    // <-- 为 ioctl 提供声明
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

// 构造：分配 RGB 缓冲，打开并初始化设备
cameraThread::cameraThread(QObject *parent)
  : QThread(parent),
    videofd(-1),
    capturing(false),
    buffers(NULL),
    nbuffers(0),
    fileLength(0),
    rgbBuffer(NULL)
{
    // 分配一次性 RGB888 缓冲
    rgbBuffer = (unsigned char*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 3);
    if (!rgbBuffer) {
        qCritical("Failed to malloc rgbBuffer");
        emit errorshow();
        return;
    }

    // 打开并初始化设备
    if (openAndInitDevice() < 0) {
        qCritical("Camera init failed");
        emit errorshow();
    }
}

cameraThread::~cameraThread()
{
    // 停采 & 释放
    stopCaptureInternal();
    uninitVideo();
    if (videofd >= 0) closeVideo(videofd);
    if (buffers)  free(buffers);
    if (rgbBuffer) free(rgbBuffer);
}

void cameraThread::startCapture()
{
    capturing = !capturing;
}

void cameraThread::run()
{
    while (true) {
        if (capturing) {
            if (readFrame() < 0) {
                perror("readFrame");
            }
        }
        // 控制帧率约30fps
        usleep(33000);
    }
}

//—— 私有方法 ——//

int cameraThread::openAndInitDevice()
{
    const char* devices[] = { DEV_NAME0, DEV_NAME1 };
    const int   devCount  = 2;
    bool        ok        = false;

    for (int i = 0; i < devCount; ++i) {
        videofd = ::open(devices[i], O_RDWR);
        if (videofd < 0) {
            qWarning("open %s failed: %s", devices[i], strerror(errno));
            continue;
        }
        qDebug("open %s success", devices[i]);

        getVideoFmt();
        if (queryVideoCap() < 0 || setVideoFmt() < 0 || requestVideoBufsAndMmap() < 0) {
            closeVideo(videofd);
            videofd = -1;
            continue;
        }
        ok = true;
        break;
    }
    return ok ? 0 : -1;
}

void cameraThread::getVideoFmt()
{
    struct v4l2_fmtdesc fmt;
    CLEAR(fmt);
    fmt.index = 0;
    fmt.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while (ioctl(videofd, VIDIOC_ENUM_FMT, &fmt) == 0) {
        fprintf(stdout,
                "fmt %u: %c%c%c%c (%s)\n",
                fmt.index,
                fmt.pixelformat & 0xFF,
                (fmt.pixelformat >> 8) & 0xFF,
                (fmt.pixelformat >> 16) & 0xFF,
                (fmt.pixelformat >> 24) & 0xFF,
                fmt.description);
        fmt.index++;
    }
}

int cameraThread::queryVideoCap()
{
    struct v4l2_capability cap;
    if (ioctl(videofd, VIDIOC_QUERYCAP, &cap) < 0) return -1;
    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) return -1;
    if (!(cap.capabilities & V4L2_CAP_STREAMING))     return -1;
    return 0;
}

int cameraThread::setVideoFmt()
{
    struct v4l2_format fmt;
    CLEAR(fmt);
    fmt.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = IMAGE_WIDTH;
    fmt.fmt.pix.height      = IMAGE_HEIGHT;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field       = V4L2_FIELD_NONE;
    if (ioctl(videofd, VIDIOC_S_FMT, &fmt) < 0) return -1;
    fileLength = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    return 0;
}

int cameraThread::requestVideoBufsAndMmap()
{
    struct v4l2_requestbuffers req;
    CLEAR(req);
    req.count  = 4;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(videofd, VIDIOC_REQBUFS, &req) < 0) return -1;

    buffers = (buffer*)calloc(req.count, sizeof(buffer));
    for (nbuffers = 0; nbuffers < req.count; ++nbuffers) {
        struct v4l2_buffer buf;
        CLEAR(buf);
        buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index  = nbuffers;
        if (ioctl(videofd, VIDIOC_QUERYBUF, &buf) < 0) return -1;
        buffers[nbuffers].length = buf.length;
        buffers[nbuffers].start = mmap(NULL, buf.length,
                                        PROT_READ|PROT_WRITE,
                                        MAP_SHARED,
                                        videofd, buf.m.offset);
        if (buffers[nbuffers].start == MAP_FAILED) return -1;
        if (ioctl(videofd, VIDIOC_QBUF, &buf) < 0) return -1;
    }
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(videofd, VIDIOC_STREAMON, &type) < 0) return -1;
    return 0;
}

int cameraThread::readFrame()
{
    CLEAR(tV4L2buf);
    tV4L2buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4L2buf.memory = V4L2_MEMORY_MMAP;
    if (ioctl(videofd, VIDIOC_DQBUF, &tV4L2buf) < 0) return -1;
    storeImage();
    if (ioctl(videofd, VIDIOC_QBUF, &tV4L2buf) < 0) return -1;
    return 0;
}

int cameraThread::storeImage()
{
    yuyv_to_rgb888((unsigned char*)buffers[tV4L2buf.index].start, rgbBuffer);
    emit Collect_complete(rgbBuffer);
    return 0;
}

int cameraThread::stopCaptureInternal()
{
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(videofd, VIDIOC_STREAMOFF, &type) < 0) {
        perror("VIDIOC_STREAMOFF");
        return -1;
    }
    return 0;
}
void cameraThread::closeVideo(int fd)
{
    if (fd >= 0) {
        ::close(fd);
    }
}

int cameraThread::uninitVideo()
{
    for (unsigned int i = 0; i < nbuffers; ++i) {
        munmap(buffers[i].start, buffers[i].length);
    }
    return 0;
}

// YUYV -> RGB888
int cameraThread::yuyv_to_rgb888(const unsigned char *yuyv, unsigned char *rgb)
{
    int idx = 0;
    for (int i = 0; i < IMAGE_HEIGHT; ++i) {
        for (int j = 0; j < IMAGE_WIDTH; j += 2) {
            int y0 = *yuyv++ - 16;
            int u  = *yuyv++ - 128;
            int y1 = *yuyv++ - 16;
            int v  = *yuyv++ - 128;
            int c0 = (298*y0 + 128) >> 8;
            int c1 = (298*y1 + 128) >> 8;
            int r0 = c0 + ((409 * v) >> 8);
            int g0 = c0 - ((100 * u + 208 * v) >> 8);
            int b0 = c0 + ((516 * u) >> 8);
            int r1 = c1 + ((409 * v) >> 8);
            int g1 = c1 - ((100 * u + 208 * v) >> 8);
            int b1 = c1 + ((516 * u) >> 8);
            rgb[idx++] = (r0 < 0 ? 0 : r0 > 255 ? 255 : r0);
            rgb[idx++] = (g0 < 0 ? 0 : g0 > 255 ? 255 : g0);
            rgb[idx++] = (b0 < 0 ? 0 : b0 > 255 ? 255 : b0);
            rgb[idx++] = (r1 < 0 ? 0 : r1 > 255 ? 255 : r1);
            rgb[idx++] = (g1 < 0 ? 0 : g1 > 255 ? 255 : g1);
            rgb[idx++] = (b1 < 0 ? 0 : b1 > 255 ? 255 : b1);
        }
    }
    return 0;
}
