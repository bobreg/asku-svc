/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../common/application.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AskuApplication[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   16,   16,   16, 0x0a,
      44,   16,   16,   16, 0x0a,
      67,   65,   60,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AskuApplication[] = {
    "AskuApplication\0\0prepareToQuit()\0"
    "slotQuit()\0flushSettings()\0bool\0e\0"
    "event(QEvent*)\0"
};

void AskuApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AskuApplication *_t = static_cast<AskuApplication *>(_o);
        switch (_id) {
        case 0: _t->prepareToQuit(); break;
        case 1: _t->slotQuit(); break;
        case 2: _t->flushSettings(); break;
        case 3: { bool _r = _t->event((*reinterpret_cast< QEvent*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AskuApplication::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AskuApplication::staticMetaObject = {
    { &QCoreApplication::staticMetaObject, qt_meta_stringdata_AskuApplication,
      qt_meta_data_AskuApplication, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AskuApplication::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AskuApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AskuApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskuApplication))
        return static_cast<void*>(const_cast< AskuApplication*>(this));
    if (!strcmp(_clname, "Logger"))
        return static_cast< Logger*>(const_cast< AskuApplication*>(this));
    return QCoreApplication::qt_metacast(_clname);
}

int AskuApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCoreApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AskuApplication::prepareToQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
