/****************************************************************************
** Meta object code from reading C++ file 'poi_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../poi_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'poi_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_POI_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      38,   13,   12,   12, 0x05,
     102,   12,   12,   12, 0x05,
     126,  120,   12,   12, 0x05,
     157,  120,   12,   12, 0x05,
     185,  120,   12,   12, 0x05,
     213,  120,   12,   12, 0x05,
     247,  120,   12,   12, 0x05,
     278,  120,   12,   12, 0x05,
     306,  120,   12,   12, 0x05,
     334,  120,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     368,   12,   12,   12, 0x09,
     386,  378,   12,   12, 0x09,
     435,  419,   12,   12, 0x09,
     479,  476,   12,   12, 0x09,
     502,   12,   12,   12, 0x09,
     523,  520,   12,   12, 0x0a,
     537,   12,   12,   12, 0x0a,
     553,   12,   12,   12, 0x0a,
     571,   12,   12,   12, 0x0a,
     597,  592,   12,   12, 0x0a,
     620,   12,   12,   12, 0x0a,
     634,   13,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_POI_SERVICE[] = {
    "POI_SERVICE\0\0config,state,koeff,pilot\0"
    "sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)\0"
    "sigChangedState()\0state\0"
    "sigStateLocal(AskuBinStateSet)\0"
    "sigKoeffLocal(AskuValueSet)\0"
    "sigPilotLocal(AskuValueSet)\0"
    "sigTransmitterLocal(AskuValueSet)\0"
    "sigStateOther(AskuBinStateSet)\0"
    "sigKoeffOther(AskuValueSet)\0"
    "sigPilotOther(AskuValueSet)\0"
    "sigTransmitterOther(AskuValueSet)\0"
    "timeout()\0id,data\0onDataArrived(qint32,QByteArray)\0"
    "id,address,port\0"
    "onConnected(qint32,QHostAddress,quint16)\0"
    "id\0onDisconnected(qint32)\0sendTemperature()\0"
    "on\0setMain(bool)\0setResetKoeff()\0"
    "setConnectedGpr()\0setDisconnectedGpr()\0"
    "temp\0setTemperature(double)\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)\0"
};

void POI_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        POI_SERVICE *_t = static_cast<POI_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3])),(*reinterpret_cast< QVariantMap(*)>(_a[4]))); break;
        case 1: _t->sigChangedState(); break;
        case 2: _t->sigStateLocal((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 3: _t->sigKoeffLocal((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 4: _t->sigPilotLocal((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 5: _t->sigTransmitterLocal((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 6: _t->sigStateOther((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 7: _t->sigKoeffOther((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 8: _t->sigPilotOther((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 9: _t->sigTransmitterOther((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 10: _t->timeout(); break;
        case 11: _t->onDataArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 12: _t->onConnected((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 13: _t->onDisconnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 14: _t->sendTemperature(); break;
        case 15: _t->setMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->setResetKoeff(); break;
        case 17: _t->setConnectedGpr(); break;
        case 18: _t->setDisconnectedGpr(); break;
        case 19: _t->setTemperature((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->syncToSlave(); break;
        case 21: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3])),(*reinterpret_cast< QVariantMap(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData POI_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject POI_SERVICE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_POI_SERVICE,
      qt_meta_data_POI_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &POI_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *POI_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *POI_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_POI_SERVICE))
        return static_cast<void*>(const_cast< POI_SERVICE*>(this));
    return QObject::qt_metacast(_clname);
}

int POI_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void POI_SERVICE::sigSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3, QVariantMap _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void POI_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void POI_SERVICE::sigStateLocal(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void POI_SERVICE::sigKoeffLocal(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void POI_SERVICE::sigPilotLocal(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void POI_SERVICE::sigTransmitterLocal(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void POI_SERVICE::sigStateOther(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void POI_SERVICE::sigKoeffOther(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void POI_SERVICE::sigPilotOther(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void POI_SERVICE::sigTransmitterOther(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
