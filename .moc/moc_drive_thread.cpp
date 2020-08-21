/****************************************************************************
** Meta object code from reading C++ file 'drive_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../drive_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drive_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DRIVE_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   14,   13,   13, 0x05,
      34,   13,   13,   13, 0x05,
      52,   13,   13,   13, 0x05,
      73,   13,   13,   13, 0x05,
      91,   13,   13,   13, 0x05,
     109,   13,   13,   13, 0x05,
     126,   13,   13,   13, 0x05,
     147,  140,   13,   13, 0x05,
     174,  166,   13,   13, 0x05,
     195,  166,   13,   13, 0x05,
     225,  219,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DRIVE_THREAD[] = {
    "DRIVE_THREAD\0\0on\0sigSetMain(bool)\0"
    "sigConnectedGpr()\0sigDisconnectedGpr()\0"
    "sigRefreshState()\0sigStartMonitor()\0"
    "sigStopMonitor()\0sigSetReset()\0manual\0"
    "sigSetManual(bool)\0n_drive\0"
    "sigSetServo(quint32)\0sigSetOverride(quint32)\0"
    "speed\0sigSetSpeed(double)\0"
};

void DRIVE_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DRIVE_THREAD *_t = static_cast<DRIVE_THREAD *>(_o);
        switch (_id) {
        case 0: _t->sigSetMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigConnectedGpr(); break;
        case 2: _t->sigDisconnectedGpr(); break;
        case 3: _t->sigRefreshState(); break;
        case 4: _t->sigStartMonitor(); break;
        case 5: _t->sigStopMonitor(); break;
        case 6: _t->sigSetReset(); break;
        case 7: _t->sigSetManual((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sigSetServo((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 9: _t->sigSetOverride((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 10: _t->sigSetSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DRIVE_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DRIVE_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DRIVE_THREAD,
      qt_meta_data_DRIVE_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DRIVE_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DRIVE_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DRIVE_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DRIVE_THREAD))
        return static_cast<void*>(const_cast< DRIVE_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int DRIVE_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DRIVE_THREAD::sigSetMain(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DRIVE_THREAD::sigConnectedGpr()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void DRIVE_THREAD::sigDisconnectedGpr()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DRIVE_THREAD::sigRefreshState()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void DRIVE_THREAD::sigStartMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void DRIVE_THREAD::sigStopMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void DRIVE_THREAD::sigSetReset()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void DRIVE_THREAD::sigSetManual(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DRIVE_THREAD::sigSetServo(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DRIVE_THREAD::sigSetOverride(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void DRIVE_THREAD::sigSetSpeed(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
