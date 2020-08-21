/****************************************************************************
** Meta object code from reading C++ file 'canalasku_phase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../canalasku_phase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canalasku_phase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModulePhasing[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   15,   14,   14, 0x05,
      57,   51,   14,   14, 0x05,
      94,   74,   14,   14, 0x05,
     138,  123,   14,   14, 0x25,
     168,  162,   14,   14, 0x25,
     188,   14,   14,   14, 0x25,
     217,  205,   14,   14, 0x05,
     250,  242,   14,   14, 0x05,
     267,   14,   14,   14, 0x05,
     301,  280,   14,   14, 0x05,
     343,  331,   14,   14, 0x05,
     377,  371,   14,   14, 0x25,

 // slots: signature, parameters, type, tag, flags
     398,   14,   14,   14, 0x09,
     408,  280,   14,   14, 0x0a,
     433,   14,   14,   14, 0x0a,
     446,   74,   14,   14, 0x0a,
     470,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ModulePhasing[] = {
    "ModulePhasing\0\0state,status\0"
    "sigStatus(int,QString)\0value\0"
    "sigProgress(int)\0n_prd,n_module,avto\0"
    "sigPhaseUpdate(int,int,bool)\0"
    "n_prd,n_module\0sigPhaseUpdate(int,int)\0"
    "n_prd\0sigPhaseUpdate(int)\0sigPhaseUpdate()\0"
    "value,valid\0sigOscPhase(double,bool)\0"
    "avtoOsc\0sigShowDlg(bool)\0sigHideDlg()\0"
    "n_prd,n_module,value\0sigPhaseValue(int,int,double)\0"
    "state,error\0phasingState(qint32,qint32)\0"
    "state\0phasingState(qint32)\0timeout()\0"
    "slotNext(int,int,double)\0slotCancel()\0"
    "slotStart(int,int,bool)\0slotStop()\0"
};

void ModulePhasing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModulePhasing *_t = static_cast<ModulePhasing *>(_o);
        switch (_id) {
        case 0: _t->sigStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sigProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sigPhaseUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->sigPhaseUpdate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sigPhaseUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sigPhaseUpdate(); break;
        case 6: _t->sigOscPhase((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->sigShowDlg((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->sigHideDlg(); break;
        case 9: _t->sigPhaseValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 10: _t->phasingState((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 11: _t->phasingState((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 12: _t->timeout(); break;
        case 13: _t->slotNext((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 14: _t->slotCancel(); break;
        case 15: _t->slotStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 16: _t->slotStop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ModulePhasing::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ModulePhasing::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModulePhasing,
      qt_meta_data_ModulePhasing, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModulePhasing::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModulePhasing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModulePhasing::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModulePhasing))
        return static_cast<void*>(const_cast< ModulePhasing*>(this));
    return QObject::qt_metacast(_clname);
}

int ModulePhasing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ModulePhasing::sigStatus(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModulePhasing::sigProgress(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ModulePhasing::sigPhaseUpdate(int _t1, int _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 6
void ModulePhasing::sigOscPhase(double _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ModulePhasing::sigShowDlg(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ModulePhasing::sigHideDlg()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void ModulePhasing::sigPhaseValue(int _t1, int _t2, double _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ModulePhasing::phasingState(qint32 _t1, qint32 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
