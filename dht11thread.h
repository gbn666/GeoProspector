#ifndef DHT11THREAD_H
#define DHT11THREAD_H

#include <QThread>
#include <QString>

/**
 * @brief DHT11Thread
 * 持续从 /dev/DHT11 读取温湿度数据，并通过 newTempHum 信号发出。
 */
class DHT11Thread : public QThread
{
    Q_OBJECT
public:
    explicit DHT11Thread(QObject *parent = nullptr);

signals:
    /**
     * @param tempInt   温度整数部分
     * @param tempFrac  温度小数部分
     * @param humidity  湿度整数部分
     */
    void newTempHum(const QString &tempInt,
                    const QString &tempFrac,
                    const QString &humidity);

protected:
    void run() override;
};

#endif // DHT11THREAD_H
