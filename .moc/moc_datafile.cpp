/****************************************************************************
** Meta object code from reading C++ file 'datafile.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../datafile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datafile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DATE_FILE_THREAD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x05,
      49,   17,   17,   17, 0x25,
      64,   18,   17,   17, 0x05,
      90,   17,   17,   17, 0x25,
     106,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     125,  120,   17,   17, 0x0a,
     147,   17,   17,   17, 0x2a,
     170,  161,   17,   17, 0x0a,
     198,  189,   17,   17, 0x0a,
     229,  223,  218,   17, 0x0a,
     240,   17,   17,   17, 0x0a,
     248,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DATE_FILE_THREAD[] = {
    "DATE_FILE_THREAD\0\0error\0"
    "loadComplete(ErrorCodes)\0loadComplete()\0"
    "writeComplete(ErrorCodes)\0writeComplete()\0"
    "changedFile()\0data\0writeToFile(QVariant)\0"
    "writeToFile()\0readonly\0readFromFile(bool)\0"
    "filename\0changeFile(QString)\0bool\0"
    "write\0open(bool)\0close()\0quit()\0"
};

void DATE_FILE_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DATE_FILE_THREAD *_t = static_cast<DATE_FILE_THREAD *>(_o);
        switch (_id) {
        case 0: _t->loadComplete((*reinterpret_cast< ErrorCodes(*)>(_a[1]))); break;
        case 1: _t->loadComplete(); break;
        case 2: _t->writeComplete((*reinterpret_cast< ErrorCodes(*)>(_a[1]))); break;
        case 3: _t->writeComplete(); break;
        case 4: _t->changedFile(); break;
        case 5: _t->writeToFile((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 6: _t->writeToFile(); break;
        case 7: _t->readFromFile((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->changeFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { bool _r = _t->open((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: _t->close(); break;
        case 11: _t->quit(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DATE_FILE_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DATE_FILE_THREAD::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DATE_FILE_THREAD,
      qt_meta_data_DATE_FILE_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DATE_FILE_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DATE_FILE_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DATE_FILE_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DATE_FILE_THREAD))
        return static_cast<void*>(const_cast< DATE_FILE_THREAD*>(this));
    return QThread::qt_metacast(_clname);
}

int DATE_FILE_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void DATE_FILE_THREAD::loadComplete(ErrorCodes _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void DATE_FILE_THREAD::writeComplete(ErrorCodes _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void DATE_FILE_THREAD::changedFile()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
static const uint qt_meta_data_LOG_FILE_THREAD[] = {

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

static const char qt_meta_stringdata_LOG_FILE_THREAD[] = {
    "LOG_FILE_THREAD\0"
};

void LOG_FILE_THREAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LOG_FILE_THREAD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LOG_FILE_THREAD::staticMetaObject = {
    { &DATE_FILE_THREAD::staticMetaObject, qt_meta_stringdata_LOG_FILE_THREAD,
      qt_meta_data_LOG_FILE_THREAD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LOG_FILE_THREAD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LOG_FILE_THREAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LOG_FILE_THREAD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LOG_FILE_THREAD))
        return static_cast<void*>(const_cast< LOG_FILE_THREAD*>(this));
    return DATE_FILE_THREAD::qt_metacast(_clname);
}

int LOG_FILE_THREAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DATE_FILE_THREAD::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_DATE_FILE[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      31,   25,   10,   10, 0x05,
      56,   10,   10,   10, 0x25,

 // slots: signature, parameters, type, tag, flags
      71,   10,   10,   10, 0x0a,
      92,   87,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DATE_FILE[] = {
    "DATE_FILE\0\0changedFile()\0error\0"
    "loadComplete(ErrorCodes)\0loadComplete()\0"
    "onChangedDate()\0code\0onLoadComplete(ErrorCodes)\0"
};

void DATE_FILE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DATE_FILE *_t = static_cast<DATE_FILE *>(_o);
        switch (_id) {
        case 0: _t->changedFile(); break;
        case 1: _t->loadComplete((*reinterpret_cast< ErrorCodes(*)>(_a[1]))); break;
        case 2: _t->loadComplete(); break;
        case 3: _t->onChangedDate(); break;
        case 4: _t->onLoadComplete((*reinterpret_cast< ErrorCodes(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DATE_FILE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DATE_FILE::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DATE_FILE,
      qt_meta_data_DATE_FILE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DATE_FILE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DATE_FILE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DATE_FILE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DATE_FILE))
        return static_cast<void*>(const_cast< DATE_FILE*>(this));
    return QObject::qt_metacast(_clname);
}

int DATE_FILE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DATE_FILE::changedFile()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DATE_FILE::loadComplete(ErrorCodes _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_LOG_FILE[] = {

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

static const char qt_meta_stringdata_LOG_FILE[] = {
    "LOG_FILE\0"
};

void LOG_FILE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LOG_FILE::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LOG_FILE::staticMetaObject = {
    { &DATE_FILE::staticMetaObject, qt_meta_stringdata_LOG_FILE,
      qt_meta_data_LOG_FILE, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LOG_FILE::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LOG_FILE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LOG_FILE::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LOG_FILE))
        return static_cast<void*>(const_cast< LOG_FILE*>(this));
    return DATE_FILE::qt_metacast(_clname);
}

int LOG_FILE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DATE_FILE::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
