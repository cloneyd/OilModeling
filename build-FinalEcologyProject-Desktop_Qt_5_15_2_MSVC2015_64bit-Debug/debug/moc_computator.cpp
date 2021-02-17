/****************************************************************************
** Meta object code from reading C++ file 'computator.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FinalEcologyProject/computator.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'computator.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Computator_t {
    QByteArrayData data[14];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Computator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Computator_t qt_meta_stringdata_Computator = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Computator"
QT_MOC_LITERAL(1, 11, 12), // "setupHeights"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 38), // "QVector<QVector<QPair<bool,do..."
QT_MOC_LITERAL(4, 64, 7), // "heights"
QT_MOC_LITERAL(5, 72, 32), // "displayXYSpeedVectorTableWidgets"
QT_MOC_LITERAL(6, 105, 18), // "setupXSpeedVectors"
QT_MOC_LITERAL(7, 124, 12), // "TableWidget*"
QT_MOC_LITERAL(8, 137, 5), // "table"
QT_MOC_LITERAL(9, 143, 18), // "setupYSpeedVectors"
QT_MOC_LITERAL(10, 162, 9), // "setARatio"
QT_MOC_LITERAL(11, 172, 5), // "value"
QT_MOC_LITERAL(12, 178, 9), // "setWOType"
QT_MOC_LITERAL(13, 188, 8) // "wo_index"

    },
    "Computator\0setupHeights\0\0"
    "QVector<QVector<QPair<bool,double> > >\0"
    "heights\0displayXYSpeedVectorTableWidgets\0"
    "setupXSpeedVectors\0TableWidget*\0table\0"
    "setupYSpeedVectors\0setARatio\0value\0"
    "setWOType\0wo_index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Computator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,
      10,    1,   54,    2, 0x0a /* Public */,
      12,    1,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Double,   11,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void Computator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Computator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setupHeights((*reinterpret_cast< const QVector<QVector<QPair<bool,double> > >(*)>(_a[1]))); break;
        case 1: _t->displayXYSpeedVectorTableWidgets(); break;
        case 2: _t->setupXSpeedVectors((*reinterpret_cast< TableWidget*(*)>(_a[1]))); break;
        case 3: _t->setupYSpeedVectors((*reinterpret_cast< TableWidget*(*)>(_a[1]))); break;
        case 4: _t->setARatio((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->setWOType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TableWidget* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TableWidget* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Computator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Computator.data,
    qt_meta_data_Computator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Computator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Computator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Computator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Computator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
