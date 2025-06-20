#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <visualizer.h>
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

private slots:
    void on_viewButton_clicked();
    void onFrameReady(unsigned char *rgbBuffer);
    void displayFrame(unsigned char *buffer);

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
     cameraThread *camThread;  // 成员变量声明
};

#endif // MAINWINDOW_H
