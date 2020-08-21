/****************************************************************************
** Meta object code from reading C++ file 'coretemp_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coretemp_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coretemp_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CORETEMP_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   17,   16,   16, 0x05,
      37,   16,   16,   16, 0x05,
      55,   16,   16,   16, 0x05,
      76,   16,   16,   16, 0x05,
      94,   16,   16,   16, 0x05,
     112,   16,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CORETEMP_THREAD[] = {
    "CORETEMP_THREAD\0\0on\0sigSetMain(bool)\0"
    "sigConnectedGpr()\0sigDisconnectedGpr()\0"
    "sigRefreshState()\0sigStartMonitor()\0"
    "sigStopMonitor()\0"
};

void CORETEMP_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CORETEMP_THREAD *_t = static_cast<CORETEMP_THREAD *>(_o);
        switch (_id) {
        case 0: _t->sigSetMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigConnectedGpr(); break;
        case 2: _t->sigDisconnectedGpr(); break;
        case 3: _t->sigRefreshState(); break;
        case 4: _t->sigStartMonitor(); break;
        case 5: _t->sigStopMonitor(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CORETEMP_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CORETEMP_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CORETEMP_THREAD,
      qt_meta_data_CORETEMP_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CORETEMP_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CORETEMP_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CORETEMP_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CORETEMP_THREAD))
        return static_cast<void*>(const_cast< CORETEMP_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int CORETEMP_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CORETEMP_THREAD::sigSetMain(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CORETEMP_THREAD::sigConnectedGpr()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CORETEMP_THREAD::sigDisconnectedGpr()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CORETEMP_THREAD::sigRefreshState()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void CORETEMP_THREAD::sigStartMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void CORETEMP_THREAD::sigStopMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
