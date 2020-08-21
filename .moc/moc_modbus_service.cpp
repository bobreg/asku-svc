/****************************************************************************
** Meta object code from reading C++ file 'modbus_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../modbus_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modbus_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MODBUS_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x09,
      35,   15,   15,   15, 0x09,
      52,   15,   15,   15, 0x09,
      76,   68,   15,   15, 0x09,
     112,  109,   15,   15, 0x09,
     132,  109,   15,   15, 0x09,
     155,   15,   15,   15, 0x09,
     169,   15,   15,   15, 0x09,
     191,  186,   15,   15, 0x09,
     215,  186,   15,   15, 0x09,
     247,  242,   15,   15, 0x09,
     272,   15,  267,   15, 0x09,
     282,   15,  267,   15, 0x09,
     294,  291,   15,   15, 0x0a,
     308,  291,   15,   15, 0x0a,
     337,  291,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MODBUS_SERVICE[] = {
    "MODBUS_SERVICE\0\0slotConnectTimer()\0"
    "slotQueryTimer()\0slotLiveTimer()\0"
    "id,data\0onDataArrived(qint32,QByteArray)\0"
    "id\0onConnected(qint32)\0onDisconnected(qint32)\0"
    "onConnected()\0onDisconnected()\0port\0"
    "onConnectedPort(qint32)\0"
    "onDisconnectedPort(qint32)\0main\0"
    "onChangedMain(bool)\0bool\0onQuery()\0"
    "onLive()\0on\0setMain(bool)\0"
    "setSeparateConnections(bool)\0"
    "setSingleConnection(bool)\0"
};

void MODBUS_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MODBUS_SERVICE *_t = static_cast<MODBUS_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->slotConnectTimer(); break;
        case 1: _t->slotQueryTimer(); break;
        case 2: _t->slotLiveTimer(); break;
        case 3: _t->onDataArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 4: _t->onConnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 5: _t->onDisconnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 6: _t->onConnected(); break;
        case 7: _t->onDisconnected(); break;
        case 8: _t->onConnectedPort((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 9: _t->onDisconnectedPort((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: { bool _r = _t->onQuery();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->onLive();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->setMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->setSeparateConnections((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->setSingleConnection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MODBUS_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MODBUS_SERVICE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MODBUS_SERVICE,
      qt_meta_data_MODBUS_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MODBUS_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MODBUS_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MODBUS_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MODBUS_SERVICE))
        return static_cast<void*>(const_cast< MODBUS_SERVICE*>(this));
    return QObject::qt_metacast(_clname);
}

int MODBUS_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
