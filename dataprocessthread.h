#ifndef DATAPROCESSTHREAD_H
#define DATAPROCESSTHREAD_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "dataprocess.h"

class DataProcessThread : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessThread(ProcessMode mode, QObject *parent = nullptr);
    ~DataProcessThread();

signals:
    void gasWarning(int);
    void distanceWarning(float);
    void lightDetected(QString);
   void tempHumDetected(float temperature, float humidity);
    void ledBuzzerTriggered();

public slots:
    void start();
    void stop();
    void process();

private:
    ProcessMode m_mode;
    bool m_running;
    QTimer *m_timer;
    QThread m_thread;

    void initDrivers();
    void loadDriver(const QString &path);

signals:
    void finished();
};

#endif // DATAPROCESSTHREAD_H
