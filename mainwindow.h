#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "visualizer.h"
#include "camera.h"
#include "camerathread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onGasUpdate(int gasValue);
    void onDistanceUpdate(float dist);
    void onLightUpdate(int lightVal);
    void onTempHumUpdate(float temperature, float humidity);


    void onLightDetected(const QString &info);
    void onLedTriggered();

public slots:
    void on_viewButton_clicked();
    void onFrameReady(unsigned char *rgbBuffer);
    void displayFrame(unsigned char *buffer);
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    cameraThread *camThread;  // 相机线程对象
     visualizer *vis = nullptr;
};

#endif // MAINWINDOW_H
