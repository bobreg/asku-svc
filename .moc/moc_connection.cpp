/****************************************************************************
** Meta object code from reading C++ file 'connection.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../common/connection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AskuConnectionManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      57,   23,   22,   22, 0x09,
     123,  110,   22,   22, 0x09,
     158,  110,   22,   22, 0x09,
     182,  110,   22,   22, 0x09,
     228,  209,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AskuConnectionManager[] = {
    "AskuConnectionManager\0\0"
    "idConnection,peerAddress,peerPort\0"
    "moduleConnectedInternal(qint32,QHostAddress,quint16)\0"
    "idConnection\0moduleDisconnectedInternal(qint32)\0"
    "moduleConnected(qint32)\0"
    "moduleDisconnected(qint32)\0"
    "idConnection,array\0"
    "moduleDataArrived(qint32,QByteArray)\0"
};

void AskuConnectionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AskuConnectionManager *_t = static_cast<AskuConnectionManager *>(_o);
        switch (_id) {
        case 0: _t->moduleConnectedInternal((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 1: _t->moduleDisconnectedInternal((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->moduleConnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 3: _t->moduleDisconnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->moduleDataArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AskuConnectionManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AskuConnectionManager::staticMetaObject = {
    { &TcpNetwork::staticMetaObject, qt_meta_stringdata_AskuConnectionManager,
      qt_meta_data_AskuConnectionManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AskuConnectionManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AskuConnectionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AskuConnectionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskuConnectionManager))
        return static_cast<void*>(const_cast< AskuConnectionManager*>(this));
    return TcpNetwork::qt_metacast(_clname);
}

int AskuConnectionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TcpNetwork::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
