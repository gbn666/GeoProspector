/********************************************************************************
** Form generated from reading UI file 'visualizer.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALIZER_H
#define UI_VISUALIZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_visualizer
{
public:
    QLabel *label;
    QLabel *imagelabel1;
    QPushButton *pushButton;
    QLabel *label_2;
    QLineEdit *lineEdit;

    void setupUi(QWidget *visualizer)
    {
        if (visualizer->objectName().isEmpty())
            visualizer->setObjectName(QStringLiteral("visualizer"));
        visualizer->resize(800, 480);
        label = new QLabel(visualizer);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(310, 10, 200, 40));
        QFont font;
        font.setFamily(QStringLiteral("AR PL UKai CN"));
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        imagelabel1 = new QLabel(visualizer);
        imagelabel1->setObjectName(QStringLiteral("imagelabel1"));
        imagelabel1->setGeometry(QRect(300, 10, 30, 29));
        imagelabel1->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/logo")));
        pushButton = new QPushButton(visualizer);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(680, 390, 89, 25));
        label_2 = new QLabel(visualizer);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 90, 300, 300));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/\346\241\214\351\235\242/2025-06-22 09-52-31\345\261\217\345\271\225\346\210\252\345\233\276.png")));
        lineEdit = new QLineEdit(visualizer);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(380, 200, 361, 51));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        lineEdit->setFont(font1);

        retranslateUi(visualizer);

        QMetaObject::connectSlotsByName(visualizer);
    } // setupUi

    void retranslateUi(QWidget *visualizer)
    {
        visualizer->setWindowTitle(QApplication::translate("visualizer", "Form", 0));
        label->setText(QApplication::translate("visualizer", "\345\217\257\350\247\206\345\214\226\346\225\260\346\215\256", 0));
        imagelabel1->setText(QString());
        pushButton->setText(QApplication::translate("visualizer", "\350\277\224\345\233\236\344\270\273\351\241\265\351\235\242", 0));
        label_2->setText(QString());
        lineEdit->setText(QApplication::translate("visualizer", "   \350\266\205\345\243\260\346\263\242\346\265\213\350\267\235\345\212\250\346\200\201\345\217\257\350\247\206\345\214\226\345\261\225\347\244\272", 0));
    } // retranslateUi

};

namespace Ui {
    class visualizer: public Ui_visualizer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALIZER_H
