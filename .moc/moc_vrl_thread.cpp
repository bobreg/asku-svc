/****************************************************************************
** Meta object code from reading C++ file 'vrl_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vrl_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vrl_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VRL_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   12,   11,   11, 0x05,
      32,   12,   11,   11, 0x05,
      57,   11,   11,   11, 0x05,
      75,   11,   11,   11, 0x05,
      96,   11,   11,   11, 0x05,
     120,  114,   11,   11, 0x05,
     143,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_VRL_THREAD[] = {
    "VRL_THREAD\0\0on\0sigSetMain(bool)\0"
    "sigSetDisableTotal(bool)\0sigConnectedGpr()\0"
    "sigDisconnectedGpr()\0sigRefreshState()\0"
    "n_vrl\0sigSetMainVRL(quint32)\0"
    "sigSetDisableReconf(bool)\0"
};

void VRL_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VRL_THREAD *_t = static_cast<VRL_THREAD *>(_o);
        switch (_id) {
        case 0: _t->sigSetMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigSetDisableTotal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sigConnectedGpr(); break;
        case 3: _t->sigDisconnectedGpr(); break;
        case 4: _t->sigRefreshState(); break;
        case 5: _t->sigSetMainVRL((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->sigSetDisableReconf((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VRL_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VRL_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_VRL_THREAD,
      qt_meta_data_VRL_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VRL_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VRL_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VRL_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VRL_THREAD))
        return static_cast<void*>(const_cast< VRL_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int VRL_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void VRL_THREAD::sigSetMain(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VRL_THREAD::sigSetDisableTotal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VRL_THREAD::sigConnectedGpr()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void VRL_THREAD::sigDisconnectedGpr()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void VRL_THREAD::sigRefreshState()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void VRL_THREAD::sigSetMainVRL(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VRL_THREAD::sigSetDisableReconf(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
