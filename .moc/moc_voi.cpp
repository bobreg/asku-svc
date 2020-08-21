/****************************************************************************
** Meta object code from reading C++ file 'voi.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../voi.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'voi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,    5,    4,    4, 0x05,
      91,   77,    4,    4, 0x25,
     134,  129,    4,    4, 0x25,
     192,  165,    4,    4, 0x05,
     249,  235,    4,    4, 0x25,
     285,  129,    4,    4, 0x25,
     320,  314,    4,    4, 0x05,
     351,  314,    4,    4, 0x05,
     382,    4,    4,    4, 0x05,
     405,  402,    4,    4, 0x05,
     427,  129,    4,    4, 0x05,
     475,  462,    4,    4, 0x05,
     517,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     538,  462,    4,    4, 0x09,
     575,  402,    4,    4, 0x0a,
     595,    4,    4,    4, 0x0a,
     612,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VOI[] = {
    "VOI\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "data,idmodule,idConnection\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "data,idmodule\0sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0state\0"
    "sigStateLocal(AskuBinStateSet)\0"
    "sigStateOther(AskuBinStateSet)\0"
    "sigUpdateSkrPilot()\0on\0sigDisableTotal(bool)\0"
    "sigDisableDynamic(AskuSektorTable)\0"
    "config,state\0sigOnSyncToSlave(QVariantMap,QVariantMap)\0"
    "sigNeedSyncToSlave()\0"
    "syncToSlave(QVariantMap,QVariantMap)\0"
    "onChangedMain(bool)\0onConnectedGpr()\0"
    "onDisconnectedGpr()\0"
};

void VOI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VOI *_t = static_cast<VOI *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sigStateLocal((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 7: _t->sigStateOther((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 8: _t->sigUpdateSkrPilot(); break;
        case 9: _t->sigDisableTotal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->sigDisableDynamic((*reinterpret_cast< AskuSektorTable(*)>(_a[1]))); break;
        case 11: _t->sigOnSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 12: _t->sigNeedSyncToSlave(); break;
        case 13: _t->syncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 14: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->onConnectedGpr(); break;
        case 16: _t->onDisconnectedGpr(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VOI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VOI::staticMetaObject = {
    { &VOI_THREAD::staticMetaObject, qt_meta_stringdata_VOI,
      qt_meta_data_VOI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOI))
        return static_cast<void*>(const_cast< VOI*>(this));
    return VOI_THREAD::qt_metacast(_clname);
}

int VOI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VOI_THREAD::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void VOI::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void VOI::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void VOI::sigStateLocal(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void VOI::sigStateOther(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void VOI::sigUpdateSkrPilot()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void VOI::sigDisableTotal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void VOI::sigDisableDynamic(AskuSektorTable _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void VOI::sigOnSyncToSlave(QVariantMap _t1, QVariantMap _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void VOI::sigNeedSyncToSlave()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}
QT_END_MOC_NAMESPACE
