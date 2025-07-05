#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QObject>
#include <QTimer>
#include <QByteArray>
#include "WzSerialPort.h"  // 你的底层串口驱动类

class SerialComm : public QObject
{
    Q_OBJECT
public:
    explicit SerialComm(QObject *parent = nullptr);
    ~SerialComm();

    bool openPort(const char *portName, int baudRate,
                  int parity = 0, int dataBits = 8, int stopBits = 1);
    void closePort();
    bool isOpen() const { return m_isPortOpen; }

    // 直接发送数据块，返回实际写入字节数
    int send(const char *data, int len);

signals:
    void lineReceived(const QByteArray &line);
    void errorOccurred(const QString &error);

private slots:
    void onPoll();

private:
    void emitError(const QString &err);

    WzSerialPort  m_port;
    QTimer       *m_timer;
    bool          m_isPortOpen;
    QByteArray    m_buffer;
};

#endif // SERIALCOMM_H
