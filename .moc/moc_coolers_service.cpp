/****************************************************************************
** Meta object code from reading C++ file 'coolers_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coolers_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coolers_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_COOLERS_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      40,   35,   16,   16, 0x05,
      74,   69,   16,   16, 0x05,
     108,  102,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     134,   16,   16,   16, 0x09,
     148,   16,   16,   16, 0x09,
     170,   16,  165,   16, 0x09,
     180,   16,  165,   16, 0x09,
     189,   16,   16,   16, 0x09,
     213,  208,   16,   16, 0x0a,
     250,  233,   16,   16, 0x0a,
     291,  286,   16,   16, 0x0a,
     317,   16,   16,   16, 0x0a,
     335,  328,   16,   16, 0x0a,
     363,  351,   16,   16, 0x0a,
     397,  383,   16,   16, 0x0a,
     421,   16,   16,   16, 0x0a,
     440,   16,   16,   16, 0x0a,
     455,   16,   16,   16, 0x0a,
     469,   16,   16,   16, 0x0a,
     483,   69,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_COOLERS_SERVICE[] = {
    "COOLERS_SERVICE\0\0sigChangedState()\0"
    "info\0sigCoolersState(QVariantMap)\0"
    "data\0sigSyncToSlave(QVariantMap)\0state\0"
    "sigState(AskuBinStateSet)\0onConnected()\0"
    "onDisconnected()\0bool\0onQuery()\0"
    "onLive()\0setFirstCommands()\0main\0"
    "onChangedMain(bool)\0n_cooler,on,temp\0"
    "setTemperature(quint32,bool,double)\0"
    "temp\0setExtTemperature(double)\0"
    "setReset()\0manual\0setManual(bool)\0"
    "n_cooler,on\0setOn(quint32,bool)\0"
    "n_cooler,freq\0setFreq(quint32,double)\0"
    "onRefreshCoolers()\0startMonitor()\0"
    "stopMonitor()\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap)\0"
};

void COOLERS_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        COOLERS_SERVICE *_t = static_cast<COOLERS_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigChangedState(); break;
        case 1: _t->sigCoolersState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
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
        case 10: _t->setTemperature((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 11: _t->setExtTemperature((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->setReset(); break;
        case 13: _t->setManual((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->setOn((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->setFreq((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 16: _t->onRefreshCoolers(); break;
        case 17: _t->startMonitor(); break;
        case 18: _t->stopMonitor(); break;
        case 19: _t->syncToSlave(); break;
        case 20: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData COOLERS_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject COOLERS_SERVICE::staticMetaObject = {
    { &MODBUS_SERVICE::staticMetaObject, qt_meta_stringdata_COOLERS_SERVICE,
      qt_meta_data_COOLERS_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &COOLERS_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *COOLERS_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *COOLERS_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_COOLERS_SERVICE))
        return static_cast<void*>(const_cast< COOLERS_SERVICE*>(this));
    return MODBUS_SERVICE::qt_metacast(_clname);
}

int COOLERS_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MODBUS_SERVICE::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void COOLERS_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void COOLERS_SERVICE::sigCoolersState(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void COOLERS_SERVICE::sigSyncToSlave(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void COOLERS_SERVICE::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
