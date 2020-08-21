/****************************************************************************
** Meta object code from reading C++ file 'pos_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pos_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pos_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AskuPosAlarm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      24,   13,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AskuPosAlarm[] = {
    "AskuPosAlarm\0\0changed()\0timeout()\0"
};

void AskuPosAlarm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AskuPosAlarm *_t = static_cast<AskuPosAlarm *>(_o);
        switch (_id) {
        case 0: _t->changed(); break;
        case 1: _t->timeout(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AskuPosAlarm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AskuPosAlarm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AskuPosAlarm,
      qt_meta_data_AskuPosAlarm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AskuPosAlarm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AskuPosAlarm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AskuPosAlarm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskuPosAlarm))
        return static_cast<void*>(const_cast< AskuPosAlarm*>(this));
    return QObject::qt_metacast(_clname);
}

int AskuPosAlarm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void AskuPosAlarm::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_POS_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      37,   31,   12,   12, 0x05,
      63,   12,   12,   12, 0x05,
      82,   12,   12,   12, 0x05,
     105,  102,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     144,   12,   12,   12, 0x09,
     154,   12,   12,   12, 0x09,
     176,  168,   12,   12, 0x09,
     225,  209,   12,   12, 0x09,
     269,  266,   12,   12, 0x09,
     295,  292,   12,   12, 0x0a,
     309,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_POS_SERVICE[] = {
    "POS_SERVICE\0\0sigChangedState()\0state\0"
    "sigState(AskuBinStateSet)\0sigOsvPerimetrOn()\0"
    "sigOsvPerimetrOff()\0,,\0"
    "sigEventToLog(QString,QString,QString)\0"
    "timeout()\0pingTimeout()\0id,data\0"
    "onDataArrived(qint32,QByteArray)\0"
    "id,address,port\0"
    "onConnected(qint32,QHostAddress,quint16)\0"
    "id\0onDisconnected(qint32)\0on\0setMain(bool)\0"
    "sendStateRelay(bool)\0"
};

void POS_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        POS_SERVICE *_t = static_cast<POS_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigChangedState(); break;
        case 1: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 2: _t->sigOsvPerimetrOn(); break;
        case 3: _t->sigOsvPerimetrOff(); break;
        case 4: _t->sigEventToLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->timeout(); break;
        case 6: _t->pingTimeout(); break;
        case 7: _t->onDataArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 8: _t->onConnected((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 9: _t->onDisconnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->setMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->sendStateRelay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData POS_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject POS_SERVICE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_POS_SERVICE,
      qt_meta_data_POS_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &POS_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *POS_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *POS_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_POS_SERVICE))
        return static_cast<void*>(const_cast< POS_SERVICE*>(this));
    return QObject::qt_metacast(_clname);
}

int POS_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void POS_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void POS_SERVICE::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void POS_SERVICE::sigOsvPerimetrOn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void POS_SERVICE::sigOsvPerimetrOff()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void POS_SERVICE::sigEventToLog(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
