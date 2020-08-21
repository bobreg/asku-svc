/****************************************************************************
** Meta object code from reading C++ file 'ups_modbus_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ups_modbus_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ups_modbus_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UPS_MODBUS_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      43,   38,   19,   19, 0x05,
      73,   68,   19,   19, 0x05,
     107,  101,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     133,   19,   19,   19, 0x09,
     147,   19,   19,   19, 0x09,
     169,  164,   19,   19, 0x09,
     193,  164,   19,   19, 0x09,
     225,   19,  220,   19, 0x09,
     235,   19,  220,   19, 0x09,
     249,  244,   19,   19, 0x0a,
     269,   19,   19,   19, 0x0a,
     284,   19,   19,   19, 0x0a,
     299,   19,   19,   19, 0x0a,
     313,   19,   19,   19, 0x0a,
     327,   68,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UPS_MODBUS_SERVICE[] = {
    "UPS_MODBUS_SERVICE\0\0sigChangedState()\0"
    "info\0sigUpsState(QVariantMap)\0data\0"
    "sigSyncToSlave(QVariantMap)\0state\0"
    "sigState(AskuBinStateSet)\0onConnected()\0"
    "onDisconnected()\0port\0onConnectedPort(qint32)\0"
    "onDisconnectedPort(qint32)\0bool\0"
    "onQuery()\0onLive()\0main\0onChangedMain(bool)\0"
    "onRefreshUps()\0startMonitor()\0"
    "stopMonitor()\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap)\0"
};

void UPS_MODBUS_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UPS_MODBUS_SERVICE *_t = static_cast<UPS_MODBUS_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigChangedState(); break;
        case 1: _t->sigUpsState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 2: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 4: _t->onConnected(); break;
        case 5: _t->onDisconnected(); break;
        case 6: _t->onConnectedPort((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 7: _t->onDisconnectedPort((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: { bool _r = _t->onQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->onLive();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->onRefreshUps(); break;
        case 12: _t->startMonitor(); break;
        case 13: _t->stopMonitor(); break;
        case 14: _t->syncToSlave(); break;
        case 15: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UPS_MODBUS_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UPS_MODBUS_SERVICE::staticMetaObject = {
    { &MODBUS_SERVICE::staticMetaObject, qt_meta_stringdata_UPS_MODBUS_SERVICE,
      qt_meta_data_UPS_MODBUS_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UPS_MODBUS_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UPS_MODBUS_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UPS_MODBUS_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UPS_MODBUS_SERVICE))
        return static_cast<void*>(const_cast< UPS_MODBUS_SERVICE*>(this));
    return MODBUS_SERVICE::qt_metacast(_clname);
}

int UPS_MODBUS_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MODBUS_SERVICE::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void UPS_MODBUS_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UPS_MODBUS_SERVICE::sigUpsState(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UPS_MODBUS_SERVICE::sigSyncToSlave(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UPS_MODBUS_SERVICE::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
