/****************************************************************************
** Meta object code from reading C++ file 'coolers.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coolers.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coolers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_COOLERS[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,    9,    8,    8, 0x05,
      95,   81,    8,    8, 0x25,
     138,  133,    8,    8, 0x25,
     169,    9,    8,    8, 0x05,
     212,   81,    8,    8, 0x25,
     248,  133,    8,    8, 0x25,
     283,  277,    8,    8, 0x05,
     309,  133,    8,    8, 0x05,
     339,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     363,  360,    8,    8, 0x0a,
     407,  383,    8,    8, 0x0a,
     457,  445,    8,    8, 0x0a,
     485,    8,    8,    8, 0x0a,
     510,  498,    8,    8, 0x0a,
     537,  532,    8,    8, 0x0a,
     556,    8,    8,    8, 0x2a,
     571,  532,    8,    8, 0x0a,
     590,    8,    8,    8, 0x2a,
     605,  532,    8,    8, 0x0a,
     625,    8,    8,    8, 0x2a,
     641,  532,    8,    8, 0x0a,
     661,    8,    8,    8, 0x2a,
     682,  677,    8,    8, 0x0a,
     708,  133,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_COOLERS[] = {
    "COOLERS\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0state\0"
    "sigState(AskuBinStateSet)\0"
    "sigOnSyncToSlave(QVariantMap)\0"
    "sigNeedSyncToSlave()\0on\0onChangedMain(bool)\0"
    "n_cooler,on,temperature\0"
    "onSetTemperature(quint32,bool,double)\0"
    "temperature\0onSetExtTemperature(double)\0"
    "onSetReset()\0n_cooler,on\0onSetOn(quint32,bool)\0"
    "oper\0cmdSetSvo1On(bool)\0cmdSetSvo1On()\0"
    "cmdSetSvo2On(bool)\0cmdSetSvo2On()\0"
    "cmdSetSvo1Off(bool)\0cmdSetSvo1Off()\0"
    "cmdSetSvo2Off(bool)\0cmdSetSvo2Off()\0"
    "info\0refreshState(QVariantMap)\0"
    "syncToSlave(QVariantMap)\0"
};

void COOLERS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        COOLERS *_t = static_cast<COOLERS *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 7: _t->sigOnSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 8: _t->sigNeedSyncToSlave(); break;
        case 9: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onSetTemperature((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 11: _t->onSetExtTemperature((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->onSetReset(); break;
        case 13: _t->onSetOn((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->cmdSetSvo1On((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->cmdSetSvo1On(); break;
        case 16: _t->cmdSetSvo2On((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->cmdSetSvo2On(); break;
        case 18: _t->cmdSetSvo1Off((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->cmdSetSvo1Off(); break;
        case 20: _t->cmdSetSvo2Off((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->cmdSetSvo2Off(); break;
        case 22: _t->refreshState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 23: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData COOLERS::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject COOLERS::staticMetaObject = {
    { &COOLERS_THREAD::staticMetaObject, qt_meta_stringdata_COOLERS,
      qt_meta_data_COOLERS, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &COOLERS::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *COOLERS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *COOLERS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_COOLERS))
        return static_cast<void*>(const_cast< COOLERS*>(this));
    return COOLERS_THREAD::qt_metacast(_clname);
}

int COOLERS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = COOLERS_THREAD::qt_metacall(_c, _id, _a);
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
void COOLERS::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void COOLERS::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void COOLERS::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void COOLERS::sigOnSyncToSlave(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void COOLERS::sigNeedSyncToSlave()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}
QT_END_MOC_NAMESPACE
