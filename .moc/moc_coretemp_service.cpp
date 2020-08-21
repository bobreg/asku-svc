/****************************************************************************
** Meta object code from reading C++ file 'coretemp_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coretemp_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coretemp_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CORETEMP_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   18,   17,   17, 0x05,
     104,   91,   17,   17, 0x05,
     148,   91,   17,   17, 0x05,
     192,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     210,   17,   17,   17, 0x09,
     230,   17,   17,   17, 0x09,
     244,   18,   17,   17, 0x09,
     300,  295,   17,   17, 0x0a,
     320,   17,   17,   17, 0x0a,
     338,   17,   17,   17, 0x0a,
     359,   17,   17,   17, 0x0a,
     374,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CORETEMP_SERVICE[] = {
    "CORETEMP_SERVICE\0\0config,state,measure\0"
    "sigSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "state,values\0sigStateLocal(AskuBinStateSet,AskuValueSet)\0"
    "sigStateOther(AskuBinStateSet,AskuValueSet)\0"
    "sigChangedState()\0onRefreshCoreTemp()\0"
    "syncToSlave()\0"
    "onSyncToSlave(QVariantMap,QVariantMap,QVariantMap)\0"
    "main\0onChangedMain(bool)\0setConnectedGpr()\0"
    "setDisconnectedGpr()\0startMonitor()\0"
    "stopMonitor()\0"
};

void CORETEMP_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CORETEMP_SERVICE *_t = static_cast<CORETEMP_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 1: _t->sigStateLocal((*reinterpret_cast< AskuBinStateSet(*)>(_a[1])),(*reinterpret_cast< AskuValueSet(*)>(_a[2]))); break;
        case 2: _t->sigStateOther((*reinterpret_cast< AskuBinStateSet(*)>(_a[1])),(*reinterpret_cast< AskuValueSet(*)>(_a[2]))); break;
        case 3: _t->sigChangedState(); break;
        case 4: _t->onRefreshCoreTemp(); break;
        case 5: _t->syncToSlave(); break;
        case 6: _t->onSyncToSlave((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< QVariantMap(*)>(_a[2])),(*reinterpret_cast< QVariantMap(*)>(_a[3]))); break;
        case 7: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setConnectedGpr(); break;
        case 9: _t->setDisconnectedGpr(); break;
        case 10: _t->startMonitor(); break;
        case 11: _t->stopMonitor(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CORETEMP_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CORETEMP_SERVICE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CORETEMP_SERVICE,
      qt_meta_data_CORETEMP_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CORETEMP_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CORETEMP_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CORETEMP_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CORETEMP_SERVICE))
        return static_cast<void*>(const_cast< CORETEMP_SERVICE*>(this));
    return QObject::qt_metacast(_clname);
}

int CORETEMP_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CORETEMP_SERVICE::sigSyncToSlave(QVariantMap _t1, QVariantMap _t2, QVariantMap _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CORETEMP_SERVICE::sigStateLocal(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CORETEMP_SERVICE::sigStateOther(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CORETEMP_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
