#include "dataprocess.h"
#include <unistd.h>
#include <QString>
#include <QDebug>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int DataProcess(ProcessMode mode)
{
    const char *path = nullptr;
    switch (mode) {
    case BroadGas:
        path = "/dev/MQ2";
        break;
    case Ultrasonic:
        path = "/dev/HCSR04";
        break;
    case LightLevel:
        path = "/dev/i2c-0";
        break;
    case TempHumidity:
        path = "/dev/DHT11";
        break;
    default:
        qWarning() << "Unknown ProcessMode in DataProcess:" << mode;
        return 0;
    }

    int fd = ::open(path, O_RDWR);
    if (fd < 0) {
        qWarning() << "Failed to open device" << path;
        return 0;
    }

    int result = 0;
    switch (mode) {
    case BroadGas: {
        if (::read(fd, &result, sizeof(result)) != sizeof(result)) {

        }
        break;
    }
    case Ultrasonic: {
        long long raw = 0;
        if (::read(fd, &raw, sizeof(raw)) != sizeof(raw)) {

        } else {
            float dist = raw * 0.017f;
            result = static_cast<int>(dist * 100);
        }
        break;
    }
    case LightLevel: {
        int addr = 0x23;
        if (ioctl(fd, I2C_SLAVE, addr) < 0) {
            qWarning() << "Failed to set I2C_SLAVE address to 0x23";
            ::close(fd);
            return 0;
        }
        unsigned char cmd = 0x10;
        if (write(fd, &cmd, 1) != 1) {
            qWarning() << "Failed to write measurement command to BH1750";
            ::close(fd);
            return 0;
        }
        usleep(1800);
        unsigned char buf[2];
        if (read(fd, buf, 2) != 2) {
            qWarning() << "Failed to read from BH1750";
            ::close(fd);
            return 0;
        }
        float lux = ((buf[0] << 8) | buf[1]) / 1.2f;
        result = static_cast<int>(lux);
        break;
    }
    case TempHumidity: {
        if (mode != TempHumidity) return 0;

         int fd = open("/dev/DHT11", O_RDONLY);
         if (fd < 0) {
             qDebug() << "open /dev/DHT11 failed:" << strerror(errno);
             return 0;
         }

         unsigned char buf[6];
         ssize_t n = read(fd, buf, sizeof(buf));
         close(fd);

         qDebug() << "DHT11 read n =" << n
                  << "buf =" << QByteArray((char*)buf, n).toHex()
                  << "sum =" << (buf[0]+buf[1]+buf[2]+buf[3]) << "chk" << buf[4];

         if (n != 6) return 0;
         uint8_t sum = buf[0] + buf[1] + buf[2] + buf[3];
         if (buf[4] != sum) return 0;

         int temp = buf[2];
         int hum  = buf[0];
         return (temp << 16) | hum;   // 高 16 位温度，低 16 位湿度
        }
    default:
        break;
    }
    ::close(fd);
    return result;
}

void WarningGas(int gas)
{
    const char *LEDBUZZER_DEV = "/dev/LEDBuzzer";
    const int GAS_THRESHOLD = 0;
    int fd = ::open(LEDBUZZER_DEV, O_RDWR);
    if (fd < 0) {
        qWarning() << "WarningGas: failed to open" << LEDBUZZER_DEV;
        return;
    }
    uint8_t cmd = (gas > GAS_THRESHOLD) ? 1 : 0;
    if(cmd)
    {
        ioctl(fd,2);
        ioctl(fd,4);

    }
    else{
        ioctl(fd,3);
        ioctl(fd,1);
    }
    ::close(fd);
}
