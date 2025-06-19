#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "visualizer.h"
#include "ui_visualizer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("可视化");



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
    visualizer *ui=new visualizer;
    ui->show();






}
