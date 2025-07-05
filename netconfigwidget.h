#ifndef NETCONFIGWIDGET_H
#define NETCONFIGWIDGET_H

#include <QWidget>
#include "WzSerialPort.h"

namespace Ui {
class NetConfigWidget;
}

class NetConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NetConfigWidget(QWidget *parent = nullptr);
    ~NetConfigWidget();

signals:
    void serverConfigured(const QString &host, const QString &port);
    void returnToMainWindow();

private slots:
    void on_btnOpen_clicked();
    void on_btnSetNet_clicked();
    void on_pushButton_clicked();

private:
    bool sendATCommand(const QByteArray &cmd, const QStringList &expected, int timeoutMs, int retry);
    void clearSerialBuffer();
    bool exitTransparentMode(); // 声明 exitTransparentMode 函数

    Ui::NetConfigWidget *ui;
    WzSerialPort *m_port;
    bool m_isOpen = false;
};

#endif // NETCONFIGWIDGET_H
