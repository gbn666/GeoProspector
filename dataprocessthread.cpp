#include "dataprocessthread.h"
#include <QTimer>
#include <QDebug>
#include <unistd.h>

DataProcessThread::DataProcessThread(ProcessMode mode, QObject *parent)
    : QObject(parent)
    , m_mode(mode)
    , m_running(false)
{
    // 第一次创建线程时加载内核驱动
    initDrivers();

    moveToThread(&m_thread);
    connect(&m_thread, &QThread::started, this, &DataProcessThread::start);
    connect(this, &DataProcessThread::finished, &m_thread, &QThread::quit);
    connect(&m_thread, &QThread::finished, this, &QObject::deleteLater);
}

DataProcessThread::~DataProcessThread() {
    stop();
    m_thread.wait();
}

void DataProcessThread::initDrivers() {
    // 使用 QProcess 加载驱动，如果已加载会失败，可忽略错误
    auto load = [&](const QString &path) {
        int ret = QProcess::execute("insmod", QStringList() << path);
        if (ret != 0) {
            qDebug() << "Driver already loaded or failed:" << path;
        } else {
            qDebug() << "Loaded driver:" << path;
        }
    };

    // 根据实际路径修改以下驱动文件位置
    load("/vendor/test/module/BH1750/driver/BH1750_driver.ko");
    load("/vendor/test/module/ULTRASONIC/driver/US_driver.ko");
    load("/vendor/test/module/GAS/driver/GAS_driver.ko");
    load("/vendor/test/module/LED_BUZZER/driver/LEDBuzzer_driver.ko");
    load("/vendor/test/module/TEMP_HUMID/driver/TH_driver.ko");
}

void DataProcessThread::start() {
    if (m_running) return;
    m_running = true;
    QTimer *timer = new QTimer;
    timer->moveToThread(&m_thread);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &DataProcessThread::process);
    connect(this, &DataProcessThread::finished, timer, &QTimer::stop);
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
    case ProcessMode::BroadGas: {
        int gas = DataProcess(static_cast<int>(ProcessMode::BroadGas));
        emit gasWarning(gas);
        break;
    }
    case ProcessMode::Ultrasonic: {
        float dist = DataProcess(static_cast<int>(ProcessMode::Ultrasonic));
        emit distanceWarning(dist);
        break;
    }
    case ProcessMode::LedBuzzer: {
        WarnnigGas(0);
        emit ledBuzzerTriggered();
        break;
    }
    case ProcessMode::LightLevel: {
        int light = DataProcess(static_cast<int>(ProcessMode::LightLevel));
        emit lightDetected(QString::number(light));
        break;
    }
    case ProcessMode::TempHumidity: {
        int th = DataProcess(static_cast<int>(ProcessMode::TempHumidity));
        emit tempHumDetected(QString::number(th));
        break;
    }
    default:
        break;
    }
}
