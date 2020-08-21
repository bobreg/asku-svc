/****************************************************************************
** Meta object code from reading C++ file 'des_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../des_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'des_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DES_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      36,   31,   12,   12, 0x05,
      66,   61,   12,   12, 0x05,
     100,   94,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     126,   12,   12,   12, 0x09,
     140,   12,   12,   12, 0x09,
     162,   12,  157,   12, 0x09,
     172,   12,  157,   12, 0x09,
     181,   12,   12,   12, 0x09,
     205,  200,   12,   12, 0x0a,
     234,  225,   12,   12, 0x0a,
     258,  225,   12,   12, 0x0a,
     290,  281,   12,   12, 0x0a,
     313,  281,   12,   12, 0x0a,
     342,  336,   12,   12, 0x0a,
     371,  365,   12,   12, 0x0a,
     402,  391,   12,   12, 0x0a,
     443,  432,   12,   12, 0x0a,
     470,   12,   12,   12, 0x0a,
     485,   12,   12,   12, 0x0a,
     500,   12,   12,   12, 0x0a,
     514,   12,   12,   12, 0x0a,
     528,   61,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DES_SERVICE[] = {
    "DES_SERVICE\0\0sigChangedState()\0info\0"
    "sigDesState(QVariantMap)\0data\0"
    "sigSyncToSlave(QVariantMap)\0state\0"
    "sigState(AskuBinStateSet)\0onConnected()\0"
    "onDisconnected()\0bool\0onQuery()\0"
    "onLive()\0setFirstCommands()\0main\0"
    "onChangedMain(bool)\0n_dgs,on\0"
    "setEngine(quint32,bool)\0setPosGB(quint32,bool)\0"
    "n_mns,on\0setPosMB(quint32,bool)\0"
    "setPosTB(quint32,bool)\0n_mns\0"
    "setMainsReset(quint32)\0n_dgs\0"
    "setDgReset(quint32)\0n_mns,mode\0"
    "setMainsMode(quint32,quint32)\0n_dgs,mode\0"
    "setDgMode(quint32,quint32)\0onRefreshDes()\0"
    "startMonitor()\0stopMonitor()\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap)\0"
};

void DES_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DES_SERVICE *_t = static_cast<DES_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigChangedState(); break;
        case 1: _t->sigDesState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 2: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 4: _t->onConnected(); break;
        case 5: _t->onDisconnected(); break;
        case 6: { bool _r = _t->onQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->onLive();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: _t->setFirstCommands(); break;
        case 9: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setEngine((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->setPosGB((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->setPosMB((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->setPosTB((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->setMainsReset((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 15: _t->setDgReset((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 16: _t->setMainsMode((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 17: _t->setDgMode((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 18: _t->onRefreshDes(); break;
        case 19: _t->startMonitor(); break;
        case 20: _t->stopMonitor(); break;
        case 21: _t->syncToSlave(); break;
        case 22: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DES_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DES_SERVICE::staticMetaObject = {
    { &MODBUS_SERVICE::staticMetaObject, qt_meta_stringdata_DES_SERVICE,
      qt_meta_data_DES_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DES_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DES_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DES_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DES_SERVICE))
        return static_cast<void*>(const_cast< DES_SERVICE*>(this));
    return MODBUS_SERVICE::qt_metacast(_clname);
}

int DES_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MODBUS_SERVICE::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void DES_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DES_SERVICE::sigDesState(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DES_SERVICE::sigSyncToSlave(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DES_SERVICE::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
