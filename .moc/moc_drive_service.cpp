/****************************************************************************
** Meta object code from reading C++ file 'drive_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../drive_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drive_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DRIVE_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   15,   14,   14, 0x05,
      94,   88,   14,   14, 0x05,
     125,  120,   14,   14, 0x05,
     152,   14,   14,   14, 0x05,
     175,  170,   14,   14, 0x05,
     199,   14,   14,   14, 0x05,
     212,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     225,   14,   14,   14, 0x09,
     239,   14,   14,   14, 0x09,
     261,  256,   14,   14, 0x09,
     285,  256,   14,   14, 0x09,
     317,   14,  312,   14, 0x09,
     327,   14,  312,   14, 0x09,
     336,   14,   14,   14, 0x09,
     360,  355,   14,   14, 0x0a,
     387,  380,   14,   14, 0x0a,
     411,  403,   14,   14, 0x0a,
     429,  403,   14,   14, 0x0a,
     456,  450,   14,   14, 0x0a,
     473,   14,   14,   14, 0x0a,
     484,   14,   14,   14, 0x0a,
     501,   14,   14,   14, 0x0a,
     516,   14,   14,   14, 0x0a,
     530,   14,   14,   14, 0x0a,
     544,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DRIVE_SERVICE[] = {
    "DRIVE_SERVICE\0\0config,state,measure\0"
    "sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "state\0sigState(AskuBinStateSet)\0info\0"
    "sigDriveState(QVariantMap)\0sigChangedState()\0"
    "ndrv\0sigButtonServo(quint32)\0sigStopped()\0"
    "sigStarted()\0onConnected()\0onDisconnected()\0"
    "port\0onConnectedPort(qint32)\0"
    "onDisconnectedPort(qint32)\0bool\0"
    "onQuery()\0onLive()\0setFirstCommands()\0"
    "main\0onChangedMain(bool)\0manual\0"
    "setManual(bool)\0n_drive\0setServo(quint32)\0"
    "setOverride(quint32)\0speed\0setSpeed(double)\0"
    "setReset()\0onRefreshDrive()\0startMonitor()\0"
    "stopMonitor()\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
};

void DRIVE_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DRIVE_SERVICE *_t = static_cast<DRIVE_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 1: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 2: _t->sigDriveState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sigChangedState(); break;
        case 4: _t->sigButtonServo((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 5: _t->sigStopped(); break;
        case 6: _t->sigStarted(); break;
        case 7: _t->onConnected(); break;
        case 8: _t->onDisconnected(); break;
        case 9: _t->onConnectedPort((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->onDisconnectedPort((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 11: { bool _r = _t->onQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->onLive();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->setFirstCommands(); break;
        case 14: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->setManual((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->setServo((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 17: _t->setOverride((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 18: _t->setSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->setReset(); break;
        case 20: _t->onRefreshDrive(); break;
        case 21: _t->startMonitor(); break;
        case 22: _t->stopMonitor(); break;
        case 23: _t->syncToSlave(); break;
        case 24: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DRIVE_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DRIVE_SERVICE::staticMetaObject = {
    { &MODBUS_SERVICE::staticMetaObject, qt_meta_stringdata_DRIVE_SERVICE,
      qt_meta_data_DRIVE_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DRIVE_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DRIVE_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DRIVE_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DRIVE_SERVICE))
        return static_cast<void*>(const_cast< DRIVE_SERVICE*>(this));
    return MODBUS_SERVICE::qt_metacast(_clname);
}

int DRIVE_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MODBUS_SERVICE::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void DRIVE_SERVICE::sigSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DRIVE_SERVICE::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DRIVE_SERVICE::sigDriveState(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DRIVE_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void DRIVE_SERVICE::sigButtonServo(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DRIVE_SERVICE::sigStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void DRIVE_SERVICE::sigStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
