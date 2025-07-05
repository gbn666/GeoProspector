/********************************************************************************
** Form generated from reading UI file 'netconfigwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETCONFIGWIDGET_H
#define UI_NETCONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetConfigWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_6;
    QLineEdit *leSerialName;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_9;
    QComboBox *cbxDataBit;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_10;
    QComboBox *cbxStopBit;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_11;
    QComboBox *cbxBuad;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_12;
    QComboBox *cbxJybit;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOpen;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *leWifiName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *leWifiPasswd;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *leWifiAddr;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *leWifiPort;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *cbxMode;
    QPushButton *btnSetNet;
    QPushButton *pushButton;

    void setupUi(QWidget *NetConfigWidget)
    {
        if (NetConfigWidget->objectName().isEmpty())
            NetConfigWidget->setObjectName(QStringLiteral("NetConfigWidget"));
        NetConfigWidget->resize(800, 430);
        verticalLayout_4 = new QVBoxLayout(NetConfigWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_3 = new QGroupBox(NetConfigWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_13->addWidget(label_6);

        leSerialName = new QLineEdit(groupBox_3);
        leSerialName->setObjectName(QStringLiteral("leSerialName"));

        horizontalLayout_13->addWidget(leSerialName);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(80, 0));
        label_9->setMaximumSize(QSize(80, 16777215));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_9);

        cbxDataBit = new QComboBox(groupBox_3);
        cbxDataBit->setObjectName(QStringLiteral("cbxDataBit"));

        horizontalLayout_14->addWidget(cbxDataBit);


        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(80, 0));
        label_10->setMaximumSize(QSize(80, 16777215));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(label_10);

        cbxStopBit = new QComboBox(groupBox_3);
        cbxStopBit->setObjectName(QStringLiteral("cbxStopBit"));

        horizontalLayout_15->addWidget(cbxStopBit);


        verticalLayout_2->addLayout(horizontalLayout_15);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(80, 0));
        label_11->setMaximumSize(QSize(80, 16777215));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(label_11);

        cbxBuad = new QComboBox(groupBox_3);
        cbxBuad->setObjectName(QStringLiteral("cbxBuad"));

        horizontalLayout_16->addWidget(cbxBuad);


        verticalLayout_3->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(80, 0));
        label_12->setMaximumSize(QSize(80, 16777215));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(label_12);

        cbxJybit = new QComboBox(groupBox_3);
        cbxJybit->setObjectName(QStringLiteral("cbxJybit"));

        horizontalLayout_17->addWidget(cbxJybit);


        verticalLayout_3->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer);

        btnOpen = new QPushButton(groupBox_3);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));

        horizontalLayout_18->addWidget(btnOpen);


        verticalLayout_3->addLayout(horizontalLayout_18);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(NetConfigWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(80, 0));
        label->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(label);

        leWifiName = new QLineEdit(groupBox_2);
        leWifiName->setObjectName(QStringLiteral("leWifiName"));

        horizontalLayout_2->addWidget(leWifiName);


        horizontalLayout_9->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(80, 0));
        label_2->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(label_2);

        leWifiPasswd = new QLineEdit(groupBox_2);
        leWifiPasswd->setObjectName(QStringLiteral("leWifiPasswd"));

        horizontalLayout_3->addWidget(leWifiPasswd);


        horizontalLayout_9->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(80, 0));
        label_3->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(label_3);

        leWifiAddr = new QLineEdit(groupBox_2);
        leWifiAddr->setObjectName(QStringLiteral("leWifiAddr"));

        horizontalLayout_4->addWidget(leWifiAddr);


        horizontalLayout_10->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(label_4);

        leWifiPort = new QLineEdit(groupBox_2);
        leWifiPort->setObjectName(QStringLiteral("leWifiPort"));

        horizontalLayout->addWidget(leWifiPort);


        horizontalLayout_10->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(80, 0));
        label_5->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_5->addWidget(label_5);

        cbxMode = new QComboBox(groupBox_2);
        cbxMode->setObjectName(QStringLiteral("cbxMode"));

        horizontalLayout_5->addWidget(cbxMode);


        horizontalLayout_11->addLayout(horizontalLayout_5);

        btnSetNet = new QPushButton(groupBox_2);
        btnSetNet->setObjectName(QStringLiteral("btnSetNet"));

        horizontalLayout_11->addWidget(btnSetNet);


        verticalLayout->addLayout(horizontalLayout_11);


        verticalLayout_4->addWidget(groupBox_2);

        pushButton = new QPushButton(NetConfigWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_4->addWidget(pushButton);


        retranslateUi(NetConfigWidget);

        QMetaObject::connectSlotsByName(NetConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *NetConfigWidget)
    {
        NetConfigWidget->setWindowTitle(QApplication::translate("NetConfigWidget", "Form", 0));
        groupBox_3->setTitle(QApplication::translate("NetConfigWidget", "\344\270\262\345\217\243\350\256\276\347\275\256", 0));
        label_6->setText(QApplication::translate("NetConfigWidget", "\344\270\262\345\217\243\345\217\267\357\274\232", 0));
        leSerialName->setText(QApplication::translate("NetConfigWidget", "/dev/ttymxc1", 0));
        label_9->setText(QApplication::translate("NetConfigWidget", "\346\225\260\346\215\256\344\275\215\357\274\232", 0));
        cbxDataBit->clear();
        cbxDataBit->insertItems(0, QStringList()
         << QApplication::translate("NetConfigWidget", "8", 0)
         << QApplication::translate("NetConfigWidget", "5", 0)
         << QApplication::translate("NetConfigWidget", "6", 0)
         << QApplication::translate("NetConfigWidget", "7", 0)
        );
        label_10->setText(QApplication::translate("NetConfigWidget", "\345\201\234\346\255\242\344\275\215\357\274\232", 0));
        cbxStopBit->clear();
        cbxStopBit->insertItems(0, QStringList()
         << QApplication::translate("NetConfigWidget", "1", 0)
         << QApplication::translate("NetConfigWidget", "2", 0)
         << QApplication::translate("NetConfigWidget", "1.5", 0)
        );
        label_11->setText(QApplication::translate("NetConfigWidget", "\346\263\242\347\211\271\347\216\207\357\274\232", 0));
        label_12->setText(QApplication::translate("NetConfigWidget", "\346\240\241\351\252\214\344\275\215\357\274\232", 0));
        cbxJybit->clear();
        cbxJybit->insertItems(0, QStringList()
         << QApplication::translate("NetConfigWidget", "NoParity", 0)
         << QApplication::translate("NetConfigWidget", "EvenParity", 0)
         << QApplication::translate("NetConfigWidget", "OddParity", 0)
         << QApplication::translate("NetConfigWidget", "SpaceParity", 0)
         << QApplication::translate("NetConfigWidget", "MarkParity", 0)
        );
        btnOpen->setText(QApplication::translate("NetConfigWidget", "\346\211\223\345\274\200", 0));
        groupBox_2->setTitle(QApplication::translate("NetConfigWidget", "wifi\351\205\215\347\275\256", 0));
        label->setText(QApplication::translate("NetConfigWidget", "WIFI\345\220\215\347\247\260", 0));
        leWifiName->setText(QApplication::translate("NetConfigWidget", "FAN", 0));
        label_2->setText(QApplication::translate("NetConfigWidget", "WIFI\345\257\206\347\240\201", 0));
        leWifiPasswd->setText(QApplication::translate("NetConfigWidget", "12345678", 0));
        label_3->setText(QApplication::translate("NetConfigWidget", "IP\345\234\260\345\235\200", 0));
        leWifiAddr->setText(QApplication::translate("NetConfigWidget", "192.168.137.97", 0));
        label_4->setText(QApplication::translate("NetConfigWidget", "\347\253\257\345\217\243\345\217\267", 0));
        leWifiPort->setText(QApplication::translate("NetConfigWidget", "3333", 0));
        label_5->setText(QApplication::translate("NetConfigWidget", "\346\250\241\345\274\217\351\200\211\346\213\251", 0));
        cbxMode->clear();
        cbxMode->insertItems(0, QStringList()
         << QApplication::translate("NetConfigWidget", "STA", 0)
         << QApplication::translate("NetConfigWidget", "AP", 0)
         << QApplication::translate("NetConfigWidget", "\346\267\267\345\220\210\346\250\241\345\274\217", 0)
        );
        cbxMode->setCurrentText(QApplication::translate("NetConfigWidget", "STA", 0));
        btnSetNet->setText(QApplication::translate("NetConfigWidget", "\351\205\215\347\275\256\347\275\221\347\273\234", 0));
        pushButton->setText(QApplication::translate("NetConfigWidget", "\350\277\224\345\233\236\344\270\273\351\241\265\351\235\242", 0));
    } // retranslateUi

};

namespace Ui {
    class NetConfigWidget: public Ui_NetConfigWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETCONFIGWIDGET_H
