/********************************************************************************
** Form generated from reading UI file 'wifi.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIFI_H
#define UI_WIFI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label_7;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(720, 480);
        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 20, 30, 29));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/logo")));
        label_2 = new QLabel(Form);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(330, 20, 121, 30));
        QFont font;
        font.setFamily(QStringLiteral("AR PL UKai CN"));
        font.setPointSize(16);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(Form);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 90, 121, 60));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(180, 110, 113, 25));
        lineEdit->setFont(font);
        label_4 = new QLabel(Form);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 180, 121, 60));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);
        lineEdit_2 = new QLineEdit(Form);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 200, 113, 25));
        lineEdit_2->setFont(font);
        label_5 = new QLabel(Form);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 270, 121, 60));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        lineEdit_3 = new QLineEdit(Form);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(180, 290, 113, 25));
        lineEdit_3->setFont(font);
        label_6 = new QLabel(Form);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(400, 100, 121, 60));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);
        comboBox = new QComboBox(Form);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(530, 120, 86, 25));
        label_7 = new QLabel(Form);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(400, 180, 121, 60));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);
        lineEdit_4 = new QLineEdit(Form);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(530, 200, 113, 25));
        lineEdit_4->setFont(font);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("Form", "\347\275\221\347\273\234\351\205\215\347\275\256", 0));
        label_3->setText(QApplication::translate("Form", "WIFI\345\220\215\347\247\260", 0));
        label_4->setText(QApplication::translate("Form", "WIFI\345\257\206\347\240\201", 0));
        label_5->setText(QApplication::translate("Form", "IP\345\234\260\345\235\200", 0));
        label_6->setText(QApplication::translate("Form", "\346\250\241\345\274\217\351\200\211\346\213\251", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Form", "AP", 0)
         << QApplication::translate("Form", "STA", 0)
        );
        label_7->setText(QApplication::translate("Form", "\347\253\257\345\217\243\345\217\267", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIFI_H
