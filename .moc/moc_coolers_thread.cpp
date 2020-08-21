/****************************************************************************
** Meta object code from reading C++ file 'coolers_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coolers_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coolers_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_COOLERS_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   16,   15,   15, 0x05,
      60,   36,   15,   15, 0x05,
     111,   99,   15,   15, 0x05,
     140,   15,   15,   15, 0x05,
     161,  154,   15,   15, 0x05,
     192,  180,   15,   15, 0x05,
     229,  215,   15,   15, 0x05,
     256,   15,   15,   15, 0x05,
     274,   15,   15,   15, 0x05,
     292,   15,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_COOLERS_THREAD[] = {
    "COOLERS_THREAD\0\0on\0sigSetMain(bool)\0"
    "n_cooler,on,temperature\0"
    "sigSetTemperature(quint32,bool,double)\0"
    "temperature\0sigSetExtTemperature(double)\0"
    "sigSetReset()\0manual\0sigSetManual(bool)\0"
    "n_cooler,on\0sigSetOn(quint32,bool)\0"
    "n_cooler,freq\0sigSetFreq(quint32,double)\0"
    "sigRefreshState()\0sigStartMonitor()\0"
    "sigStopMonitor()\0"
};

void COOLERS_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        COOLERS_THREAD *_t = static_cast<COOLERS_THREAD *>(_o);
        switch (_id) {
        case 0: _t->sigSetMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigSetTemperature((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->sigSetExtTemperature((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->sigSetReset(); break;
        case 4: _t->sigSetManual((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->sigSetOn((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->sigSetFreq((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: _t->sigRefreshState(); break;
        case 8: _t->sigStartMonitor(); break;
        case 9: _t->sigStopMonitor(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData COOLERS_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject COOLERS_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_COOLERS_THREAD,
      qt_meta_data_COOLERS_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &COOLERS_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *COOLERS_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *COOLERS_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_COOLERS_THREAD))
        return static_cast<void*>(const_cast< COOLERS_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int COOLERS_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void COOLERS_THREAD::sigSetMain(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void COOLERS_THREAD::sigSetTemperature(quint32 _t1, bool _t2, double _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void COOLERS_THREAD::sigSetExtTemperature(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void COOLERS_THREAD::sigSetReset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void COOLERS_THREAD::sigSetManual(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void COOLERS_THREAD::sigSetOn(quint32 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void COOLERS_THREAD::sigSetFreq(quint32 _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void COOLERS_THREAD::sigRefreshState()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void COOLERS_THREAD::sigStartMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void COOLERS_THREAD::sigStopMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
