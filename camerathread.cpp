#include "camerathread.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/mman.h>

cameraThread::cameraThread(QObject *parent) :
    QThread(parent)
{
    startflag = false;
    if(-1 == (this->openVideo(DEV_NAME0)))//打开摄像头设备
    {
        emit errorshow();
        perror("openVideo fail");
    }else{
        this->getVideoFmt();//获取当前视频设备支持的视频格式
        if(-1 == (this->queryVideoCap()))// 查询视频设备的功能
        {
            perror("queryVideoCap fail");
            exit(-1);
        }

        if(-1 == (this->setVideoFmt()))//设置视频设备的视频数据格式
        {
            printf("setVideoFmt fail, try again!");
            this->closeVideo(videofd);
            if(-1 == (this->openVideo(DEV_NAME1)))  //打开摄像头设备
            {
                emit errorshow();
                perror("openVideo fail");
                exit(-1);
            }

            this->getVideoFmt(); //获取当前视频设备支持的视频格式

            if(-1 == (this->queryVideoCap())) // 查询视频设备的功能
            {
                perror("queryVideoCap fail");
                exit(-1);
            }
            if(-1 == (this->setVideoFmt())) //设置视频设备的视频数据格式
            {
                perror("setVideoFmt fail");
                exit(-1);
            }
        }

        if(-1 == (this->requestVideoBufsAndMmap())) //请求V4L2驱动分配视频缓冲区（申请V4L2视频驱动分配内存）
        {
            perror("requestVideoBufs fail");
            exit(-1);
        }

    }
}

cameraThread::~cameraThread()
{
    this->closeVideo(videofd);
    this->uninitVideo();
}

void cameraThread::run()
{
    while(1)
    {
        usleep(1);
        if(startflag == true)
        {
            if(-1 == this->readFrame())
            {
                perror("readFrame fail");
                //return -1;
            }
        }
    }
}

/**************************************
* 功能     ：视频采集
* 返回值   ：成功返回0，失败返回-1
***************************************/
void cameraThread::startCapture()
{
        startflag = startflag ? false : true;
}

/********************************************************************************************************
* 功能     ：打开摄像头设备
* 返回值   ：成功返回0，失败返回-1
***************************************/
int cameraThread::openVideo(const char *dev_name)
{
    this->videofd = open(dev_name, O_RDWR, 0);//以阻塞方式打开摄像头设备
    if(this->videofd > 0)
    {
        printf("open %s success\n",dev_name);
        return 0;
    }
    else
    {
        perror("open video fail");
        return -1;
    }
}

void cameraThread::closeVideo(int fd)
{
    ::close(fd);
}

/**************************************
* 功能     ：获取当前视频设备支持的视频格式
* 返回值   ：无
***************************************/
void cameraThread::getVideoFmt()
{
    struct v4l2_fmtdesc fmt;

    CLEAR(fmt);
    fmt.index = 0;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while (0 == ioctl(this->videofd, VIDIOC_ENUM_FMT, &fmt))
    {
        fmt.index++;
        printf("pixelformat = %c%c%c%c, description = %s\n",
               fmt.pixelformat & 0xFF, (fmt.pixelformat >> 8) & 0xFF,
               (fmt.pixelformat >> 16) & 0xFF, (fmt.pixelformat >> 24) & 0xFF,
               fmt.description);
        //printf("fmt.index = %d\n",fmt.index);
    }
    printf("getVideoFmt success\n");
}

/**************************************
* 功能     ：查询视频设备的功能
* 返回值   ：成功返回0，失败返回-1
***************************************/
int cameraThread::queryVideoCap()
{
    struct v4l2_capability cap;

    if(-1 == ioctl(this->videofd, VIDIOC_QUERYCAP, &cap))
    {
        perror("VIDIOC_QUERYCAP fail");
        return -1;
    }
    //查看是否支持图像获取
    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
        perror("V4L2_CAP_VIDEO_CAPTURE fail");
        return -1;
    }
    //查看是否支持视频捕获功能
    if(!(cap.capabilities & V4L2_CAP_STREAMING))
    {
        perror("V4L2_CAP_STREAMING fail");
        return -1;
    }

    printf("queryVideoCap success\n");

    return 0;
}

/**************************************
* 功能     ：设置视频设备的视频数据格式，
            例如设置视频图像数据的长、宽，图像格式（JPEG、YUYV格式）
* 返回值   ：成功返回0，失败返回-1
***************************************/
int cameraThread::setVideoFmt()
{
    struct v4l2_format tv4l2_format;

    CLEAR(tv4l2_format);

    tv4l2_format.type                   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tv4l2_format.fmt.pix.width          = IMAGE_WIDTH;
    tv4l2_format.fmt.pix.height         = IMAGE_HEIGHT;
    tv4l2_format.fmt.pix.pixelformat    = V4L2_PIX_FMT_YUYV;
    tv4l2_format.fmt.pix.field          = V4L2_FIELD_NONE;//V4L2_FIELD_INTERLACED

    if(-1 == ioctl(this->videofd, VIDIOC_S_FMT, &tv4l2_format))
    {
        perror("setVideoFmt fail");
        return -1;
    }
    else
    {
        //计算视频图像的大小
        this->fileLength = tv4l2_format.fmt.pix.bytesperline * tv4l2_format.fmt.pix.height;

        printf("setVideoFmt success\n");
        return 0;
    }
}

/**************************************
* 功能     ：请求V4L2驱动分配视频缓冲区（申请V4L2视频驱动分配内存）,
            把内核空间缓冲区映射到用户空间
            投放一个空的视频缓冲区到视频缓冲区输入队列中
            启动视频采集
* 返回值   ：成功返回0，失败返回-1
***************************************/
int cameraThread::requestVideoBufsAndMmap()
{
    unsigned int i = 0;
    struct v4l2_requestbuffers  tV4L2_reqbuf;

    CLEAR(tV4L2_reqbuf);

    tV4L2_reqbuf.count          = 3;    //申请缓冲区的个数
    tV4L2_reqbuf.type           = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    tV4L2_reqbuf.memory         = V4L2_MEMORY_MMAP;

    if(-1 == ioctl(this->videofd, VIDIOC_REQBUFS, &tV4L2_reqbuf))
    {
        perror("requestVideoBufs fail");
        return -1;
    }
    if(tV4L2_reqbuf.count < 2 )
    {
        printf("Memory is not enough\n");
    }

   //内存中建立对应空间
    this->buffers = (struct buffer *)calloc(tV4L2_reqbuf.count,sizeof(*(this->buffers)));

    for (nbuffers = 0; nbuffers < tV4L2_reqbuf.count; ++nbuffers)
    {
        struct v4l2_buffer buf;   //驱动中的一帧

        CLEAR (buf);
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = nbuffers;

        if (-1 == ioctl (this->videofd, VIDIOC_QUERYBUF, &buf)) //映射用户空间
        {
            perror("VIDIOC_QUERYBUF fail");
            return -1;
        }

        this->buffers[nbuffers].length = buf.length;
        buffers[nbuffers].start =
        mmap (NULL /* start anywhere */,    //通过mmap建立映射关系
        buf.length,
        PROT_READ | PROT_WRITE /* required */,
        MAP_SHARED /* recommended */,
        this->videofd, buf.m.offset);

        if (MAP_FAILED == buffers[nbuffers].start)
        {
            perror("mmap failed");
            return -1;
        }
    }

    for (i = 0; i < nbuffers; ++i)
    {
        struct v4l2_buffer buf;
        CLEAR (buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;

        if (-1 == ioctl (this->videofd, VIDIOC_QBUF, &buf)) //申请到的缓冲进入列队
        {
            perror("VIDIOC_QBUF fail");
            return -1;
        }
    }
    enum v4l2_buf_type v4l2type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    //启动视频采集
    if(-1 == ioctl(this->videofd, VIDIOC_STREAMON, &v4l2type))
    {
        perror("VIDIOC_STREAMON fail");
        return -1;
    }

    printf("requestVideoBufs success\n");
    return 0;
}

/**************************************
* 功能     ：从视频缓冲区的输出队列中取得一个已经保存有一帧视频数据的视频缓冲区
* 返回值   ：成功返回0，失败返回-1
***************************************/
int cameraThread::readFrame()
{
    CLEAR(this->tV4L2buf);

    this->tV4L2buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    this->tV4L2buf.memory = V4L2_MEMORY_MMAP;

    if(-1 == ioctl(this->videofd, VIDIOC_DQBUF, &(this->tV4L2buf))) //出列采集的帧缓冲
    {
        perror("VIDIOC_DQBUF fail");
        return -1;
    }
    if(-1 == this->storeImage()) //保存图片
    {
        perror("storeImage fail");
        return -1;
    }
    if(-1 == ioctl (this->videofd, VIDIOC_QBUF, &(this->tV4L2buf)))//再将其入列
    {
        perror("VIDIOC_QBUF");
        return -1;
    }

    return 0;
}

//保存图片
int cameraThread::storeImage()
{
    encode_jpeg((unsigned char*)(this->buffers[this->tV4L2buf.index].start),IMAGE_WIDTH,IMAGE_HEIGHT); //RGB24 to Jpeg
    return 0;
}

//停止视频采集
int cameraThread::stopCapture()
{
    enum v4l2_buf_type  v4l2type;

    v4l2type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(-1 == ioctl(this->videofd, VIDIOC_STREAMOFF, &v4l2type))
    {
        perror("VIDIOC_STREAMOFF fail");
        return -1;
    }

    return 0;
}

//取消映射
int cameraThread::uninitVideo()
{
    unsigned int i = 0;
    printf("nbuffers = %u\n",this->nbuffers);
    for(i=0; i<this->nbuffers; ++i)
    {
        if(-1 == munmap(this->buffers[i].start, this->buffers[i].length))
        {
            perror("munmap fail");
            return -1;
        }
    }
    free(this->buffers);
    return 0;
}

int cameraThread::encode_jpeg(unsigned char *lpbuf,int width,int height)
{
    unsigned  char frame_buffer[width*height*3];
    yuyv_2_rgb888(lpbuf,frame_buffer);
    emit Collect_complete(frame_buffer);
    return true ;
}

int cameraThread::yuyv_2_rgb888(unsigned char *buffers, unsigned char *frame_buffer)
{
    int           i,j;
    unsigned char y1,y2,u,v;
    int r1,g1,b1,r2,g2,b2;
    unsigned char * pointer;

    pointer = buffers;

    for(i=0;i<IMAGE_HEIGHT;i++)
    {
    for(j=0;j<IMAGE_WIDTH/2;j++)
    {
    y1 = *( pointer + (i*IMAGE_WIDTH/2+j)*4);
    u  = *( pointer + (i*IMAGE_WIDTH/2+j)*4 + 1);
    y2 = *( pointer + (i*IMAGE_WIDTH/2+j)*4 + 2);
    v  = *( pointer + (i*IMAGE_WIDTH/2+j)*4 + 3);

    r1 = y1 + 1.042*(v-128);
    g1 = y1 - 0.34414*(u-128) - 0.71414*(v-128);
    b1 = y1 + 1.772*(u-128);

    r2 = y2 + 1.042*(v-128);
    g2 = y2 - 0.34414*(u-128) - 0.71414*(v-128);
    b2 = y2 + 1.772*(u-128);

    if(r1>255)
    r1 = 255;
    else if(r1<0)
    r1 = 0;

    if(b1>255)
    b1 = 255;
    else if(b1<0)
    b1 = 0;

    if(g1>255)
    g1 = 255;
    else if(g1<0)
    g1 = 0;

    if(r2>255)
    r2 = 255;
    else if(r2<0)
    r2 = 0;

    if(b2>255)
    b2 = 255;
    else if(b2<0)
    b2 = 0;

    if(g2>255)
    g2 = 255;
    else if(g2<0)
    g2 = 0;

    *(frame_buffer + (i*IMAGE_WIDTH/2+j)*6    ) = (unsigned char)r1;
    *(frame_buffer + (i*IMAGE_WIDTH/2+j)*6 + 1) = (unsigned char)g1;
    *(frame_buffer + (i*IMAGE_WIDTH/2+j)*6 + 2) = (unsigned char)b1;
    *(frame_buffer + (i*IMAGE_WIDTH/2+j)*6 + 3) = (unsigned char)r2;
    *(frame_buffer + (i*IMAGE_WIDTH/2+j)*6 + 4) = (unsigned char)g2;
    *(frame_buffer + (i*IMAGE_WIDTH/2+j)*6 + 5) = (unsigned char)b2;
    }
    }
    return 0;
}

