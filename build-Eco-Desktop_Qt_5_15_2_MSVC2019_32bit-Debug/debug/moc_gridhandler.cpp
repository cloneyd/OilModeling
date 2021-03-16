/****************************************************************************
** Meta object code from reading C++ file 'gridhandler.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Eco/gridhandler.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gridhandler.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GridHandler_t {
    QByteArrayData data[29];
    char stringdata0[348];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GridHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GridHandler_t qt_meta_stringdata_GridHandler = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GridHandler"
QT_MOC_LITERAL(1, 12, 11), // "gridChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 39), // "QVector<QVector<QPair<bool,QP..."
QT_MOC_LITERAL(4, 65, 4), // "grid"
QT_MOC_LITERAL(5, 70, 12), // "xStepChanged"
QT_MOC_LITERAL(6, 83, 4), // "step"
QT_MOC_LITERAL(7, 88, 12), // "yStepChanged"
QT_MOC_LITERAL(8, 101, 12), // "markSearched"
QT_MOC_LITERAL(9, 114, 14), // "QPair<int,int>"
QT_MOC_LITERAL(10, 129, 10), // "mark_index"
QT_MOC_LITERAL(11, 140, 10), // "createGrid"
QT_MOC_LITERAL(12, 151, 8), // "QPixmap&"
QT_MOC_LITERAL(13, 160, 2), // "pm"
QT_MOC_LITERAL(14, 163, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(15, 180, 17), // "water_object_area"
QT_MOC_LITERAL(16, 198, 12), // "islands_area"
QT_MOC_LITERAL(17, 211, 18), // "std::list<QPointF>"
QT_MOC_LITERAL(18, 230, 8), // "mark_pos"
QT_MOC_LITERAL(19, 239, 5), // "color"
QT_MOC_LITERAL(20, 245, 10), // "line_width"
QT_MOC_LITERAL(21, 256, 10), // "deleteGrid"
QT_MOC_LITERAL(22, 267, 16), // "drawGridInPixmap"
QT_MOC_LITERAL(23, 284, 8), // "setScale"
QT_MOC_LITERAL(24, 293, 5), // "scale"
QT_MOC_LITERAL(25, 299, 12), // "setCellWidth"
QT_MOC_LITERAL(26, 312, 10), // "cell_width"
QT_MOC_LITERAL(27, 323, 13), // "setCellHeight"
QT_MOC_LITERAL(28, 337, 10) // "cellHeight"

    },
    "GridHandler\0gridChanged\0\0"
    "QVector<QVector<QPair<bool,QPointF> > >\0"
    "grid\0xStepChanged\0step\0yStepChanged\0"
    "markSearched\0QPair<int,int>\0mark_index\0"
    "createGrid\0QPixmap&\0pm\0QVector<QPointF>\0"
    "water_object_area\0islands_area\0"
    "std::list<QPointF>\0mark_pos\0color\0"
    "line_width\0deleteGrid\0drawGridInPixmap\0"
    "setScale\0scale\0setCellWidth\0cell_width\0"
    "setCellHeight\0cellHeight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GridHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,
       7,    1,   80,    2, 0x06 /* Public */,
       8,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    6,   86,    2, 0x0a /* Public */,
      11,    5,   99,    2, 0x2a /* Public | MethodCloned */,
      11,    4,  110,    2, 0x2a /* Public | MethodCloned */,
      21,    0,  119,    2, 0x0a /* Public */,
      22,    3,  120,    2, 0x0a /* Public */,
      23,    1,  127,    2, 0x0a /* Public */,
      25,    1,  130,    2, 0x0a /* Public */,
      27,    1,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14, 0x80000000 | 14, 0x80000000 | 17, QMetaType::QColor, QMetaType::Double,   13,   15,   16,   18,   19,   20,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14, 0x80000000 | 14, 0x80000000 | 17, QMetaType::QColor,   13,   15,   16,   18,   19,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14, 0x80000000 | 14, 0x80000000 | 17,   13,   15,   16,   18,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QColor, QMetaType::Double,   13,   19,   20,
    QMetaType::Void, QMetaType::Double,   24,
    QMetaType::Void, QMetaType::Double,   26,
    QMetaType::Void, QMetaType::Double,   28,

       0        // eod
};

void GridHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GridHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gridChanged((*reinterpret_cast< const QVector<QVector<QPair<bool,QPointF> > >(*)>(_a[1]))); break;
        case 1: _t->xStepChanged((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 2: _t->yStepChanged((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 3: _t->markSearched((*reinterpret_cast< QPair<int,int>(*)>(_a[1]))); break;
        case 4: _t->createGrid((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[2])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[3])),(*reinterpret_cast< const std::list<QPointF>(*)>(_a[4])),(*reinterpret_cast< const QColor(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 5: _t->createGrid((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[2])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[3])),(*reinterpret_cast< const std::list<QPointF>(*)>(_a[4])),(*reinterpret_cast< const QColor(*)>(_a[5]))); break;
        case 6: _t->createGrid((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[2])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[3])),(*reinterpret_cast< const std::list<QPointF>(*)>(_a[4]))); break;
        case 7: _t->deleteGrid(); break;
        case 8: _t->drawGridInPixmap((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 9: _t->setScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setCellWidth((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setCellHeight((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GridHandler::*)(const QVector<QVector<QPair<bool,QPointF>> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GridHandler::gridChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GridHandler::*)(const double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GridHandler::xStepChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GridHandler::*)(const double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GridHandler::yStepChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GridHandler::*)(QPair<int,int> ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GridHandler::markSearched)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GridHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GridHandler.data,
    qt_meta_data_GridHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GridHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GridHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GridHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GridHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void GridHandler::gridChanged(const QVector<QVector<QPair<bool,QPointF>> > & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GridHandler::xStepChanged(const double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GridHandler::yStepChanged(const double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GridHandler::markSearched(QPair<int,int> _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< GridHandler *>(this), &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
