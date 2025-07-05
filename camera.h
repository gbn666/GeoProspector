// camera.h
#pragma once

#include <QWidget>
#include <QImage>
#include <QPushButton>
#include "camerathread.h"
#include "ui_camera.h"

class camera : public QWidget {
    Q_OBJECT

public:
    explicit camera(QWidget *parent = nullptr);
    ~camera() override;

private slots:
    void errorshowslot();
    void videoDisplay(const QImage &frame);
    void on_startButton_clicked();

signals:
    void Show_complete();

private:
    Ui::camera *ui;
    cameraThread *camerathread;
    bool cameraflag = false;
};
