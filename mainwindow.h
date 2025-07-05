#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "camerathread.h"
#include "dht11thread.h"
#include "dataprocessthread.h"
#include "serialcomm.h"
#include "imageuploader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateDHT11Display(const QString &tempInt,
                            const QString &tempFrac,
                            const QString &humidity);
    void displayFrame(const QImage &img);
    void on_viewButton_clicked();
    void on_startButton_clicked();
    void on_saveButton_clicked();
    void on_recognitionButton_clicked();
    void on_wifiButton_clicked();

    // 来自 DataProcessThread
    void onGasUpdate(int gasValue);
    void onDistanceUpdate(float dist);
    void onLightDetected(const QString &info);
    void onTempHumDetected(float temperature, float humidity);

    // 来自 NetConfigWidget
    void onServerConfigured(const QString &host, const QString &port);

private:
    Ui::MainWindow *ui;

    cameraThread *camThread;
    DHT11Thread  *dhtThread;
    QImage        m_lastFrame;

    QString       m_serverHost;
    QString       m_serverPort;
    QString m_ssid;
    QString m_password;

    SerialComm   *m_serial;
};

#endif // MAINWINDOW_H
