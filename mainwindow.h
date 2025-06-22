#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "camera.h"
#include "camerathread.h"
#include "visualizer.h"
#include "dataprocess.h"
#include "dataprocessthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGasUpdate(int gasValue);
    void onDistanceUpdate(float dist);
    void onLightUpdate(int lightVal);
    void onTempHumUpdate(float temperature, float humidity);
    void onLightDetected(const QString &info);
    void onLedTriggered();
    void displayFrame(unsigned char *buffer);
    void onFrameReady(unsigned char *rgbBuffer);
    void on_viewButton_clicked();
    void on_startButton_clicked();
    void updateDHT11Display(int tempInt, int tempFrac, int humidity);

private:
    class DHT11Thread : public QThread
    {
    public:
        explicit DHT11Thread(MainWindow *parent);
        void run() override;

    private:
        MainWindow *m_parent;
    };

    Ui::MainWindow *ui;
    cameraThread *camThread;
    DHT11Thread *dhtThread;
};

#endif // MAINWINDOW_H
