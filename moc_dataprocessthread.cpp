/****************************************************************************
** Meta object code from reading C++ file 'dataprocessthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dataprocessthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataprocessthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataProcessThread_t {
    QByteArrayData data[13];
    char stringdata[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataProcessThread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataProcessThread_t qt_meta_stringdata_DataProcessThread = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 10),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 15),
QT_MOC_LITERAL(4, 46, 13),
QT_MOC_LITERAL(5, 60, 15),
QT_MOC_LITERAL(6, 76, 11),
QT_MOC_LITERAL(7, 88, 8),
QT_MOC_LITERAL(8, 97, 18),
QT_MOC_LITERAL(9, 116, 8),
QT_MOC_LITERAL(10, 125, 5),
QT_MOC_LITERAL(11, 131, 4),
QT_MOC_LITERAL(12, 136, 7)
    },
    "DataProcessThread\0gasWarning\0\0"
    "distanceWarning\0lightDetected\0"
    "tempHumDetected\0temperature\0humidity\0"
    "ledBuzzerTriggered\0finished\0start\0"
    "stop\0process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataProcessThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,
       4,    1,   65,    2, 0x06 /* Public */,
       5,    2,   68,    2, 0x06 /* Public */,
       8,    0,   73,    2, 0x06 /* Public */,
       9,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   75,    2, 0x0a /* Public */,
      11,    0,   76,    2, 0x0a /* Public */,
      12,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    6,    7,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DataProcessThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataProcessThread *_t = static_cast<DataProcessThread *>(_o);
        switch (_id) {
        case 0: _t->gasWarning((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->distanceWarning((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->lightDetected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->tempHumDetected((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->ledBuzzerTriggered(); break;
        case 5: _t->finished(); break;
        case 6: _t->start(); break;
        case 7: _t->stop(); break;
        case 8: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataProcessThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataProcessThread::gasWarning)) {
                *result = 0;
            }
        }
        {
            typedef void (DataProcessThread::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataProcessThread::distanceWarning)) {
                *result = 1;
            }
        }
        {
            typedef void (DataProcessThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataProcessThread::lightDetected)) {
                *result = 2;
            }
        }
        {
            typedef void (DataProcessThread::*_t)(float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataProcessThread::tempHumDetected)) {
                *result = 3;
            }
        }
        {
            typedef void (DataProcessThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataProcessThread::ledBuzzerTriggered)) {
                *result = 4;
            }
        }
        {
            typedef void (DataProcessThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataProcessThread::finished)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject DataProcessThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataProcessThread.data,
      qt_meta_data_DataProcessThread,  qt_static_metacall, 0, 0}
};


const QMetaObject *DataProcessThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataProcessThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataProcessThread.stringdata))
        return static_cast<void*>(const_cast< DataProcessThread*>(this));
    return QObject::qt_metacast(_clname);
}

int DataProcessThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DataProcessThread::gasWarning(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataProcessThread::distanceWarning(float _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataProcessThread::lightDetected(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataProcessThread::tempHumDetected(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DataProcessThread::ledBuzzerTriggered()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void DataProcessThread::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
