#include "dataprocessthread.h"
#include <QTimer>
#include <QDebug>
#include <unistd.h>
#include <QProcess>

DataProcessThread::DataProcessThread(ProcessMode mode, QObject *parent)
    : QObject(parent)
    , m_mode(mode)
    , m_running(false)
{
    initDrivers();

    moveToThread(&m_thread);
    connect(&m_thread, SIGNAL(started()), this, SLOT(start()));
    connect(this, SIGNAL(finished()), &m_thread, SLOT(quit()));
    connect(&m_thread, SIGNAL(finished()), this, SLOT(deleteLater()));
}

DataProcessThread::~DataProcessThread() {
    stop();
    m_thread.wait();
}

void DataProcessThread::loadDriver(const QString &path) {
    QStringList args;
    args << path;
    int ret = QProcess::execute("insmod", args);
    if (ret != 0) {
        qDebug() << "Driver already loaded or failed:" << path;
    } else {
        qDebug() << "Loaded driver:" << path;
    }
}

void DataProcessThread::initDrivers() {
    // 分别调用 loadDriver 加载模块
    loadDriver("/vendor/test/module/BH1750/driver/BH1750_driver.ko");
    loadDriver("/vendor/test/module/ULTRASONIC/driver/US_driver.ko");
    loadDriver("/vendor/test/module/GAS/driver/GAS_driver.ko");
    loadDriver("/vendor/test/module/LED_BUZZER/driver/LEDBuzzer_driver.ko");
    loadDriver("/vendor/test/module/TEMP_HUMID/driver/TH_driver.ko");
}

void DataProcessThread::start() {
    if (m_running) return;
    m_running = true;

    QTimer *timer = new QTimer;
    timer->moveToThread(&m_thread);
    timer->setInterval(500);

    connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    connect(this, SIGNAL(finished()), timer, SLOT(stop()));

    timer->start();
}

void DataProcessThread::stop() {
    if (!m_running) return;
    m_running = false;
    emit finished();
}

void DataProcessThread::process() {
    if (!m_running) return;

    switch (m_mode) {
    case BroadGas: {
        int gas = DataProcess(static_cast<int>(BroadGas));
        emit gasWarning(gas);
        break;
    }
    case Ultrasonic: {
        float dist = DataProcess(static_cast<int>(Ultrasonic));
        emit distanceWarning(dist);
        break;
    }
    case LedBuzzer: {
        gasWarning(0);
        emit ledBuzzerTriggered();
        break;
    }
    case LightLevel: {
        int light = DataProcess(static_cast<int>(LightLevel));
        emit lightDetected(QString::number(light));
        break;
    }
    case TempHumidity: {
        int th = DataProcess(static_cast<int>(TempHumidity));
        emit tempHumDetected(QString::number(th));
        break;
    }
    default:
        break;
    }
}
