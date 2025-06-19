#include "visualizer.h"
#include "ui_visualizer.h"
#include "mainwindow.h"

visualizer::visualizer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::visualizer)
{
    ui->setupUi(this);

}

visualizer::~visualizer()
{
    delete ui;
}

void visualizer::on_pushButton_clicked()
{
    this->close();
    MainWindow *ui=new MainWindow;
    ui->show();

}
