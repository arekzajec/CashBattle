/****************************************************************************
** Meta object code from reading C++ file 'OperatorPanel.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "OperatorPanel.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OperatorPanel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QButtonDesc_t {
    QByteArrayData data[3];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QButtonDesc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QButtonDesc_t qt_meta_stringdata_QButtonDesc = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QButtonDesc"
QT_MOC_LITERAL(1, 12, 15), // "released_signal"
QT_MOC_LITERAL(2, 28, 0) // ""

    },
    "QButtonDesc\0released_signal\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QButtonDesc[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void QButtonDesc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QButtonDesc *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->released_signal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QButtonDesc::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QButtonDesc::released_signal)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QButtonDesc::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_QButtonDesc.data,
    qt_meta_data_QButtonDesc,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QButtonDesc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QButtonDesc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QButtonDesc.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QButtonDesc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void QButtonDesc::released_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_QButtonDescGroup_t {
    QByteArrayData data[6];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QButtonDescGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QButtonDescGroup_t qt_meta_stringdata_QButtonDescGroup = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QButtonDescGroup"
QT_MOC_LITERAL(1, 17, 15), // "released_signal"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "ekey"
QT_MOC_LITERAL(4, 39, 3), // "key"
QT_MOC_LITERAL(5, 43, 13) // "released_slot"

    },
    "QButtonDescGroup\0released_signal\0\0"
    "ekey\0key\0released_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QButtonDescGroup[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void QButtonDescGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QButtonDescGroup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->released_signal((*reinterpret_cast< ekey(*)>(_a[1]))); break;
        case 1: _t->released_slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QButtonDescGroup::*)(ekey );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QButtonDescGroup::released_signal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QButtonDescGroup::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_QButtonDescGroup.data,
    qt_meta_data_QButtonDescGroup,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QButtonDescGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QButtonDescGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QButtonDescGroup.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QButtonDescGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QButtonDescGroup::released_signal(ekey _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_OperatorPanel_t {
    QByteArrayData data[5];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OperatorPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OperatorPanel_t qt_meta_stringdata_OperatorPanel = {
    {
QT_MOC_LITERAL(0, 0, 13), // "OperatorPanel"
QT_MOC_LITERAL(1, 14, 14), // "qbuttonhandler"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "ekey"
QT_MOC_LITERAL(4, 35, 3) // "key"

    },
    "OperatorPanel\0qbuttonhandler\0\0ekey\0"
    "key"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OperatorPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void OperatorPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OperatorPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->qbuttonhandler((*reinterpret_cast< ekey(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OperatorPanel::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_OperatorPanel.data,
    qt_meta_data_OperatorPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OperatorPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OperatorPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OperatorPanel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OperatorPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
