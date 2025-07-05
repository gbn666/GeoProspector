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
    QByteArrayData data[24];
    char stringdata[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 18),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 7),
QT_MOC_LITERAL(4, 39, 8),
QT_MOC_LITERAL(5, 48, 8),
QT_MOC_LITERAL(6, 57, 12),
QT_MOC_LITERAL(7, 70, 3),
QT_MOC_LITERAL(8, 74, 21),
QT_MOC_LITERAL(9, 96, 22),
QT_MOC_LITERAL(10, 119, 21),
QT_MOC_LITERAL(11, 141, 28),
QT_MOC_LITERAL(12, 170, 21),
QT_MOC_LITERAL(13, 192, 11),
QT_MOC_LITERAL(14, 204, 8),
QT_MOC_LITERAL(15, 213, 16),
QT_MOC_LITERAL(16, 230, 4),
QT_MOC_LITERAL(17, 235, 15),
QT_MOC_LITERAL(18, 251, 4),
QT_MOC_LITERAL(19, 256, 17),
QT_MOC_LITERAL(20, 274, 11),
QT_MOC_LITERAL(21, 286, 18),
QT_MOC_LITERAL(22, 305, 4),
QT_MOC_LITERAL(23, 310, 4)
    },
    "MainWindow\0updateDHT11Display\0\0tempInt\0"
    "tempFrac\0humidity\0displayFrame\0img\0"
    "on_viewButton_clicked\0on_startButton_clicked\0"
    "on_saveButton_clicked\0"
    "on_recognitionButton_clicked\0"
    "on_wifiButton_clicked\0onGasUpdate\0"
    "gasValue\0onDistanceUpdate\0dist\0"
    "onLightDetected\0info\0onTempHumDetected\0"
    "temperature\0onServerConfigured\0host\0"
    "port"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   74,    2, 0x08 /* Private */,
       6,    1,   81,    2, 0x08 /* Private */,
       8,    0,   84,    2, 0x08 /* Private */,
       9,    0,   85,    2, 0x08 /* Private */,
      10,    0,   86,    2, 0x08 /* Private */,
      11,    0,   87,    2, 0x08 /* Private */,
      12,    0,   88,    2, 0x08 /* Private */,
      13,    1,   89,    2, 0x08 /* Private */,
      15,    1,   92,    2, 0x08 /* Private */,
      17,    1,   95,    2, 0x08 /* Private */,
      19,    2,   98,    2, 0x08 /* Private */,
      21,    2,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   20,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,   23,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->updateDHT11Display((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->displayFrame((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 2: _t->on_viewButton_clicked(); break;
        case 3: _t->on_startButton_clicked(); break;
        case 4: _t->on_saveButton_clicked(); break;
        case 5: _t->on_recognitionButton_clicked(); break;
        case 6: _t->on_wifiButton_clicked(); break;
        case 7: _t->onGasUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onDistanceUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->onLightDetected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->onTempHumDetected((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->onServerConfigured((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
