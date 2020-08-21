/****************************************************************************
** Meta object code from reading C++ file 'pos.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_POS[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,    5,    4,    4, 0x05,
      91,   77,    4,    4, 0x25,
     134,  129,    4,    4, 0x25,
     165,    5,    4,    4, 0x05,
     208,   77,    4,    4, 0x25,
     244,  129,    4,    4, 0x25,
     279,  273,    4,    4, 0x05,
     305,    4,    4,    4, 0x05,
     324,    4,    4,    4, 0x05,
     344,    4,    4,    4, 0x05,
     372,  369,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     414,  411,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_POS[] = {
    "POS\0\0data,idModule,idConnection\0"
    "sendControlAnswer(QVariantMap,qint32,qint32)\0"
    "data,idModule\0sendControlAnswer(QVariantMap,qint32)\0"
    "data\0sendControlAnswer(QVariantMap)\0"
    "sendInfoMessage(QVariantMap,qint32,qint32)\0"
    "sendInfoMessage(QVariantMap,qint32)\0"
    "sendInfoMessage(QVariantMap)\0state\0"
    "sigState(AskuBinStateSet)\0sigOsvPerimetrOn()\0"
    "sigOsvPerimetrOff()\0perim_light_on_off(bool)\0"
    ",,\0sigEventToLog(QString,QString,QString)\0"
    "on\0onChangedMain(bool)\0"
};

void POS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        POS *_t = static_cast<POS *>(_o);
        switch (_id) {
        case 0: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 1: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 2: _t->sendControlAnswer((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 3: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3]))); break;
        case 4: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 5: _t->sendInfoMessage((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 6: _t->sigState((*reinterpret_cast< AskuBinStateSet(*)>(_a[1]))); break;
        case 7: _t->sigOsvPerimetrOn(); break;
        case 8: _t->sigOsvPerimetrOff(); break;
        case 9: _t->perim_light_on_off((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->sigEventToLog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: _t->onChangedMain((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData POS::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject POS::staticMetaObject = {
    { &POS_THREAD::staticMetaObject, qt_meta_stringdata_POS,
      qt_meta_data_POS, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &POS::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *POS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *POS::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_POS))
        return static_cast<void*>(const_cast< POS*>(this));
    return POS_THREAD::qt_metacast(_clname);
}

int POS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = POS_THREAD::qt_metacall(_c, _id, _a);
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
void POS::sendControlAnswer(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 3
void POS::sendInfoMessage(QVariantMap _t1, qint32 _t2, qint32 _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void POS::sigState(AskuBinStateSet _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void POS::sigOsvPerimetrOn()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void POS::sigOsvPerimetrOff()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void POS::perim_light_on_off(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void POS::sigEventToLog(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
