#include "dht11thread.h"
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

DHT11Thread::DHT11Thread(QObject *parent)
    : QThread(parent) {}

void DHT11Thread::run()
{
    int fd = open("/dev/DHT11", O_RDONLY);
    if (fd < 0) {
        qDebug() << "DHT11 open failed:" << strerror(errno);
        return;
    }

    unsigned char buf[5];
    while (!isInterruptionRequested()) {
        int bytesRead = ::read(fd, buf, sizeof(buf));
        if (bytesRead == sizeof(buf)) {
            uint8_t sum = buf[0] + buf[1] + buf[2] + buf[3];
            if (buf[4] == sum) {
                int hum  = buf[0];   // 整数湿度 %
                int temp = buf[2];   // 整数温度 ℃
                emit newTempHum(temp, hum);   // 发 int 即可
            }
        }
        msleep(2000);
    }
    ::close(fd);
}
