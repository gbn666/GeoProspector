#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QWidget>
#include <QMovie>
#include <QPixmap>

class MainWindow;  // 前向声明主窗口类

namespace Ui {
class visualizer;
}

class visualizer : public QWidget
{
    Q_OBJECT

public:
    // 构造函数接收主窗口指针，parent 用于 Qt 对象树
    explicit visualizer(MainWindow *mainWin, QWidget *parent = nullptr);
    ~visualizer();

private slots:
    // 返回主窗口槽
    void on_pushButton_clicked();

signals:
    void returnToMainWindow();
private:
    Ui::visualizer *ui;
    MainWindow *m_mainWin;  // 保存主窗口指针以便返回时调用
};

#endif // VISUALIZER_H
