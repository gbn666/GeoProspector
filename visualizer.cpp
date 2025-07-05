#include "visualizer.h"
#include "ui_visualizer.h"

visualizer::visualizer(MainWindow *mainWin, QWidget *parent)
    : QWidget(parent), ui(new Ui::visualizer), m_mainWin(mainWin)
{
    ui->setupUi(this);
//    QMovie* movie1 = new QMovie(":/../桌面/plot.gif");
////    ui->label->setMovie(movie1);
//    movie1->setCacheMode(QMovie::CacheAll);
//    ui->label_2->resize(400,400);
//    ui->label_2->setMovie(movie1);
////    movie1->start();
///
}

visualizer::~visualizer()
{
    delete ui;
}

void visualizer::on_pushButton_clicked()
{
    emit returnToMainWindow();
}


