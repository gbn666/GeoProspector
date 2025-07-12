// dataprocessthread.cpp
#include "dataprocessthread.h"
#include <QProcess>
#include <QDebug>
#include <cstring>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

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
        const QString samplePath = "/vendor/test/module/DHT11/test/DHT11_test";

        // 检查可执行
        if (!QFile::exists(samplePath) || !QFileInfo(samplePath).isExecutable()) {
            qWarning() << "[DHT11] 样例程序不存在或不可执行：" << samplePath;
            break;
        }

        // 启动样例程序
        QProcess proc;
        proc.setProcessChannelMode(QProcess::MergedChannels);
        proc.start("stdbuf", QStringList{ "-oL", samplePath });

        if (!proc.waitForStarted(500)) {
            qWarning() << "[DHT11] 启动样例失败：" << proc.errorString();
            break;
        }

        // 等待样例程序第一次输出——sleep(2)+printf 后
        if (!proc.waitForReadyRead(4000)) {
            qWarning() << "[DHT11] 样例未在 4s 内输出";
            proc.kill();
            proc.waitForFinished(200);
            break;
        }

        // 读取一行
        QByteArray line = proc.readLine().trimmed();
        // 杀掉后台循环
        proc.kill();
        proc.waitForFinished(200);

        qDebug() << "[DHT11 sample] raw line =" << line;

        // 用 UTF-8 解码（根据你板子实际编码也可以试 fromLocal8Bit）
        QString out = QString::fromUtf8(line);
        qDebug() << "[DHT11 sample] 解码后 =" << out;

        // 正则提取数字
        QRegularExpression re(R"(Temp\s*:\s*(\d+)\.(\d+)℃,\s*Humi\s*:\s*(\d+)%RH)");
        auto match = re.match(out);
        if (match.hasMatch()) {
            float temperature = match.captured(1).toFloat()
                              + match.captured(2).toFloat() / 10.0f;
            float humidity    = match.captured(3).toFloat();
            emit tempHumDetected(temperature, humidity);
        } else {
            qWarning() << "[DHT11] 输出格式不匹配";
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
