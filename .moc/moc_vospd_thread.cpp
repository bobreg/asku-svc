/****************************************************************************
** Meta object code from reading C++ file 'vospd_thread.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vospd_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vospd_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOSPD_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   14,   13,   13, 0x05,
      42,   34,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_VOSPD_THREAD[] = {
    "VOSPD_THREAD\0\0on\0sigSetMain(bool)\0"
    "channel\0sigChangedAzimuthSource(quint32)\0"
};

void VOSPD_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VOSPD_THREAD *_t = static_cast<VOSPD_THREAD *>(_o);
        switch (_id) {
        case 0: _t->sigSetMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sigChangedAzimuthSource((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VOSPD_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VOSPD_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_VOSPD_THREAD,
      qt_meta_data_VOSPD_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOSPD_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOSPD_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOSPD_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOSPD_THREAD))
        return static_cast<void*>(const_cast< VOSPD_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int VOSPD_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VOSPD_THREAD::sigSetMain(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VOSPD_THREAD::sigChangedAzimuthSource(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
