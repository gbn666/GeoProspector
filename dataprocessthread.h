// dataprocessthread.h
#ifndef DATAPROCESSTHREAD_H
#define DATAPROCESSTHREAD_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "dataprocess.h"
#include <sys/ioctl.h>   // for ioctl
#include <fcntl.h>
#include <unistd.h>

// 直接对应驱动中的 IOCTL_BUZZER_ON = 4, IOCTL_BUZZER_OFF = 3
#define BUZZER_ON   4
#define BUZZER_OFF  3

class DataProcessThread : public QObject
{
    Q_OBJECT

public:
    explicit DataProcessThread(ProcessMode mode, QObject *parent = nullptr);
    ~DataProcessThread();
    void start();

signals:
    void gasWarning(int);
    void distanceWarning(float);
    void lightDetected(const QString &);
    void tempHumDetected(float temperature, float humidity);
    void finished();

private slots:

    void process();
    void triggerBuzzer();

private:
    void stop();
    void initDrivers();
    void loadDriver(const QString &path);
    int calculateBuzzerInterval(float dist);

    ProcessMode m_mode;
    bool        m_running;
    QTimer     *m_timer;
    QTimer     *buzzerTimer;
    QThread     m_thread;
    int         buzzerFd;
    float       lastDist;
};

#endif // DATAPROCESSTHREAD_H
