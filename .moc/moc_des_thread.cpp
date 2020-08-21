/****************************************************************************
** Meta object code from reading C++ file 'des_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../des_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'des_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DES_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   12,   11,   11, 0x05,
      32,   11,   11,   11, 0x05,
      50,   11,   11,   11, 0x05,
      68,   11,   11,   11, 0x05,
      94,   85,   11,   11, 0x05,
     130,  121,   11,   11, 0x05,
     156,   85,   11,   11, 0x05,
     182,   85,   11,   11, 0x05,
     214,  208,   11,   11, 0x05,
     246,  240,   11,   11, 0x05,
     280,  269,   11,   11, 0x05,
     324,  313,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DES_THREAD[] = {
    "DES_THREAD\0\0on\0sigSetMain(bool)\0"
    "sigRefreshState()\0sigStartMonitor()\0"
    "sigStopMonitor()\0n_mns,on\0"
    "sigSetEngine(quint32,bool)\0n_dgs,on\0"
    "sigSetPosGB(quint32,bool)\0"
    "sigSetPosMB(quint32,bool)\0"
    "sigSetPosTB(quint32,bool)\0n_mns\0"
    "sigSetMainsReset(quint32)\0n_dgs\0"
    "sigSetDgReset(quint32)\0n_mns,mode\0"
    "sigSetMainsMode(quint32,quint32)\0"
    "n_dgs,mode\0sigSetDgMode(quint32,quint32)\0"
};

void DES_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DES_THREAD *_t = static_cast<DES_THREAD *>(_o);
        switch (_id) {
        case 0: _t->sigSetMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigRefreshState(); break;
        case 2: _t->sigStartMonitor(); break;
        case 3: _t->sigStopMonitor(); break;
        case 4: _t->sigSetEngine((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->sigSetPosGB((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->sigSetPosMB((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->sigSetPosTB((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->sigSetMainsReset((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 9: _t->sigSetDgReset((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 10: _t->sigSetMainsMode((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 11: _t->sigSetDgMode((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DES_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DES_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DES_THREAD,
      qt_meta_data_DES_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DES_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DES_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DES_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DES_THREAD))
        return static_cast<void*>(const_cast< DES_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int DES_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void DES_THREAD::sigSetMain(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DES_THREAD::sigRefreshState()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void DES_THREAD::sigStartMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DES_THREAD::sigStopMonitor()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void DES_THREAD::sigSetEngine(quint32 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DES_THREAD::sigSetPosGB(quint32 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DES_THREAD::sigSetPosMB(quint32 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DES_THREAD::sigSetPosTB(quint32 _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DES_THREAD::sigSetMainsReset(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DES_THREAD::sigSetDgReset(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void DES_THREAD::sigSetMainsMode(quint32 _t1, quint32 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void DES_THREAD::sigSetDgMode(quint32 _t1, quint32 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
