/****************************************************************************
** Meta object code from reading C++ file 'gridcreatorwidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FinalEcologyProject/MapWithGridFiles/gridcreatorwidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gridcreatorwidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GridCreatorWidget_t {
    QByteArrayData data[20];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GridCreatorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GridCreatorWidget_t qt_meta_stringdata_GridCreatorWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "GridCreatorWidget"
QT_MOC_LITERAL(1, 18, 11), // "gridChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 39), // "QVector<QVector<QPair<bool,QP..."
QT_MOC_LITERAL(4, 71, 4), // "grid"
QT_MOC_LITERAL(5, 76, 14), // "saveMapInLabel"
QT_MOC_LITERAL(6, 91, 3), // "map"
QT_MOC_LITERAL(7, 95, 15), // "updateCellWidth"
QT_MOC_LITERAL(8, 111, 5), // "width"
QT_MOC_LITERAL(9, 117, 16), // "updateCellHeight"
QT_MOC_LITERAL(10, 134, 6), // "height"
QT_MOC_LITERAL(11, 141, 11), // "updateScale"
QT_MOC_LITERAL(12, 153, 5), // "scale"
QT_MOC_LITERAL(13, 159, 14), // "createGridArea"
QT_MOC_LITERAL(14, 174, 14), // "image_filepath"
QT_MOC_LITERAL(15, 189, 13), // "updateFullMap"
QT_MOC_LITERAL(16, 203, 10), // "updateGrid"
QT_MOC_LITERAL(17, 214, 17), // "tableWidgetClosed"
QT_MOC_LITERAL(18, 232, 12), // "TableWidget*"
QT_MOC_LITERAL(19, 245, 5) // "table"

    },
    "GridCreatorWidget\0gridChanged\0\0"
    "QVector<QVector<QPair<bool,QPointF> > >\0"
    "grid\0saveMapInLabel\0map\0updateCellWidth\0"
    "width\0updateCellHeight\0height\0updateScale\0"
    "scale\0createGridArea\0image_filepath\0"
    "updateFullMap\0updateGrid\0tableWidgetClosed\0"
    "TableWidget*\0table"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GridCreatorWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   65,    2, 0x0a /* Public */,
       9,    1,   68,    2, 0x0a /* Public */,
      11,    1,   71,    2, 0x0a /* Public */,
      13,    1,   74,    2, 0x0a /* Public */,
      15,    0,   77,    2, 0x0a /* Public */,
      16,    0,   78,    2, 0x0a /* Public */,
      17,    1,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QPixmap,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void, QMetaType::Double,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void GridCreatorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GridCreatorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gridChanged((*reinterpret_cast< const QVector<QVector<QPair<bool,QPointF> > >(*)>(_a[1]))); break;
        case 1: _t->saveMapInLabel((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: _t->updateCellWidth((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->updateCellHeight((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->updateScale((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->createGridArea((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->updateFullMap(); break;
        case 7: _t->updateGrid(); break;
        case 8: _t->tableWidgetClosed((*reinterpret_cast< TableWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
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
            using _t = void (GridCreatorWidget::*)(const QVector<QVector<QPair<bool,QPointF>> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GridCreatorWidget::gridChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GridCreatorWidget::*)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GridCreatorWidget::saveMapInLabel)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GridCreatorWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_GridCreatorWidget.data,
    qt_meta_data_GridCreatorWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GridCreatorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GridCreatorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GridCreatorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GridCreatorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GridCreatorWidget::gridChanged(const QVector<QVector<QPair<bool,QPointF>> > & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GridCreatorWidget::saveMapInLabel(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
