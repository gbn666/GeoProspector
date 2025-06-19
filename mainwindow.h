#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <visualizer.h>
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
    void on_pushButton_clicked();
    void onFrameReady(unsigned char *rgbBuffer);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
