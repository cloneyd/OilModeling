/****************************************************************************
** Meta object code from reading C++ file 'surfacecontainer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FinalEcologyProject/SurfaceFiles/surfacecontainer.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'surfacecontainer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SurfaceContainer_t {
    QByteArrayData data[15];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SurfaceContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SurfaceContainer_t qt_meta_stringdata_SurfaceContainer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SurfaceContainer"
QT_MOC_LITERAL(1, 17, 14), // "heightsChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 38), // "QVector<QVector<QPair<bool,do..."
QT_MOC_LITERAL(4, 72, 7), // "heights"
QT_MOC_LITERAL(5, 80, 9), // "setupGrid"
QT_MOC_LITERAL(6, 90, 39), // "QVector<QVector<QPair<bool,QP..."
QT_MOC_LITERAL(7, 130, 4), // "grid"
QT_MOC_LITERAL(8, 135, 16), // "setupTableWidget"
QT_MOC_LITERAL(9, 152, 12), // "setupHeights"
QT_MOC_LITERAL(10, 165, 12), // "TableWidget*"
QT_MOC_LITERAL(11, 178, 5), // "table"
QT_MOC_LITERAL(12, 184, 10), // "setupScale"
QT_MOC_LITERAL(13, 195, 5), // "scale"
QT_MOC_LITERAL(14, 201, 10) // "showWidget"

    },
    "SurfaceContainer\0heightsChanged\0\0"
    "QVector<QVector<QPair<bool,double> > >\0"
    "heights\0setupGrid\0"
    "QVector<QVector<QPair<bool,QPointF> > >\0"
    "grid\0setupTableWidget\0setupHeights\0"
    "TableWidget*\0table\0setupScale\0scale\0"
    "showWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SurfaceContainer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   47,    2, 0x0a /* Public */,
       8,    0,   50,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,
      12,    1,   54,    2, 0x0a /* Public */,
      14,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void,

       0        // eod
};

void SurfaceContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SurfaceContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->heightsChanged((*reinterpret_cast< const QVector<QVector<QPair<bool,double> > >(*)>(_a[1]))); break;
        case 1: _t->setupGrid((*reinterpret_cast< const QVector<QVector<QPair<bool,QPointF> > >(*)>(_a[1]))); break;
        case 2: _t->setupTableWidget(); break;
        case 3: _t->setupHeights((*reinterpret_cast< TableWidget*(*)>(_a[1]))); break;
        case 4: _t->setupScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->showWidget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TableWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SurfaceContainer::*)(const QVector<QVector<QPair<bool,double>> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SurfaceContainer::heightsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SurfaceContainer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SurfaceContainer.data,
    qt_meta_data_SurfaceContainer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SurfaceContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SurfaceContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SurfaceContainer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SurfaceContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SurfaceContainer::heightsChanged(const QVector<QVector<QPair<bool,double>> > & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
