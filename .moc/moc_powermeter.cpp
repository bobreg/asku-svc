/****************************************************************************
** Meta object code from reading C++ file 'powermeter.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../powermeter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'powermeter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PowerMeter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   12,   11,   11, 0x05,
      98,   84,   11,   11, 0x25,
     141,  136,   11,   11, 0x25,
     172,   12,   11,   11, 0x05,
     215,   84,   11,   11, 0x25,
     251,  136,   11,   11, 0x25,
     280,   12,   11,   11, 0x05,
     326,   84,   11,   11, 0x25,
     365,  136,   11,   11, 0x25,
     410,  397,   11,   11, 0x05,
     449,  136,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     482,  479,   11,   11, 0x0a,
     502,   11,   11,   11, 0x0a,
     515,   11,   11,   11, 0x0a,
     531,  526,   11,   11, 0x0a,
     557,   11,   11,   11, 0x0a,
     572,   11,   11,   11, 0x0a,
     580,   11,   11,   11, 0x0a,
     587,   11,   11,   11, 0x0a,
     604,   11,   11,   11, 0x0a,
     618,   11,   11,   11, 0x0a,
     635,  136,   11,   11, 0x08,
     679,  660,   11,   11, 0x08,
     719,  711,   11,   11, 0x28,
     739,  660,   11,   11, 0x08,
     778,  711,   11,   11, 0x28,

       0        // eod
};

static const char qt_meta_stringdata_PowerMeter[] = {
    "PowerMeter\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0"
    "sendControlCommand(QVariantMap,qint32,qint32)\0"
    "sendControlCommand(QVariantMap,qint32)\0"
    "sendControlCommand(QVariantMap)\0"
    "state,values\0sigState(AskuBinStateSet,AskuValueSet)\0"
    "sigOnSyncToSlave(QVariantMap)\0on\0"
    "onChangedMain(bool)\0cmdMeasure()\0"
    "cmdReset()\0info\0refreshState(QVariantMap)\0"
    "onRefreshPwm()\0start()\0stop()\0"
    "processTimeout()\0onConnected()\0"
    "onDisconnected()\0syncToSlave(QVariantMap)\0"
    "command,parameters\0sendAction(QString,QStringList)\0"
    "command\0sendAction(QString)\0"
    "sendControlAction(QString,QStringList)\0"
    "sendControlAction(QString)\0"
};

void PowerMeter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PowerMeter *_t = static_cast<PowerMeter *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sendControlCommand((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 7: _t->sendControlCommand((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 8: _t->sendControlCommand((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 9: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1])),(*reinterpret_cast< AskuValueSet(*)>(_a[2]))); break;
        case 10: _t->sigOnSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 11: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->cmdMeasure(); break;
        case 13: _t->cmdReset(); break;
        case 14: _t->refreshState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 15: _t->onRefreshPwm(); break;
        case 16: _t->start(); break;
        case 17: _t->stop(); break;
        case 18: _t->processTimeout(); break;
        case 19: _t->onConnected(); break;
        case 20: _t->onDisconnected(); break;
        case 21: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 22: _t->sendAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 23: _t->sendAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->sendControlAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 25: _t->sendControlAction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PowerMeter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PowerMeter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PowerMeter,
      qt_meta_data_PowerMeter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PowerMeter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PowerMeter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PowerMeter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PowerMeter))
        return static_cast<void*>(const_cast< PowerMeter*>(this));
    return QObject::qt_metacast(_clname);
}

int PowerMeter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void PowerMeter::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void PowerMeter::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void PowerMeter::sendControlCommand(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 9
void PowerMeter::sigState(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PowerMeter::sigOnSyncToSlave(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
