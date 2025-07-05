// dataprocessthread.cpp
#include "dataprocessthread.h"
#include <QProcess>
#include <QDebug>
#include <cstring>

DataProcessThread::DataProcessThread(ProcessMode mode, QObject *parent)
    : QObject(parent)
    , m_mode(mode)
    , m_running(false)
    , m_timer(nullptr)
    , buzzerTimer(nullptr)
    , buzzerFd(-1)
    , lastDist(0.0f)
{
    if (m_mode == Ultrasonic) {
        buzzerTimer = new QTimer(this);
        connect(buzzerTimer, &QTimer::timeout,
                this, &DataProcessThread::triggerBuzzer);

        buzzerFd = ::open("/dev/LEDBuzzer", O_RDWR);
        if (buzzerFd < 0) {
//            qWarning() << "[Buzzer] open failed:" << strerror(errno);
        } else {
//            qDebug() << "[Buzzer] opened fd =" << buzzerFd;
        }
    }

    initDrivers();

    moveToThread(&m_thread);
    connect(&m_thread, &QThread::started,
            this, &DataProcessThread::start);
    connect(this, &DataProcessThread::finished,
            &m_thread, &QThread::quit);
    connect(&m_thread, &QThread::finished,
            this, &DataProcessThread::deleteLater);
    m_thread.start();
}

DataProcessThread::~DataProcessThread()
{
    stop();
    m_thread.quit();
    m_thread.wait();
    if (buzzerTimer) {
        buzzerTimer->stop();
        buzzerTimer->deleteLater();
    }
    if (buzzerFd >= 0) {
        ::close(buzzerFd);
    }
}

void DataProcessThread::loadDriver(const QString &path)
{
    QStringList args{path};
    int ret = QProcess::execute("insmod", args);
    if (ret != 0) {
        qWarning() << "insmod failed for" << path;
    }
}

void DataProcessThread::initDrivers()
{
    loadDriver("/home/root/vendor/BH1750_driver.ko");
    loadDriver("/home/root/vendor/HCSR04_driver.ko");
    loadDriver("/home/root/vendor/MQ2_driver.ko");
    loadDriver("/home/root/vendor/LEDBuzzer_driver.ko");
    loadDriver("/home/root/vendor/DHT11_driver.ko");
}

void DataProcessThread::start()
{
    if (m_running) return;
    m_running = true;

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,
            this, &DataProcessThread::process);
    m_timer->start(1000);
}

void DataProcessThread::stop()
{
    if (!m_running) return;
    m_running = false;
    if (m_timer) {
        m_timer->stop();
        m_timer->deleteLater();
        m_timer = nullptr;
    }
    if (buzzerTimer) {
        buzzerTimer->stop();
    }
    emit finished();
}

void DataProcessThread::process()
{
    if (!m_running) return;

    switch (m_mode) {
    case BroadGas: {
        int gas = DataProcess(BroadGas);
        emit gasWarning(gas);
        break;
    }
    case Ultrasonic: {
        float dist = DataProcess(Ultrasonic) / 100.0f;
        emit distanceWarning(dist);

        if (qAbs(dist - lastDist) > 0.5f) {
            int interval = calculateBuzzerInterval(dist);
//            qDebug() << "[Ultrasonic] dist =" << dist
//                     << " interval =" << interval;
            if (interval > 0) {
                buzzerTimer->start(interval);
            } else {
                buzzerTimer->stop();
            }
            lastDist = dist;
        }
        break;
    }
    case LightLevel: {
        int light = DataProcess(LightLevel);
        emit lightDetected(QString::number(light));
        break;
    }
    case TempHumidity: {
        int result = DataProcess(TempHumidity);
        if (result != 0) {
            float temperature = (result >> 16) / 10.0f;
            float humidity    = (result & 0xFFFF) / 10.0f;
            emit tempHumDetected(temperature, humidity);
        }
        break;
    }
    default:
        break;
    }
}

void DataProcessThread::triggerBuzzer()
{
    if (buzzerFd < 0) return;

//    qDebug() << "[Buzzer] ioctl BUZZER_ON (4)";
    if (ioctl(buzzerFd, BUZZER_ON) < 0) {
        qWarning() << "ioctl BUZZER_ON failed:" << strerror(errno);
    }

    usleep(10000);

//    qDebug() << "[Buzzer] ioctl BUZZER_OFF (3)";
    if (ioctl(buzzerFd, BUZZER_OFF) < 0) {
//        qWarning() << "ioctl BUZZER_OFF failed:" << strerror(errno);
    }
}

int DataProcessThread::calculateBuzzerInterval(float dist)
{
    if (dist <= 50 && dist > 40) return 1000;
    if (dist <= 40 && dist > 30) return 600;
    if (dist <= 30 && dist > 20) return 400;
    if (dist <= 20 && dist > 10) return 200;
    if (dist <= 10 && dist > 5)  return 100;
    if (dist <= 5 && dist > 0)   return 50;
    return 0;
}
