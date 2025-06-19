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
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *labelImage;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menutest;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelImage = new QLabel(centralWidget);
        labelImage->setObjectName(QStringLiteral("labelImage"));
        labelImage->setGeometry(QRect(300, 10, 30, 29));
        labelImage->setMinimumSize(QSize(30, 29));
        labelImage->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/logo")));
        labelImage->setScaledContents(false);
        labelImage->setWordWrap(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(340, 0, 411, 41));
        QFont font;
        font.setFamily(QStringLiteral("AR PL UKai CN"));
        font.setPointSize(21);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(440, 80, 120, 40));
        QFont font1;
        font1.setFamily(QStringLiteral("AR PL UKai CN"));
        font1.setPointSize(17);
        pushButton->setFont(font1);
        pushButton->setDefault(false);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(610, 80, 120, 40));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(440, 190, 120, 40));
        pushButton_3->setFont(font1);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(610, 190, 120, 40));
        pushButton_4->setFont(font1);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(440, 300, 120, 40));
        pushButton_5->setFont(font1);
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(610, 300, 120, 40));
        pushButton_6->setFont(font1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 70, 300, 300));
        label_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 28));
        menutest = new QMenu(menuBar);
        menutest->setObjectName(QStringLiteral("menutest"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menutest->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        labelImage->setText(QString());
        label->setText(QApplication::translate("MainWindow", "\346\231\272\350\203\275\345\214\226\351\207\216\345\244\226\345\234\260\350\264\250\345\213\230\346\216\242\347\216\257\345\242\203\347\233\221\346\265\213\344\273\252", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\345\217\257\350\247\206\345\214\226", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\277\235\345\255\230", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "\350\266\205\345\243\260\346\263\242\346\265\213\350\267\235", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\345\205\211\347\205\247\345\274\272\345\272\246", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "\346\270\251\346\271\277\345\272\246", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "\345\271\277\350\260\261\346\260\224\344\275\223", 0));
        label_2->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\347\224\273\351\235\242", 0));
        menutest->setTitle(QApplication::translate("MainWindow", "test", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
