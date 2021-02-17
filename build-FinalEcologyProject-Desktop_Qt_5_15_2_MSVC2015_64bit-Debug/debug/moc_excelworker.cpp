/****************************************************************************
** Meta object code from reading C++ file 'excelworker.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FinalEcologyProject/HelperEntities/excelworker.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'excelworker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExcelWorker_t {
    QByteArrayData data[10];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExcelWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExcelWorker_t qt_meta_stringdata_ExcelWorker = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ExcelWorker"
QT_MOC_LITERAL(1, 12, 17), // "updateHeightsFile"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 39), // "QVector<QVector<QPair<bool,QP..."
QT_MOC_LITERAL(4, 71, 4), // "grid"
QT_MOC_LITERAL(5, 76, 13), // "updateHeights"
QT_MOC_LITERAL(6, 90, 38), // "QVector<QVector<QPair<bool,do..."
QT_MOC_LITERAL(7, 129, 7), // "heights"
QT_MOC_LITERAL(8, 137, 15), // "saveHeightsFile"
QT_MOC_LITERAL(9, 153, 8) // "filepath"

    },
    "ExcelWorker\0updateHeightsFile\0\0"
    "QVector<QVector<QPair<bool,QPointF> > >\0"
    "grid\0updateHeights\0"
    "QVector<QVector<QPair<bool,double> > >\0"
    "heights\0saveHeightsFile\0filepath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExcelWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    1,   32,    2, 0x0a /* Public */,
       8,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void ExcelWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExcelWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateHeightsFile((*reinterpret_cast< const QVector<QVector<QPair<bool,QPointF> > >(*)>(_a[1]))); break;
        case 1: _t->updateHeights((*reinterpret_cast< const QVector<QVector<QPair<bool,double> > >(*)>(_a[1]))); break;
        case 2: _t->saveHeightsFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExcelWorker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ExcelWorker.data,
    qt_meta_data_ExcelWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExcelWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExcelWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExcelWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExcelWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
