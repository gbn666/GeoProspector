#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QWidget>

namespace Ui {
class visualizer;
}

class visualizer : public QWidget
{
    Q_OBJECT

public:
    explicit visualizer(QWidget *parent = 0);
    ~visualizer();

private slots:
    void on_pushButton_clicked();

private:
    Ui::visualizer *ui;
};

#endif // VISUALIZER_H
