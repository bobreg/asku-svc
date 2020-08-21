/****************************************************************************
** Meta object code from reading C++ file 'voi_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../voi_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'voi_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOI_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x05,
      50,   13,   12,   12, 0x05,
      94,   81,   12,   12, 0x05,
     134,   12,   12,   12, 0x05,
     155,  152,   12,   12, 0x05,
     182,  177,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     217,   12,   12,   12, 0x09,
     248,  227,   12,   12, 0x09,
     295,  152,   12,   12, 0x0a,
     309,   12,   12,   12, 0x0a,
     327,   12,   12,   12, 0x0a,
     357,  348,   12,   12, 0x0a,
     395,  382,   12,   12, 0x0a,
     426,   12,   12,   12, 0x0a,
     445,   12,   12,   12, 0x0a,
     459,   81,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VOI_SERVICE[] = {
    "VOI_SERVICE\0\0state\0sigStateLocal(AskuBinStateSet)\0"
    "sigStateOther(AskuBinStateSet)\0"
    "config,state\0sigSyncToSlave(QVariantMap,QVariantMap)\0"
    "sigChangedState()\0on\0sigDisableTotal(bool)\0"
    "data\0sigDisableDynamic(AskuSektorTable)\0"
    "timeout()\0data,haFrom,portFrom\0"
    "onDataArrived(QByteArray,QHostAddress,quint16)\0"
    "setMain(bool)\0setConnectedGpr()\0"
    "setDisconnectedGpr()\0rlkState\0"
    "setRlsState(QVariantMap)\0disableTable\0"
    "setDisableSektors(QVariantMap)\0"
    "setControlSektor()\0syncToSlave()\0"
    "onSyncToSlave(QVariantMap,QVariantMap)\0"
};

void VOI_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VOI_SERVICE *_t = static_cast<VOI_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigStateLocal((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 1: _t->sigStateOther((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 2: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        case 3: _t->sigChangedState(); break;
        case 4: _t->sigDisableTotal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->sigDisableDynamic((*reinterpret_cast< AskuSektorTable(*)>(_a[1]))); break;
        case 6: _t->timeout(); break;
        case 7: _t->onDataArrived((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 8: _t->setMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setConnectedGpr(); break;
        case 10: _t->setDisconnectedGpr(); break;
        case 11: _t->setRlsState((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 12: _t->setDisableSektors((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 13: _t->setControlSektor(); break;
        case 14: _t->syncToSlave(); break;
        case 15: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VOI_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VOI_SERVICE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VOI_SERVICE,
      qt_meta_data_VOI_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOI_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOI_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOI_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOI_SERVICE))
        return static_cast<void*>(const_cast< VOI_SERVICE*>(this));
    return QObject::qt_metacast(_clname);
}

int VOI_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void VOI_SERVICE::sigStateLocal(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VOI_SERVICE::sigStateOther(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VOI_SERVICE::sigSyncToSlave(QVariantMap _t1, QVariantMap _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VOI_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void VOI_SERVICE::sigDisableTotal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VOI_SERVICE::sigDisableDynamic(AskuSektorTable _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
