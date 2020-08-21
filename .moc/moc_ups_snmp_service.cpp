/****************************************************************************
** Meta object code from reading C++ file 'ups_snmp_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ups_snmp_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ups_snmp_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UPS_SNMP_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      41,   36,   17,   17, 0x05,
      87,   66,   17,   17, 0x05,
     153,  139,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     192,   17,   17,   17, 0x09,
     206,   17,   17,   17, 0x09,
     228,  223,   17,   17, 0x0a,
     248,   17,   17,   17, 0x0a,
     263,   17,   17,   17, 0x0a,
     278,   17,   17,   17, 0x0a,
     292,   17,   17,   17, 0x0a,
     306,   66,   17,   17, 0x0a,
     372,  357,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UPS_SNMP_SERVICE[] = {
    "UPS_SNMP_SERVICE\0\0sigChangedState()\0"
    "info\0sigUpsState(QVariantMap)\0"
    "config,state,measure\0"
    "sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "state,measure\0sigState(AskuBinStateSet,AskuValueSet)\0"
    "onConnected()\0onDisconnected()\0main\0"
    "onChangedMain(bool)\0onRefreshUps()\0"
    "startMonitor()\0stopMonitor()\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "device,results\0"
    "onProcessSnmpResults(SNMP_DEVICE*,SnmpResultMap)\0"
};

void UPS_SNMP_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UPS_SNMP_SERVICE *_t = static_cast<UPS_SNMP_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigChangedState(); break;
        case 1: _t->sigUpsState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 2: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 3: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1])),(*reinterpret_cast< AskuValueSet(*)>(_a[2]))); break;
        case 4: _t->onConnected(); break;
        case 5: _t->onDisconnected(); break;
        case 6: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onRefreshUps(); break;
        case 8: _t->startMonitor(); break;
        case 9: _t->stopMonitor(); break;
        case 10: _t->syncToSlave(); break;
        case 11: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 12: _t->onProcessSnmpResults((*reinterpret_cast< SNMP_DEVICE*(*)>(_a[1])),(*reinterpret_cast< const SnmpResultMap(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UPS_SNMP_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UPS_SNMP_SERVICE::staticMetaObject = {
    { &SNMP_SERVICE::staticMetaObject, qt_meta_stringdata_UPS_SNMP_SERVICE,
      qt_meta_data_UPS_SNMP_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UPS_SNMP_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UPS_SNMP_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UPS_SNMP_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UPS_SNMP_SERVICE))
        return static_cast<void*>(const_cast< UPS_SNMP_SERVICE*>(this));
    return SNMP_SERVICE::qt_metacast(_clname);
}

int UPS_SNMP_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SNMP_SERVICE::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void UPS_SNMP_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UPS_SNMP_SERVICE::sigUpsState(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UPS_SNMP_SERVICE::sigSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UPS_SNMP_SERVICE::sigState(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
