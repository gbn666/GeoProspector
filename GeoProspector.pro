#-------------------------------------------------
#
# Project created by QtCreator 2025-06-16T00:30:03
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
target.path=/home/
INSTALLS+=target
TARGET = GeoProspector
TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    visualizer.cpp \
    camerathread.cpp \
    camera.cpp \
    dataprocess.cpp \
    dataprocessthread.cpp


HEADERS += \
        mainwindow.h \
    visualizer.h \
    camerathread.h \
    camera.h \
    ui_camera.h \
    device.h \
    dataprocess.h \
    dataprocessthread.h


FORMS += \
        mainwindow.ui \
    visualizer.ui

DISTFILES += \
    resources/logo

RESOURCES += \
    images.qrc \
    images.qrc
