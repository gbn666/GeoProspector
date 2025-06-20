/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *labelImage;
    QLabel *titlelabel;
    QPushButton *viewButton;
    QPushButton *saveButton;
    QPushButton *pushButton;
    QPushButton *lightButton;
    QPushButton *temperButton;
    QPushButton *gasButton;
    QLabel *viewlabel;
    QPushButton *startButton;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelImage = new QLabel(centralWidget);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(160, 10, 30, 29));
        labelImage->setMinimumSize(QSize(30, 29));
        labelImage->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/logo")));
        labelImage->setScaledContents(false);
        labelImage->setWordWrap(false);
        titlelabel = new QLabel(centralWidget);
        titlelabel->setObjectName(QStringLiteral("titlelabel"));
        titlelabel->setGeometry(QRect(200, 0, 400, 41));
        QFont font;
        font.setFamily(QStringLiteral("AR PL UKai CN"));
        font.setPointSize(21);
        font.setBold(true);
        font.setWeight(75);
        titlelabel->setFont(font);
        viewButton = new QPushButton(centralWidget);
        viewButton->setObjectName(QStringLiteral("viewButton"));
        viewButton->setGeometry(QRect(290, 70, 120, 40));
        QFont font1;
        font1.setFamily(QStringLiteral("AR PL UKai CN"));
        font1.setPointSize(17);
        viewButton->setFont(font1);
        viewButton->setDefault(false);
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(500, 70, 120, 40));
        saveButton->setFont(font1);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(530, 160, 120, 40));
        pushButton->setFont(font1);
        lightButton = new QPushButton(centralWidget);
        lightButton->setObjectName(QStringLiteral("lightButton"));
        lightButton->setGeometry(QRect(530, 220, 120, 40));
        lightButton->setFont(font1);
        temperButton = new QPushButton(centralWidget);
        temperButton->setObjectName(QStringLiteral("temperButton"));
        temperButton->setGeometry(QRect(530, 280, 120, 40));
        temperButton->setFont(font1);
        gasButton = new QPushButton(centralWidget);
        gasButton->setObjectName(QStringLiteral("gasButton"));
        gasButton->setGeometry(QRect(530, 340, 120, 40));
        gasButton->setFont(font1);
        viewlabel = new QLabel(centralWidget);
        viewlabel->setObjectName(QStringLiteral("viewlabel"));
        viewlabel->setGeometry(QRect(10, 110, 480, 360));
        viewlabel->setAlignment(Qt::AlignCenter);
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(80, 70, 120, 40));
        startButton->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(680, 160, 121, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(680, 220, 101, 41));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(680, 280, 111, 41));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(680, 340, 91, 41));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        labelImage->setText(QString());
        titlelabel->setText(QApplication::translate("MainWindow", "\346\231\272\350\203\275\345\214\226\351\207\216\345\244\226\345\234\260\350\264\250\345\213\230\346\216\242\347\216\257\345\242\203\347\233\221\346\265\213\344\273\252", 0));
        viewButton->setText(QApplication::translate("MainWindow", "\345\217\257\350\247\206\345\214\226", 0));
        saveButton->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\277\235\345\255\230", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\350\266\205\345\243\260\346\263\242\346\265\213\350\267\235", 0));
        lightButton->setText(QApplication::translate("MainWindow", "\345\205\211\347\205\247\345\274\272\345\272\246", 0));
        temperButton->setText(QApplication::translate("MainWindow", "\346\270\251\346\271\277\345\272\246", 0));
        gasButton->setText(QApplication::translate("MainWindow", "\345\271\277\350\260\261\346\260\224\344\275\223", 0));
        viewlabel->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\347\224\273\351\235\242", 0));
        startButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\347\233\221\346\265\213", 0));
        label_3->setText(QApplication::translate("MainWindow", "data1", 0));
        label_4->setText(QApplication::translate("MainWindow", "data2", 0));
        label_5->setText(QApplication::translate("MainWindow", "data3", 0));
        label_6->setText(QApplication::translate("MainWindow", "data4", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
