/****************************************************************************
** Meta object code from reading C++ file 'vospd_service.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vospd_service.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vospd_service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VOSPD_SERVICE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      46,   33,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   14,   14,   14, 0x09,
      95,   14,   14,   14, 0x09,
     128,  110,   14,   14, 0x09,
     183,  175,   14,   14, 0x09,
     232,  216,   14,   14, 0x09,
     276,  273,   14,   14, 0x09,
     302,  299,   14,   14, 0x0a,
     324,  316,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_VOSPD_SERVICE[] = {
    "VOSPD_SERVICE\0\0sigChangedState()\0"
    "state,values\0sigState(AskuBinStateSet,AskuValueSet)\0"
    "timeout()\0queryTimeout()\0data,address,port\0"
    "onDataArrived(QByteArray,QHostAddress,quint16)\0"
    "id,data\0onDataArrived(qint32,QByteArray)\0"
    "id,address,port\0"
    "onConnected(qint32,QHostAddress,quint16)\0"
    "id\0onDisconnected(qint32)\0on\0setMain(bool)\0"
    "channel\0onChangedAzimuthSource(quint32)\0"
};

void VOSPD_SERVICE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VOSPD_SERVICE *_t = static_cast<VOSPD_SERVICE *>(_o);
        switch (_id) {
        case 0: _t->sigChangedState(); break;
        case 1: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1])),(*reinterpret_cast< AskuValueSet(*)>(_a[2]))); break;
        case 2: _t->timeout(); break;
        case 3: _t->queryTimeout(); break;
        case 4: _t->onDataArrived((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 5: _t->onDataArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 6: _t->onConnected((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 7: _t->onDisconnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: _t->setMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->onChangedAzimuthSource((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VOSPD_SERVICE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VOSPD_SERVICE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VOSPD_SERVICE,
      qt_meta_data_VOSPD_SERVICE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VOSPD_SERVICE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VOSPD_SERVICE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VOSPD_SERVICE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VOSPD_SERVICE))
        return static_cast<void*>(const_cast< VOSPD_SERVICE*>(this));
    return QObject::qt_metacast(_clname);
}

int VOSPD_SERVICE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VOSPD_SERVICE::sigChangedState()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void VOSPD_SERVICE::sigState(AskuBinStateSet _t1, AskuValueSet _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
