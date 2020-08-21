/****************************************************************************
** Meta object code from reading C++ file 'drive.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../drive.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DRIVE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,    7,    6,    6, 0x05,
      93,   79,    6,    6, 0x25,
     136,  131,    6,    6, 0x25,
     167,    7,    6,    6, 0x05,
     210,   79,    6,    6, 0x25,
     246,  131,    6,    6, 0x25,
     281,  275,    6,    6, 0x05,
     328,  307,    6,    6, 0x05,
     382,    6,    6,    6, 0x05,
     408,  403,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     435,  432,    6,    6, 0x0a,
     455,    6,    6,    6, 0x0a,
     472,    6,    6,    6, 0x0a,
     497,  492,    6,    6, 0x0a,
     529,  523,    6,    6, 0x0a,
     556,  548,    6,    6, 0x0a,
     576,  548,    6,    6, 0x0a,
     599,    6,    6,    6, 0x0a,
     612,    6,    6,    6, 0x0a,
     627,    6,    6,    6, 0x0a,
     643,    6,    6,    6, 0x0a,
     659,    6,    6,    6, 0x0a,
     682,  675,    6,    6, 0x0a,
     705,  307,    6,    6, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DRIVE[] = {
    "DRIVE\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0state\0"
    "sigState(AskuBinStateSet)\0"
    "config,state,measure\0"
    "sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "sigNeedSyncToSlave()\0ndrv\0"
    "sigButtonServo(quint32)\0on\0"
    "onChangedMain(bool)\0onConnectedGpr()\0"
    "onDisconnectedGpr()\0info\0"
    "refreshState(QVariantMap)\0speed\0"
    "onSetSpeed(double)\0n_drive\0"
    "onSetServo(quint32)\0onSetOverride(quint32)\0"
    "onSetReset()\0onSetServoOn()\0onSetServo1On()\0"
    "onSetServo2On()\0onSetServoOff()\0number\0"
    "onSetOverview(quint32)\0"
    "syncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
};

void DRIVE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DRIVE *_t = static_cast<DRIVE *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 7: _t->sigOnSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 8: _t->sigNeedSyncToSlave(); break;
        case 9: _t->sigButtonServo((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 10: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->onConnectedGpr(); break;
        case 12: _t->onDisconnectedGpr(); break;
        case 13: _t->refreshState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 14: _t->onSetSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->onSetServo((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 16: _t->onSetOverride((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 17: _t->onSetReset(); break;
        case 18: _t->onSetServoOn(); break;
        case 19: _t->onSetServo1On(); break;
        case 20: _t->onSetServo2On(); break;
        case 21: _t->onSetServoOff(); break;
        case 22: _t->onSetOverview((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 23: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DRIVE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DRIVE::staticMetaObject = {
    { &DRIVE_THREAD::staticMetaObject, qt_meta_stringdata_DRIVE,
      qt_meta_data_DRIVE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DRIVE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DRIVE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DRIVE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DRIVE))
        return static_cast<void*>(const_cast< DRIVE*>(this));
    return DRIVE_THREAD::qt_metacast(_clname);
}

int DRIVE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DRIVE_THREAD::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void DRIVE::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void DRIVE::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void DRIVE::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DRIVE::sigOnSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DRIVE::sigNeedSyncToSlave()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void DRIVE::sigButtonServo(quint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
