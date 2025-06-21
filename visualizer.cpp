#include "visualizer.h"
#include "ui_visualizer.h"

visualizer::visualizer(MainWindow *mainWin, QWidget *parent)
    : QWidget(parent), ui(new Ui::visualizer), m_mainWin(mainWin)
{
    ui->setupUi(this);
}

visualizer::~visualizer()
{
    delete ui;
}

void visualizer::on_pushButton_clicked()
{
    emit returnToMainWindow();
}


