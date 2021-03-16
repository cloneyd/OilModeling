/****************************************************************************
** Meta object code from reading C++ file 'excelworker.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Eco/excelworker.hpp"
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
    QByteArrayData data[23];
    char stringdata0[369];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExcelWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExcelWorker_t qt_meta_stringdata_ExcelWorker = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ExcelWorker"
QT_MOC_LITERAL(1, 12, 13), // "heightsLoaded"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 39), // "QVector<QVector<QPair<bool,do..."
QT_MOC_LITERAL(4, 67, 7), // "heights"
QT_MOC_LITERAL(5, 75, 10), // "acceptGrid"
QT_MOC_LITERAL(6, 86, 39), // "QVector<QVector<QPair<bool,QP..."
QT_MOC_LITERAL(7, 126, 4), // "grid"
QT_MOC_LITERAL(8, 131, 13), // "updateHeights"
QT_MOC_LITERAL(9, 145, 38), // "QVector<QVector<QPair<bool,do..."
QT_MOC_LITERAL(10, 184, 15), // "saveHeightsFile"
QT_MOC_LITERAL(11, 200, 8), // "filepath"
QT_MOC_LITERAL(12, 209, 19), // "loadHeightsFromFile"
QT_MOC_LITERAL(13, 229, 9), // "file_path"
QT_MOC_LITERAL(14, 239, 14), // "updateUXSpeeds"
QT_MOC_LITERAL(15, 254, 25), // "QVector<QVector<double> >"
QT_MOC_LITERAL(16, 280, 6), // "speeds"
QT_MOC_LITERAL(17, 287, 14), // "updateUYSpeeds"
QT_MOC_LITERAL(18, 302, 15), // "updateU0XSpeeds"
QT_MOC_LITERAL(19, 318, 15), // "updateU0YSpeeds"
QT_MOC_LITERAL(20, 334, 7), // "updateU"
QT_MOC_LITERAL(21, 342, 8), // "updateU0"
QT_MOC_LITERAL(22, 351, 17) // "saveSpeedsAsExcel"

    },
    "ExcelWorker\0heightsLoaded\0\0"
    "QVector<QVector<QPair<bool,double> > >&\0"
    "heights\0acceptGrid\0"
    "QVector<QVector<QPair<bool,QPointF> > >\0"
    "grid\0updateHeights\0"
    "QVector<QVector<QPair<bool,double> > >\0"
    "saveHeightsFile\0filepath\0loadHeightsFromFile\0"
    "file_path\0updateUXSpeeds\0"
    "QVector<QVector<double> >\0speeds\0"
    "updateUYSpeeds\0updateU0XSpeeds\0"
    "updateU0YSpeeds\0updateU\0updateU0\0"
    "saveSpeedsAsExcel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExcelWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   77,    2, 0x0a /* Public */,
       8,    1,   80,    2, 0x0a /* Public */,
      10,    1,   83,    2, 0x0a /* Public */,
      12,    1,   86,    2, 0x0a /* Public */,
      14,    1,   89,    2, 0x0a /* Public */,
      17,    1,   92,    2, 0x0a /* Public */,
      18,    1,   95,    2, 0x0a /* Public */,
      19,    1,   98,    2, 0x0a /* Public */,
      20,    1,  101,    2, 0x0a /* Public */,
      21,    1,  104,    2, 0x0a /* Public */,
      22,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,    4,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void ExcelWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExcelWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->heightsLoaded((*reinterpret_cast< QVector<QVector<QPair<bool,double> > >(*)>(_a[1]))); break;
        case 1: _t->acceptGrid((*reinterpret_cast< const QVector<QVector<QPair<bool,QPointF> > >(*)>(_a[1]))); break;
        case 2: _t->updateHeights((*reinterpret_cast< const QVector<QVector<QPair<bool,double> > >(*)>(_a[1]))); break;
        case 3: _t->saveHeightsFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->loadHeightsFromFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateUXSpeeds((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 6: _t->updateUYSpeeds((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 7: _t->updateU0XSpeeds((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 8: _t->updateU0YSpeeds((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 9: _t->updateU((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 10: _t->updateU0((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 11: _t->saveSpeedsAsExcel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExcelWorker::*)(QVector<QVector<QPair<bool,double>> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ExcelWorker::heightsLoaded)) {
                *result = 0;
                return;
            }
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ExcelWorker::heightsLoaded(QVector<QVector<QPair<bool,double>> > & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
