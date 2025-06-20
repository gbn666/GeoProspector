#include "dataprocess.h"
#include <unistd.h>
#include <QString>
#include <QDebug>

int DataProcess(int mode) {
    const char *path = NULL;
    switch (mode) {
        case BroadGas:
            path = "/dev/MQ2";
            break;
        case Ultrasonic:
            path = "/dev/ULTRASONIC";
            break;
        case LightLevel:
            path = "/dev/BH1750";
            break;
        case TempHumidity:
            path = "/dev/TempHum";
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
        if (::read(fd, &result, sizeof(result)) != sizeof(result)) {
            qWarning() << "LightLevel read error";
        }
        break;

    case TempHumidity: {
        int data[2] = {0};
        if (::read(fd, data, sizeof(data)) != sizeof(data)) {
            qWarning() << "TempHumidity read error";
        }
        int temp = data[0] / 1000;
        int hum  = data[1] / 1000;
        result = temp * 100 + hum;
        break;
    }

    default:
        break;
    }

    ::close(fd);
    return result;
}
