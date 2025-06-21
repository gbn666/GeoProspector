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
    char stringdata[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 8),
QT_MOC_LITERAL(4, 33, 16),
QT_MOC_LITERAL(5, 50, 4),
QT_MOC_LITERAL(6, 55, 13),
QT_MOC_LITERAL(7, 69, 8),
QT_MOC_LITERAL(8, 78, 15),
QT_MOC_LITERAL(9, 94, 11),
QT_MOC_LITERAL(10, 106, 8),
QT_MOC_LITERAL(11, 115, 15),
QT_MOC_LITERAL(12, 131, 4),
QT_MOC_LITERAL(13, 136, 14),
QT_MOC_LITERAL(14, 151, 21),
QT_MOC_LITERAL(15, 173, 12),
QT_MOC_LITERAL(16, 186, 14),
QT_MOC_LITERAL(17, 201, 9),
QT_MOC_LITERAL(18, 211, 12),
QT_MOC_LITERAL(19, 224, 6),
QT_MOC_LITERAL(20, 231, 22)
    },
    "MainWindow\0onGasUpdate\0\0gasValue\0"
    "onDistanceUpdate\0dist\0onLightUpdate\0"
    "lightVal\0onTempHumUpdate\0temperature\0"
    "humidity\0onLightDetected\0info\0"
    "onLedTriggered\0on_viewButton_clicked\0"
    "onFrameReady\0unsigned char*\0rgbBuffer\0"
    "displayFrame\0buffer\0on_startButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       6,    1,   70,    2, 0x0a /* Public */,
       8,    2,   73,    2, 0x0a /* Public */,
      11,    1,   78,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,
      14,    0,   82,    2, 0x0a /* Public */,
      15,    1,   83,    2, 0x0a /* Public */,
      18,    1,   86,    2, 0x0a /* Public */,
      20,    0,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   19,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->onGasUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onDistanceUpdate((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->onLightUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onTempHumUpdate((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->onLightDetected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onLedTriggered(); break;
        case 6: _t->on_viewButton_clicked(); break;
        case 7: _t->onFrameReady((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 8: _t->displayFrame((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 9: _t->on_startButton_clicked(); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
