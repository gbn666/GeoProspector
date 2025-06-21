#include "dataprocessthread.h"
#include <QTimer>
#include <QDebug>
#include <QProcess>



DataProcessThread::DataProcessThread(ProcessMode mode, QObject *parent)
    : QObject(parent), m_mode(mode), m_running(false)
{
    initDrivers();

    moveToThread(&m_thread);
    connect(&m_thread, &QThread::started, this, &DataProcessThread::start);
    connect(this, &DataProcessThread::finished, &m_thread, &QThread::quit);
    connect(&m_thread, &QThread::finished, this, &DataProcessThread::deleteLater);

    m_thread.start();  // ⚠️ 不要忘记启动线程！
}

DataProcessThread::~DataProcessThread() {
    stop();
    m_thread.quit();
    m_thread.wait();
}

void DataProcessThread::loadDriver(const QString &path) {
    QStringList args; args << path;
    int ret = QProcess::execute("insmod", args);
    if (ret != 0) {
        qDebug() << "Driver already loaded or failed:" << path;
    } else {
        qDebug() << "Loaded driver:" << path;
    }
}

void DataProcessThread::initDrivers() {
    loadDriver("/home/root/vendor/BH1750_driver.ko");
    loadDriver("/home/root/vendor/HCSR04_driver.ko");
    loadDriver("/home/root/vendor/MQ2_driver.ko");
    loadDriver("/home/root/vendor/LEDBuzzer_driver.ko");
    loadDriver("/home/root/vendor/DHT11_driver.ko");
}

void DataProcessThread::start() {
    if (m_running) return;
    m_running = true;

    m_timer = new QTimer(this);  // this在线程中，没问题
    connect(m_timer, &QTimer::timeout, this, &DataProcessThread::process);
    m_timer->start(1000); // 每秒触发一次
}

void DataProcessThread::stop() {
    if (!m_running) return;
    m_running = false;
    if (m_timer) {
        m_timer->stop();
        m_timer->deleteLater();
        m_timer = nullptr;
    }
    emit finished();
}


void DataProcessThread::process() {
    if (!m_running) return;

    switch (m_mode) {
    case BroadGas: {
        int gas = DataProcess(BroadGas);
        emit gasWarning(gas);
        break;
    }
    case Ultrasonic: {
        float dist = DataProcess(Ultrasonic);
        emit distanceWarning(dist / 100.0f);
        break;
    }
    case LightLevel: {
        int light = DataProcess(LightLevel);
        emit lightDetected(QString::number(light));
        break;
    }
    case TempHumidity: {
        int result = DataProcess(TempHumidity);
        if (result == 0) {
            qWarning() << "TempHumidity data invalid, result = 0";
            break;
        }

        float temperature = (result / 10000) / 100.0f;
        float humidity = (result % 10000) / 100.0f;

        if (temperature < 0 || temperature > 50 || humidity < 20 || humidity > 90) {
            qWarning() << "TempHumidity out of range: Temp =" << temperature << "C, Humi =" << humidity << "%";
            break;
        }

        qDebug() << "Temperature:" << temperature << "C, Humidity:" << humidity << "%";
        emit tempHumDetected(temperature, humidity);
        break;
    }
    case LEDBuzzer: {
        int buz = DataProcess(LEDBuzzer);
        if (buz) emit ledBuzzerTriggered();
        break;
    }
    default:
        break;
    }
}
