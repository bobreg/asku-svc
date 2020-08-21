/****************************************************************************
** Meta object code from reading C++ file 'vrl_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vrl_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vrl_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VRL_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x05,
      45,   13,   12,   12, 0x05,
      68,   12,   12,   12, 0x05,
      91,   86,   12,   12, 0x05,
     135,  116,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     187,   12,   12,   12, 0x09,
     218,  197,   12,   12, 0x09,
     268,  265,   12,   12, 0x0a,
     288,  282,   12,   12, 0x0a,
     308,  265,   12,   12, 0x0a,
     330,  265,   12,   12, 0x0a,
     353,   12,   12,   12, 0x0a,
     370,   12,   12,   12, 0x0a,
     385,   12,   12,   12, 0x0a,
     403,   12,   12,   12, 0x0a,
     424,   12,   12,   12, 0x0a,
     439,   12,   12,   12, 0x0a,
     453,   12,   12,   12, 0x0a,
     467,  116,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VRL_SERVICE[] = {
    "VRL_SERVICE\0\0state\0sigState(AskuBinStateSet)\0"
    "sigKoeff(AskuValueSet)\0sigChangedState()\0"
    "info\0sigVrlState(QVariantMap)\0"
    "config,state,koeff\0"
    "sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "timeout()\0data,haFrom,portFrom\0"
    "onDataArrived(QByteArray,QHostAddress,quint16)\0"
    "on\0setMain(bool)\0n_vrl\0setMainVRL(quint32)\0"
    "setDisableTotal(bool)\0setDisableReconf(bool)\0"
    "setAutoMainVRL()\0onRefreshVrl()\0"
    "setConnectedGpr()\0setDisconnectedGpr()\0"
    "startMonitor()\0stopMonitor()\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
};

void VRL_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VRL_SERVICE *_t = static_cast<VRL_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 1: _t->sigKoeff((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 2: _t->sigChangedState(); break;
        case 3: _t->sigVrlState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 4: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 5: _t->timeout(); break;
        case 6: _t->onDataArrived((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 7: _t->setMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setMainVRL((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 9: _t->setDisableTotal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setDisableReconf((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->setAutoMainVRL(); break;
        case 12: _t->onRefreshVrl(); break;
        case 13: _t->setConnectedGpr(); break;
        case 14: _t->setDisconnectedGpr(); break;
        case 15: _t->startMonitor(); break;
        case 16: _t->stopMonitor(); break;
        case 17: _t->syncToSlave(); break;
        case 18: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VRL_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VRL_SERVICE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VRL_SERVICE,
      qt_meta_data_VRL_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VRL_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VRL_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VRL_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VRL_SERVICE))
        return static_cast<void*>(const_cast< VRL_SERVICE*>(this));
    return QObject::qt_metacast(_clname);
}

int VRL_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void VRL_SERVICE::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VRL_SERVICE::sigKoeff(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VRL_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void VRL_SERVICE::sigVrlState(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VRL_SERVICE::sigSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
