#include "dht11thread.h"
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

DHT11Thread::DHT11Thread(QObject *parent)
    : QThread(parent)
{}

void DHT11Thread::run()
{
    // 打开 DHT11 设备节点
    int fd = open("/dev/DHT11", O_RDWR);
    if (fd < 0) {
        qDebug() << "DHT11 open failed:" << strerror(errno);
        return;
    }

    unsigned char buf[6];
    while (!isInterruptionRequested()) {
        // 读取 6 字节：湿度整数、湿度小数、温度整数、温度小数、校验、高字节校验
        int bytesRead = ::read(fd, buf, sizeof(buf));
        if (bytesRead == sizeof(buf)) {
            // 发射信号到主界面
            emit newTempHum(
                QString::number(buf[2]),  // 温度整数
                QString::number(buf[3]),  // 温度小数
                QString::number(buf[0])   // 湿度整数
            );
        }
        // 每 2 秒读一次
        msleep(2000);
    }

    ::close(fd);
}
