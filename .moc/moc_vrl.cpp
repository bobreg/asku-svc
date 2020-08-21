/****************************************************************************
** Meta object code from reading C++ file 'vrl.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vrl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vrl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VRL[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,    5,    4,    4, 0x05,
      91,   77,    4,    4, 0x25,
     134,  129,    4,    4, 0x25,
     165,    5,    4,    4, 0x05,
     208,   77,    4,    4, 0x25,
     244,  129,    4,    4, 0x25,
     279,  273,    4,    4, 0x05,
     305,  273,    4,    4, 0x05,
     347,  328,    4,    4, 0x05,
     401,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     422,  328,    4,    4, 0x09,
     474,  471,    4,    4, 0x0a,
     494,    4,    4,    4, 0x0a,
     511,    4,    4,    4, 0x0a,
     537,  531,    4,    4, 0x0a,
     560,  471,    4,    4, 0x0a,
     589,  471,    4,    4, 0x0a,
     611,  129,    4,    4, 0x0a,
     651,  646,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VRL[] = {
    "VRL\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0state\0"
    "sigState(AskuBinStateSet)\0"
    "sigKoeff(AskuValueSet)\0config,state,koeff\0"
    "sigOnSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "sigNeedSyncToSlave()\0"
    "syncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "on\0onChangedMain(bool)\0onConnectedGpr()\0"
    "onDisconnectedGpr()\0n_vrl\0"
    "cmdSetMainVRL(quint32)\0"
    "cmdSetDisableReconfVRL(bool)\0"
    "cmdDisableTotal(bool)\0"
    "cmdDisableDynamic(AskuSektorTable)\0"
    "info\0refreshState(QVariantMap)\0"
};

void VRL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VRL *_t = static_cast<VRL *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 7: _t->sigKoeff((*reinterpret_cast< AskuValueSet(*)>(_a[1]))); break;
        case 8: _t->sigOnSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 9: _t->sigNeedSyncToSlave(); break;
        case 10: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 11: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->onConnectedGpr(); break;
        case 13: _t->onDisconnectedGpr(); break;
        case 14: _t->cmdSetMainVRL((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 15: _t->cmdSetDisableReconfVRL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->cmdDisableTotal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->cmdDisableDynamic((*reinterpret_cast< AskuSektorTable(*)>(_a[1]))); break;
        case 18: _t->refreshState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VRL::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VRL::staticMetaObject = {
    { &VRL_THREAD::staticMetaObject, qt_meta_stringdata_VRL,
      qt_meta_data_VRL, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VRL::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VRL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VRL::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VRL))
        return static_cast<void*>(const_cast< VRL*>(this));
    return VRL_THREAD::qt_metacast(_clname);
}

int VRL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VRL_THREAD::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void VRL::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void VRL::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void VRL::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void VRL::sigKoeff(AskuValueSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void VRL::sigOnSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void VRL::sigNeedSyncToSlave()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
