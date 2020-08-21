/****************************************************************************
** Meta object code from reading C++ file 'poi.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../poi.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'poi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_POI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,    5,    4,    4, 0x05,
      91,   77,    4,    4, 0x25,
     134,  129,    4,    4, 0x25,
     165,    5,    4,    4, 0x05,
     208,   77,    4,    4, 0x25,
     244,  129,    4,    4, 0x25,
     279,  273,    4,    4, 0x05,
     310,  273,    4,    4, 0x05,
     338,  273,    4,    4, 0x05,
     366,  273,    4,    4, 0x05,
     400,  273,    4,    4, 0x05,
     431,  273,    4,    4, 0x05,
     459,  273,    4,    4, 0x05,
     487,  273,    4,    4, 0x05,
     546,  521,    4,    4, 0x05,
     612,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     633,  521,    4,    4, 0x09,
     697,  694,    4,    4, 0x0a,
     717,    4,    4,    4, 0x0a,
     732,    4,    4,    4, 0x0a,
     749,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_POI[] = {
    "POI\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0state\0"
    "sigStateLocal(AskuBinStateSet)\0"
    "sigKoeffLocal(AskuValueSet)\0"
    "sigPilotLocal(AskuValueSet)\0"
    "sigTransmitterLocal(AskuValueSet)\0"
    "sigStateOther(AskuBinStateSet)\0"
    "sigKoeffOther(AskuValueSet)\0"
    "sigPilotOther(AskuValueSet)\0"
    "sigTransmitterOther(AskuValueSet)\0"
    "config,state,koeff,pilot\0"
    "sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)\0"
    "sigNeedSyncToSlave()\0"
    "syncToSlave(QVariantMap,QVariantMap,QVariantMap,QVariantMap)\0"
    "on\0onChangedMain(bool)\0onResetKoeff()\0"
    "onConnectedGpr()\0onDisconnectedGpr()\0"
};

void POI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        POI *_t = static_cast<POI *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sigStateLocal((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 7: _t->sigKoeffLocal((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 8: _t->sigPilotLocal((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 9: _t->sigTransmitterLocal((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 10: _t->sigStateOther((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 11: _t->sigKoeffOther((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 12: _t->sigPilotOther((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 13: _t->sigTransmitterOther((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 14: _t->sigOnSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3])),(*reinterpret_cast< QVariantMap(*)>(_a[4]))); break;
        case 15: _t->sigNeedSyncToSlave(); break;
        case 16: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3])),(*reinterpret_cast< QVariantMap(*)>(_a[4]))); break;
        case 17: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->onResetKoeff(); break;
        case 19: _t->onConnectedGpr(); break;
        case 20: _t->onDisconnectedGpr(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData POI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject POI::staticMetaObject = {
    { &POI_THREAD::staticMetaObject, qt_meta_stringdata_POI,
      qt_meta_data_POI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &POI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *POI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *POI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_POI))
        return static_cast<void*>(const_cast< POI*>(this));
    return POI_THREAD::qt_metacast(_clname);
}

int POI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = POI_THREAD::qt_metacall(_c, _id, _a);
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
void POI::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void POI::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void POI::sigStateLocal(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void POI::sigKoeffLocal(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void POI::sigPilotLocal(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void POI::sigTransmitterLocal(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void POI::sigStateOther(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void POI::sigKoeffOther(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void POI::sigPilotOther(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void POI::sigTransmitterOther(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void POI::sigOnSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3, QVariantMap _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void POI::sigNeedSyncToSlave()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}
QT_END_MOC_NAMESPACE
