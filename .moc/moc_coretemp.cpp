/****************************************************************************
** Meta object code from reading C++ file 'coretemp.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coretemp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coretemp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CORETEMP[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      37,   10,    9,    9, 0x05,
      96,   82,    9,    9, 0x25,
     139,  134,    9,    9, 0x25,
     170,   10,    9,    9, 0x05,
     213,   82,    9,    9, 0x25,
     249,  134,    9,    9, 0x25,
     291,  278,    9,    9, 0x05,
     335,  278,    9,    9, 0x05,
     400,  379,    9,    9, 0x05,
     454,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     478,  475,    9,    9, 0x0a,
     498,    9,    9,    9, 0x0a,
     515,    9,    9,    9, 0x0a,
     540,  535,    9,    9, 0x0a,
     566,  379,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CORETEMP[] = {
    "CORETEMP\0\0data,idModule,idConnection\0"
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
    "sigNeedSyncToSlave()\0on\0onChangedMain(bool)\0"
    "onConnectedGpr()\0onDisconnectedGpr()\0"
    "info\0refreshState(QVariantMap)\0"
    "syncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
};

void CORETEMP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CORETEMP *_t = static_cast<CORETEMP *>(_o);
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
        case 10: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->onConnectedGpr(); break;
        case 12: _t->onDisconnectedGpr(); break;
        case 13: _t->refreshState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 14: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CORETEMP::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CORETEMP::staticMetaObject = {
    { &CORETEMP_THREAD::staticMetaObject, qt_meta_stringdata_CORETEMP,
      qt_meta_data_CORETEMP, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CORETEMP::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CORETEMP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CORETEMP::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CORETEMP))
        return static_cast<void*>(const_cast< CORETEMP*>(this));
    return CORETEMP_THREAD::qt_metacast(_clname);
}

int CORETEMP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CORETEMP_THREAD::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void CORETEMP::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void CORETEMP::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void CORETEMP::sigStateLocal(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CORETEMP::sigStateOther(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CORETEMP::sigOnSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CORETEMP::sigNeedSyncToSlave()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
