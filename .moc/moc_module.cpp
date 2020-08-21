/****************************************************************************
** Meta object code from reading C++ file 'module.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../common/module.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'module.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AskuModule[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   28,   11,   11, 0x0a,
      59,   11,   11,   11, 0x2a,
      71,   28,   11,   11, 0x0a,
      91,   11,   11,   11, 0x2a,
     105,   28,   11,   11, 0x0a,
     124,   11,   11,   11, 0x2a,
     164,  137,   11,   11, 0x0a,
     224,  210,   11,   11, 0x2a,
     268,  263,   11,   11, 0x2a,
     300,  137,   11,   11, 0x0a,
     345,  210,   11,   11, 0x2a,
     383,  263,   11,   11, 0x2a,
     414,  137,   11,   11, 0x0a,
     457,  210,   11,   11, 0x2a,
     493,  263,   11,   11, 0x2a,
     522,  137,   11,   11, 0x0a,
     565,  210,   11,   11, 0x2a,
     601,  263,   11,   11, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_AskuModule[] = {
    "AskuModule\0\0flushSettings()\0idConnection\0"
    "sendHello(qint32)\0sendHello()\0"
    "sendStartup(qint32)\0sendStartup()\0"
    "sendByeBye(qint32)\0sendByeBye()\0"
    "data,idModule,idConnection\0"
    "sendControlCommand(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlCommand(QVariantMap,qint32)\0"
    "data\0sendControlCommand(QVariantMap)\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "sendControlAnswer(QVariantMap,qint32)\0"
    "sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0"
    "sendSyncMessage(QVariantMap,qint32,qint32)\0"
    "sendSyncMessage(QVariantMap,qint32)\0"
    "sendSyncMessage(QVariantMap)\0"
};

void AskuModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AskuModule *_t = static_cast<AskuModule *>(_o);
        switch (_id) {
        case 0: _t->flushSettings(); break;
        case 1: _t->sendHello((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->sendHello(); break;
        case 3: _t->sendStartup((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->sendStartup(); break;
        case 5: _t->sendByeBye((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 6: _t->sendByeBye(); break;
        case 7: _t->sendControlCommand((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 8: _t->sendControlCommand((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 9: _t->sendControlCommand((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 10: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 11: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 12: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 13: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 14: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 15: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 16: _t->sendSyncMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 17: _t->sendSyncMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 18: _t->sendSyncMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AskuModule::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AskuModule::staticMetaObject = {
    { &AskuConnectionManager::staticMetaObject, qt_meta_stringdata_AskuModule,
      qt_meta_data_AskuModule, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AskuModule::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AskuModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AskuModule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskuModule))
        return static_cast<void*>(const_cast< AskuModule*>(this));
    return AskuConnectionManager::qt_metacast(_clname);
}

int AskuModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AskuConnectionManager::qt_metacall(_c, _id, _a);
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
void AskuModule::flushSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
