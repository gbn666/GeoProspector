#include "serialcomm.h"
#include <QDebug>
#include <QThread>

SerialComm::SerialComm(QObject *parent)
    : QObject(parent),
      m_timer(new QTimer(this)),
      m_isPortOpen(false)
{
    connect(m_timer, &QTimer::timeout, this, &SerialComm::onPoll);
}

SerialComm::~SerialComm()
{
    m_timer->stop();
    if (m_isPortOpen) {
        m_port.close();
    }
}

bool SerialComm::openPort(const char *portName, int baudRate,
                          int parity, int dataBits, int stopBits)
{
    bool ok = m_port.open(portName, baudRate, parity, dataBits, stopBits);
    if (!ok) {
        emitError(QString("打开串口失败: %1").arg(portName));
        return false;
    }
    m_isPortOpen = true;
    m_timer->start(50);  // 每 50ms 轮询一次接收
    return true;
}

void SerialComm::closePort()
{
    m_timer->stop();
    m_port.close();
    m_isPortOpen = false;
}

int SerialComm::send(const char *data, int len)
{
    if (!m_isPortOpen) {
        emitError("串口未打开");
        return 0;
    }

    int totalWritten = 0;
    while (totalWritten < len) {
        int written = m_port.send(data + totalWritten, len - totalWritten);
        if (written <= 0) {
            emitError("串口写入失败或写入为0");
            break;
        }
        totalWritten += written;

        // 可选：让串口缓冲器有时间写完，避免溢出
        QThread::msleep(5);
    }

    return totalWritten;
}


void SerialComm::onPoll()
{
    if (!m_isPortOpen) return;

    char buf[512];
    int n = m_port.receive(buf, sizeof(buf));
    if (n < 0) {
        emitError("串口读取错误");
        return;
    }
    if (n == 0) {
        // 当前无数据，静默
        return;
    }
    m_buffer.append(buf, n);

    // 按行分发
    int idx;
    while ((idx = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(idx+1);
        m_buffer.remove(0, idx+1);
        emit lineReceived(line.trimmed());
    }
}

void SerialComm::emitError(const QString &err)
{
    qDebug() << "[SerialComm] Error:" << err;
    emit errorOccurred(err);
}
