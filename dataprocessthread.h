#ifndef DATAPROCESSTHREAD_H
#define DATAPROCESSTHREAD_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include "dataprocess.h"

// 线程模式：涵盖所有设备（C++03 兼容）
enum ProcessMode {
    None = 0,
    BroadGas = 1,        // 广谱气体
    Ultrasonic = 2,      // 超声波测距
    LedBuzzer = 3,       // LED 蜂鸣器
    LightLevel = 4,      // 光照强度
    TempHumidity = 5     // 温湿度传感器
};

class DataProcessThread : public QObject {
    Q_OBJECT
public:
    // C++03 不支持 nullptr，去掉默认参数
    explicit DataProcessThread(ProcessMode mode, QObject *parent);
    ~DataProcessThread();

public slots:
    void start();
    void stop();

signals:
    void gasWarning(int gasValue);
    void distanceWarning(float distance);
    void ledBuzzerTriggered();
    void lightDetected(const QString &info);
    void tempHumDetected(const QString &info);
    void finished();

private slots:
    void process();

private:
    void initDrivers();          // 驱动加载
    void loadDriver(const QString &path);

    QThread      m_thread;
    ProcessMode  m_mode;
    bool         m_running;
};

#endif // DATAPROCESSTHREAD_H
