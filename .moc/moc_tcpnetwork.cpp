/****************************************************************************
** Meta object code from reading C++ file 'tcpnetwork.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../common/tcpnetwork.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpnetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TcpNetworkConnection[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_TcpNetworkConnection[] = {
    "TcpNetworkConnection\0"
};

void TcpNetworkConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TcpNetworkConnection::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TcpNetworkConnection::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_TcpNetworkConnection,
      qt_meta_data_TcpNetworkConnection, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TcpNetworkConnection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TcpNetworkConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TcpNetworkConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpNetworkConnection))
        return static_cast<void*>(const_cast< TcpNetworkConnection*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int TcpNetworkConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_TcpNetworkServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_TcpNetworkServer[] = {
    "TcpNetworkServer\0"
};

void TcpNetworkServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TcpNetworkServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TcpNetworkServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_TcpNetworkServer,
      qt_meta_data_TcpNetworkServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TcpNetworkServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TcpNetworkServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TcpNetworkServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpNetworkServer))
        return static_cast<void*>(const_cast< TcpNetworkServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int TcpNetworkServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_TcpNetwork[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x05,
      52,   11,   11,   11, 0x05,
      94,   70,   11,   11, 0x05,
     139,  136,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     163,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     195,   11,   11,   11, 0x08,
     207,   11,   11,   11, 0x08,
     226,   11,   11,   11, 0x08,
     249,   11,   11,   11, 0x08,
     268,  261,   11,   11, 0x08,
     293,  289,   11,   11, 0x08,
     329,   11,   11,   11, 0x08,
     348,   12,   11,   11, 0x0a,
     390,  377,   11,   11, 0x0a,
     420,  415,   11,   11, 0x0a,
     437,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TcpNetwork[] = {
    "TcpNetwork\0\0id,array\0"
    "dataArrived(qint32,QByteArray)\0"
    "sigConnectError()\0id,peerAddress,peerPort\0"
    "sigConnected(qint32,QHostAddress,quint16)\0"
    "id\0sigDisconnected(qint32)\0"
    "slotNewConnection()\0hostFound()\0"
    "connected()\0connectionClosed()\0"
    "delayedCloseFinished()\0readyRead()\0"
    "nbytes\0bytesWritten(qint64)\0err\0"
    "error(QAbstractSocket::SocketError)\0"
    "timeoutReconnect()\0sendReply(qint32,QByteArray)\0"
    "address,port\0slotConnect(QString,int)\0"
    "port\0slotConnect(int)\0slotDisconnect()\0"
};

void TcpNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TcpNetwork *_t = static_cast<TcpNetwork *>(_o);
        switch (_id) {
        case 0: _t->dataArrived((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->sigConnectError(); break;
        case 2: _t->sigConnected((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QHostAddress(*)>(_a[2])),(*reinterpret_cast< quint16(*)>(_a[3]))); break;
        case 3: _t->sigDisconnected((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->slotNewConnection(); break;
        case 5: _t->hostFound(); break;
        case 6: _t->connected(); break;
        case 7: _t->connectionClosed(); break;
        case 8: _t->delayedCloseFinished(); break;
        case 9: _t->readyRead(); break;
        case 10: _t->bytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 11: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 12: _t->timeoutReconnect(); break;
        case 13: _t->sendReply((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 14: _t->slotConnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->slotConnect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->slotDisconnect(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TcpNetwork::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TcpNetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TcpNetwork,
      qt_meta_data_TcpNetwork, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TcpNetwork::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TcpNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TcpNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpNetwork))
        return static_cast<void*>(const_cast< TcpNetwork*>(this));
    return QObject::qt_metacast(_clname);
}

int TcpNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void TcpNetwork::dataArrived(qint32 _t1, QByteArray _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpNetwork::sigConnectError()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void TcpNetwork::sigConnected(qint32 _t1, QHostAddress _t2, quint16 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TcpNetwork::sigDisconnected(qint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
