/****************************************************************************
** Meta object code from reading C++ file 'dasd.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dasd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dasd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DASD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,    6,    5,    5, 0x05,
      92,   78,    5,    5, 0x25,
     135,  130,    5,    5, 0x25,
     166,    6,    5,    5, 0x05,
     209,   78,    5,    5, 0x25,
     245,  130,    5,    5, 0x25,
     287,  274,    5,    5, 0x05,
     331,  274,    5,    5, 0x05,
     396,  375,    5,    5, 0x05,
     450,    5,    5,    5, 0x05,
     471,    5,    5,    5, 0x05,
     497,  490,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
     530,  375,    5,    5, 0x09,
     582,  579,    5,    5, 0x0a,
     602,    5,    5,    5, 0x0a,
     619,    5,    5,    5, 0x0a,
     639,    5,    5,    5, 0x0a,
     660,  652,    5,    5, 0x0a,
     692,  652,    5,    5, 0x0a,
     732,  727,    5,    5, 0x0a,
     765,  757,    5,    5, 0x0a,
     788,    5,    5,    5, 0x0a,
     824,  806,    5,    5, 0x0a,
     867,  861,    5,    5, 0x0a,
     904,  893,    5,    5, 0x0a,
     948,  935,    5,    5, 0x0a,
     979,  935,    5,    5, 0x0a,
    1009,  935,    5,    5, 0x0a,
    1041,  935,    5,    5, 0x0a,
    1074,  757,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DASD[] = {
    "DASD\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0state,values\0"
    "sigStateLocal(AskuBinStateSet,AskuValueSet)\0"
    "sigStateOther(AskuBinStateSet,AskuValueSet)\0"
    "config,state,measure\0"
    "sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "sigNeedSyncToSlave()\0sigFlushSettings()\0"
    "source\0sigChangedAzimuthSource(quint32)\0"
    "syncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "on\0onChangedMain(bool)\0onConnectedGpr()\0"
    "onDisconnectedGpr()\0onSetReset()\0"
    "devRegs\0dumpRegisters(DEVICE_REGISTERS)\0"
    "refreshRegisters(DEVICE_REGISTERS)\0"
    "list\0commandList(QStringList)\0message\0"
    "statusMessage(QString)\0refreshSkrPilot()\0"
    "azSKR,azPS,period\0"
    "setSkrPilot(quint32,quint32,quint32)\0"
    "value\0setFreqDeviation(quint32)\0"
    "setPrmInfo\0refreshSetPrmInfo(QVariantMap)\0"
    "table,maxRow\0tableRipch(QVariantMap,qint32)\0"
    "tableMode(QVariantMap,qint32)\0"
    "tableSwitch(QVariantMap,qint32)\0"
    "tableDisable(QVariantMap,qint32)\0"
    "tablesResults(QString)\0"
};

void DASD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DASD *_t = static_cast<DASD *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sigStateLocal((*reinterpret_cast< AskuBinStateSet(*)>(_a[1])),(*reinterpret_cast< AskuValueSet(*)>(_a[2]))); break;
        case 7: _t->sigStateOther((*reinterpret_cast< AskuBinStateSet(*)>(_a[1])),(*reinterpret_cast< AskuValueSet(*)>(_a[2]))); break;
        case 8: _t->sigOnSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 9: _t->sigNeedSyncToSlave(); break;
        case 10: _t->sigFlushSettings(); break;
        case 11: _t->sigChangedAzimuthSource((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 12: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 13: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->onConnectedGpr(); break;
        case 15: _t->onDisconnectedGpr(); break;
        case 16: _t->onSetReset(); break;
        case 17: _t->dumpRegisters((*reinterpret_cast< DEVICE_REGISTERS(*)>(_a[1]))); break;
        case 18: _t->refreshRegisters((*reinterpret_cast< DEVICE_REGISTERS(*)>(_a[1]))); break;
        case 19: _t->commandList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 20: _t->statusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->refreshSkrPilot(); break;
        case 22: _t->setSkrPilot((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        case 23: _t->setFreqDeviation((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 24: _t->refreshSetPrmInfo((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 25: _t->tableRipch((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 26: _t->tableMode((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 27: _t->tableSwitch((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 28: _t->tableDisable((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 29: _t->tablesResults((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DASD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DASD::staticMetaObject = {
    { &DASD_THREAD::staticMetaObject, qt_meta_stringdata_DASD,
      qt_meta_data_DASD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DASD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DASD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DASD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DASD))
        return static_cast<void*>(const_cast< DASD*>(this));
    return DASD_THREAD::qt_metacast(_clname);
}

int DASD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DASD_THREAD::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void DASD::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void DASD::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void DASD::sigStateLocal(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DASD::sigStateOther(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DASD::sigOnSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DASD::sigNeedSyncToSlave()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void DASD::sigFlushSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void DASD::sigChangedAzimuthSource(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
