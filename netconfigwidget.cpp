#include "netconfigwidget.h"
#include "ui_netconfigwidget.h"
#include <QMessageBox>
#include <QThread>
#include <QDebug>

NetConfigWidget::NetConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetConfigWidget),
    m_port(new WzSerialPort)
{
    ui->setupUi(this);

    // 波特率下拉
    ui->cbxBuad->addItems(
        {"9600", "19200", "38400", "57600", "115200", "230400"});
    ui->cbxBuad->setCurrentText("115200");
    ui->cbxDataBit->setCurrentText("8");
    ui->cbxJybit->setCurrentIndex(0);
}

NetConfigWidget::~NetConfigWidget()
{
    delete ui;
}

void NetConfigWidget::on_btnOpen_clicked()
{
    if (!m_isOpen) {
        QString serialName = ui->leSerialName->text().trimmed();
        if (serialName.isEmpty()) {
            QMessageBox::critical(this, tr("错误"), tr("串口名称不能为空"));
            return;
        }

        if (!m_port->open(
              serialName.toStdString().c_str(),
              ui->cbxBuad->currentText().toInt(),
              0, 8, 1))
        {
            qDebug() << "Failed to open serial port: " << serialName;
            QMessageBox::critical(this, tr("错误"), tr("串口打开失败：%1").arg(serialName));
            return;
        }
        m_isOpen = true;
        ui->btnOpen->setText(tr("关闭"));
        ui->leSerialName->setDisabled(true);
        ui->cbxBuad->setDisabled(true);
        ui->cbxDataBit->setDisabled(true);
        ui->cbxJybit->setDisabled(true);
        ui->cbxStopBit->setDisabled(true);
        QMessageBox::information(this, tr("提示"), tr("串口打开成功"));
    } else {
        m_port->close();
        m_isOpen = false;
        ui->btnOpen->setText(tr("打开"));
        ui->leSerialName->setEnabled(true);
        ui->cbxBuad->setEnabled(true);
        ui->cbxDataBit->setEnabled(true);
        ui->cbxJybit->setEnabled(true);
        ui->cbxStopBit->setEnabled(true);
        QMessageBox::information(this, tr("提示"), tr("串口已关闭"));
    }
}

bool NetConfigWidget::sendATCommand(const QByteArray &cmd,
                                    const QStringList &expected,
                                    int timeoutMs,
                                    int retry)
{
    qDebug() << "NetConfigWidget::sendATCommand run: " << cmd.trimmed();
    for (int attempt = 0; attempt < retry; ++attempt) {
        qDebug() << "Attempt " << attempt + 1 << " of " << retry;
        clearSerialBuffer();
        if (!m_port->send(cmd.constData(), cmd.size())) {
            qDebug() << "Send failed: " << cmd.trimmed();
            continue;
        }

        QByteArray resp;
        int elapsed = 0;
        const int interval = 100; // 每 100ms 轮询
        while (elapsed < timeoutMs) {
            QThread::msleep(interval);
            elapsed += interval;

            char buf[512];
            int len = m_port->receive(buf, sizeof(buf));
            if (len > 0) {
                resp.append(buf, len);
                qDebug() << "Received: " << resp.trimmed();
                for (auto &exp : expected) {
                    if (resp.contains(exp.toUtf8())) {
                        qDebug() << "CMD " << cmd.trimmed() << " => " << resp.trimmed();
                        return true;
                    }
                }
                if (resp.contains("ERROR") || resp.contains("FAIL")) {
                    qDebug() << "CMD " << cmd.trimmed() << " => " << resp.trimmed() << " (ERROR)";
                    return false;
                }
            }
        }
        qDebug() << "Timeout for " << cmd.trimmed() << " resp: " << resp.trimmed();
    }
    return false;
}

void NetConfigWidget::clearSerialBuffer()
{
    char discard[512];
    int len;
    while ((len = m_port->receive(discard, sizeof(discard))) > 0) {
        qDebug() << "Cleared buffer: " << QByteArray(discard, len).trimmed();
    }
}

bool NetConfigWidget::exitTransparentMode()
{
    qDebug() << "Attempting to exit transparent mode";
    // 发送 +++ 以退出透传模式
    QByteArray cmd = "+++";
    if (!m_port->send(cmd.constData(), cmd.size())) {
        qDebug() << "Failed to send +++";
        return false;
    }
    QThread::msleep(1000); // 等待 1 秒
    clearSerialBuffer();
    // 检查是否回到命令模式
    return sendATCommand("AT\r\n", {"OK"}, 1000, 2);
}

void NetConfigWidget::on_btnSetNet_clicked()
{
    if (!m_isOpen) {
        QMessageBox::warning(this, tr("警告"), tr("请先打开串口"));
        return;
    }

    // 收集参数并验证
    const QString ssid = ui->leWifiName->text().trimmed();
    const QString pwd = ui->leWifiPasswd->text().trimmed();
    const QString host = ui->leWifiAddr->text().trimmed();
    const QString port = ui->leWifiPort->text().trimmed();

    if (ssid.isEmpty() || pwd.isEmpty() || host.isEmpty() || port.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请填写所有字段"));
        return;
    }

    // 1. 尝试退出透传模式
    if (!exitTransparentMode()) {
        qDebug() << "Failed to exit transparent mode, attempting to proceed";
    }

    // 2. 测试 AT 链路
    if (!sendATCommand("AT\r\n", {"OK"}, 1000, 3)) {
        // 尝试其他波特率
        QList<int> baudRates = {9600, 38400, 57600, 115200, 230400};
        for (int baud : baudRates) {
            qDebug() << "Trying baud rate: " << baud;
            m_port->close();
            if (m_port->open(ui->leSerialName->text().toStdString().c_str(), baud, 0, 8, 1)) {
                if (sendATCommand("AT\r\n", {"OK"}, 1000, 2)) {
                    qDebug() << "Success with baud rate: " << baud;
                    ui->cbxBuad->setCurrentText(QString::number(baud));
                    m_isOpen = true;
                    break;
                }
                m_port->close();
            }
        }
        if (!m_isOpen) {
            QMessageBox::critical(this, tr("错误"), tr("模块无响应 (AT)，请检查串口连接或波特率"));
            return;
        }
    }

    // 3. 重启模块并等待 ready
    if (!sendATCommand("AT+RST\r\n", {"ready"}, 5000, 1)) {
        QMessageBox::warning(this, tr("警告"), tr("未检测到 ready，继续"));
    }
    QThread::msleep(5000); // 等待模块完全启动

    // 4. 检查是否已连接到 WiFi
    if (sendATCommand("AT+CWJAP?\r\n", {"+CWJAP:"}, 2000, 2)) {
        qDebug() << "WiFi already connected, skipping AT+CWJAP";
    } else {
        // 5. 设置工作模式为 Station
        if (!sendATCommand("AT+CWMODE=1\r\n", {"OK", "no change"}, 1000, 2)) {
            QMessageBox::critical(this, tr("错误"), tr("设置工作模式失败"));
            return;
        }

        // 6. 连接 WiFi
        if (!sendATCommand(QString("AT+CWJAP=\"%1\",\"%2\"\r\n").arg(ssid).arg(pwd).toUtf8(),
                           {"OK", "WIFI GOT IP"}, 20000, 1)) {
            QMessageBox::critical(this, tr("错误"), tr("连接 WiFi 失败，请检查 SSID/密码"));
            return;
        }
    }

    // 7. 查询 IP 地址
    if (!sendATCommand("AT+CIFSR\r\n", {"STAIP"}, 2000, 2)) {
        QMessageBox::warning(this, tr("警告"), tr("无法获取 IP 地址"));
        return;
    }

    // 8. 连接 TCP 服务器
    if (!sendATCommand(QString("AT+CIPSTART=\"TCP\",\"%1\",%2\r\n").arg(host).arg(port).toUtf8(),
                       {"OK", "ALREADY CONNECT"}, 5000, 2)) {
        QMessageBox::critical(this, tr("错误"), tr("连接服务器失败"));
        return;
    }

    // 9. 进入透传模式
    if (!sendATCommand("AT+CIPMODE=1\r\n", {"OK"}, 1000, 2)) {
        QMessageBox::critical(this, tr("错误"), tr("设置透传模式失败"));
        return;
    }
    if (!sendATCommand("AT+CIPSEND\r\n", {">"}, 2000, 2)) {
        QMessageBox::critical(this, tr("错误"), tr("启动透传失败"));
        return;
    }

    // 配置成功
    QMessageBox::information(this, tr("提示"), tr("网络配置成功"));
    emit serverConfigured(host, port);
    emit returnToMainWindow();
}

void NetConfigWidget::on_pushButton_clicked()
{
    emit returnToMainWindow();
}
