/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 12),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 3),
QT_MOC_LITERAL(4, 29, 21),
QT_MOC_LITERAL(5, 51, 22),
QT_MOC_LITERAL(6, 74, 21),
QT_MOC_LITERAL(7, 96, 28),
QT_MOC_LITERAL(8, 125, 21),
QT_MOC_LITERAL(9, 147, 11),
QT_MOC_LITERAL(10, 159, 8),
QT_MOC_LITERAL(11, 168, 16),
QT_MOC_LITERAL(12, 185, 4),
QT_MOC_LITERAL(13, 190, 15),
QT_MOC_LITERAL(14, 206, 4),
QT_MOC_LITERAL(15, 211, 17),
QT_MOC_LITERAL(16, 229, 11),
QT_MOC_LITERAL(17, 241, 8),
QT_MOC_LITERAL(18, 250, 18),
QT_MOC_LITERAL(19, 269, 4),
QT_MOC_LITERAL(20, 274, 4)
    },
    "MainWindow\0displayFrame\0\0img\0"
    "on_viewButton_clicked\0on_startButton_clicked\0"
    "on_saveButton_clicked\0"
    "on_recognitionButton_clicked\0"
    "on_wifiButton_clicked\0onGasUpdate\0"
    "gasValue\0onDistanceUpdate\0dist\0"
    "onLightDetected\0info\0onTempHumDetected\0"
    "temperature\0humidity\0onServerConfigured\0"
    "host\0port"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    0,   72,    2, 0x08 /* Private */,
       5,    0,   73,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      11,    1,   80,    2, 0x08 /* Private */,
      13,    1,   83,    2, 0x08 /* Private */,
      15,    2,   86,    2, 0x08 /* Private */,
      18,    2,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   16,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->displayFrame((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->on_viewButton_clicked(); break;
        case 2: _t->on_startButton_clicked(); break;
        case 3: _t->on_saveButton_clicked(); break;
        case 4: _t->on_recognitionButton_clicked(); break;
        case 5: _t->on_wifiButton_clicked(); break;
        case 6: _t->onGasUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onDistanceUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->onLightDetected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->onTempHumDetected((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 10: _t->onServerConfigured((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
