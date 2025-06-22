#include "dataprocess.h"
#include <unistd.h>
#include <QString>
#include <QThread>
#include <QDebug>
#include <sys/ioctl.h>      // for ioctl()
#include <linux/i2c-dev.h>  // for I2C_SLAVE


int DataProcess(int mode) {
    const char *path = NULL;
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
//        case TempHumidity:
//            path = "/dev/DHT11";
//            break;
        case LEDBuzzer:
            // 可选：如果没有设备路径，可以设置为 nullptr 或空处理
            path = "/dev/LEDBuzzer";  // 或者 nullptr，如果你还没有该设备
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
    case BroadGas:
        if (::read(fd, &result, sizeof(result)) != sizeof(result)) {
            qWarning() << "BroadGas read error";
        }
        break;

    case Ultrasonic: {
        long long raw = 0;
        if (::read(fd, &raw, sizeof(raw)) != sizeof(raw)) {
            qWarning() << "Ultrasonic read error";
        }
        float dist = raw * 0.017f;
        result = (int)(dist * 100);
        break;
    }

    case LightLevel:
    {
        const char *dev = "/dev/i2c-0";  // 根据 i2cdetect 结果选择正确的 I2C 设备
        int addr = 0x23;                 // BH1750 默认 I2C 地址

        int fd = open(dev, O_RDWR);
        if (fd < 0) {
            qWarning() << "Failed to open device" << dev;
            break;
        }

        if (ioctl(fd, I2C_SLAVE, addr) < 0) {
            qWarning() << "Failed to set I2C_SLAVE address to 0x23";
            close(fd);
            break;
        }

        unsigned char cmd = 0x10;  // 连续高分辨率模式
        if (write(fd, &cmd, 1) != 1) {
            qWarning() << "Failed to write measurement command to BH1750";
            close(fd);
            break;
        }

        usleep(1800);  // 等待测量完成（必须）

        unsigned char buf[2];
        if (read(fd, buf, 2) != 2) {
            qWarning() << "Failed to read from BH1750";
            close(fd);
            break;
        }

        close(fd);

        float lux = ((buf[0] << 8) | buf[1]) / 1.2f;  // 将原始数据转为 lux
        result = lux;
        break;
    }


//    case TempHumidity: {
//        int fd;
//            unsigned char buf[6];   //定义存放数据的数组
//            int length;

//            /* 以只读方式打开设备节点 */
//            fd = open("/dev/DHT11", O_RDONLY);
//            if(fd == -1)
//            {
//                printf("open failed!\n");
//                return -1;
//            }
//            while(1)
//            {
//                length = read(fd, buf, 6);  // 读取温湿度数据
//                if(length == -1)
//                {
//                    printf("read error!\n");
//                    return -1;
//                }
//                /* 将数据从终端打印出来 */
//                ui->label_5->setText("Temp : %d.%d℃, Humi : %d%RH\n", buf[2],buf[3],buf[0]);

//            }





    default:
        break;
    }

    ::close(fd);
    return result;
}
//根据广谱气体的返回数据调用LED蜂鸣器进行警告
void WarningGas(int gas)
{

    const char *LEDBUZZER_DEV  = "/dev/LEDBuzzer";
    const int   GAS_THRESHOLD  = 0;
    int fd = ::open(LEDBUZZER_DEV, O_RDWR);
        if (fd < 0) {
            qWarning() << "WarningGas: failed to open" << LEDBUZZER_DEV;
            return;
        }

        // 如果气体超标，写 1 打开 LED＋蜂鸣；否则写 0 关闭
        uint8_t cmd = (gas > GAS_THRESHOLD) ? 1 : 0;
        ssize_t written = ::write(fd, &cmd, sizeof(cmd));
        if (written != sizeof(cmd)) {
            qWarning() << "WarningGas: write error, wrote" << written;
        }

        ::close(fd);
}
