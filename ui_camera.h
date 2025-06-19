/********************************************************************************
** Form generated from reading UI file 'camera.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_camera
{
public:
    QLabel *cameraLabel;
    QPushButton *startButton;

    void setupUi(QWidget *camera)
    {
        if (camera->objectName().isEmpty())
            camera->setObjectName(QStringLiteral("camera"));
        camera->resize(800, 480);
        cameraLabel = new QLabel(camera);
        cameraLabel->setObjectName(QStringLiteral("cameraLabel"));
        cameraLabel->setGeometry(QRect(0, 0, 640, 480));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy);
        startButton = new QPushButton(camera);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(650, 190, 80, 25));

        retranslateUi(camera);

        QMetaObject::connectSlotsByName(camera);
    } // setupUi

    void retranslateUi(QWidget *camera)
    {
        camera->setWindowTitle(QApplication::translate("camera", "Form", 0));
        cameraLabel->setText(QString());
        startButton->setText(QApplication::translate("camera", "\346\222\255\346\224\276", 0));
    } // retranslateUi

};

namespace Ui {
    class camera: public Ui_camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
