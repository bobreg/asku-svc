/****************************************************************************
** Meta object code from reading C++ file 'svcmodule.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../svcmodule.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'svcmodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AskuSvcModule[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      35,   14,   14,   14, 0x0a,
      54,   51,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AskuSvcModule[] = {
    "AskuSvcModule\0\0makeLoggerMessage()\0"
    "prepareToQuit()\0,,\0"
    "eventFromPosToLog(QString,QString,QString)\0"
};

void AskuSvcModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AskuSvcModule *_t = static_cast<AskuSvcModule *>(_o);
        switch (_id) {
        case 0: _t->makeLoggerMessage(); break;
        case 1: _t->prepareToQuit(); break;
        case 2: _t->eventFromPosToLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AskuSvcModule::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AskuSvcModule::staticMetaObject = {
    { &AskuModule::staticMetaObject, qt_meta_stringdata_AskuSvcModule,
      qt_meta_data_AskuSvcModule, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AskuSvcModule::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AskuSvcModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AskuSvcModule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskuSvcModule))
        return static_cast<void*>(const_cast< AskuSvcModule*>(this));
    return AskuModule::qt_metacast(_clname);
}

int AskuSvcModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AskuModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
