/****************************************************************************
** Meta object code from reading C++ file 'paintingwidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Eco/paintingwidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintingwidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PaintingWidget_t {
    QByteArrayData data[51];
    char stringdata0[798];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintingWidget_t qt_meta_stringdata_PaintingWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PaintingWidget"
QT_MOC_LITERAL(1, 15, 12), // "imageChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "image"
QT_MOC_LITERAL(4, 35, 26), // "cellScaleParametersChanged"
QT_MOC_LITERAL(5, 62, 5), // "width"
QT_MOC_LITERAL(6, 68, 6), // "height"
QT_MOC_LITERAL(7, 75, 5), // "scale"
QT_MOC_LITERAL(8, 81, 10), // "createGrid"
QT_MOC_LITERAL(9, 92, 8), // "QPixmap&"
QT_MOC_LITERAL(10, 101, 2), // "pm"
QT_MOC_LITERAL(11, 104, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(12, 121, 17), // "water_object_area"
QT_MOC_LITERAL(13, 139, 12), // "islands_area"
QT_MOC_LITERAL(14, 152, 18), // "std::list<QPointF>"
QT_MOC_LITERAL(15, 171, 8), // "mark_pos"
QT_MOC_LITERAL(16, 180, 5), // "color"
QT_MOC_LITERAL(17, 186, 10), // "line_width"
QT_MOC_LITERAL(18, 197, 10), // "deleteGrid"
QT_MOC_LITERAL(19, 208, 16), // "drawGridInPixmap"
QT_MOC_LITERAL(20, 225, 3), // "map"
QT_MOC_LITERAL(21, 229, 19), // "getEdittedMapPixmap"
QT_MOC_LITERAL(22, 249, 8), // "QPixmap*"
QT_MOC_LITERAL(23, 258, 6), // "pixmap"
QT_MOC_LITERAL(24, 265, 11), // "getMapImage"
QT_MOC_LITERAL(25, 277, 7), // "QImage*"
QT_MOC_LITERAL(26, 285, 14), // "setScenePixmap"
QT_MOC_LITERAL(27, 300, 19), // "prepareGraphicsView"
QT_MOC_LITERAL(28, 320, 9), // "file_path"
QT_MOC_LITERAL(29, 330, 26), // "acceptChangesButtonPressed"
QT_MOC_LITERAL(30, 357, 30), // "discardAllChangesButtonPressed"
QT_MOC_LITERAL(31, 388, 22), // "updateMapButtonPressed"
QT_MOC_LITERAL(32, 411, 31), // "discardLastChandesButtonPressed"
QT_MOC_LITERAL(33, 443, 30), // "returnLastChangesButtonPressed"
QT_MOC_LITERAL(34, 474, 24), // "showChangesButtonPressed"
QT_MOC_LITERAL(35, 499, 10), // "PaintStyle"
QT_MOC_LITERAL(36, 510, 5), // "style"
QT_MOC_LITERAL(37, 516, 23), // "brushType1ButtonPressed"
QT_MOC_LITERAL(38, 540, 23), // "brushType2ButtonPressed"
QT_MOC_LITERAL(39, 564, 23), // "brushType3ButtonPressed"
QT_MOC_LITERAL(40, 588, 23), // "brushType4ButtonPressed"
QT_MOC_LITERAL(41, 612, 23), // "updateGridButtonPressed"
QT_MOC_LITERAL(42, 636, 23), // "enableGridButtonPressed"
QT_MOC_LITERAL(43, 660, 24), // "shadowNonWOButtonPressed"
QT_MOC_LITERAL(44, 685, 24), // "saveChangesButtonClicked"
QT_MOC_LITERAL(45, 710, 16), // "QAbstractButton*"
QT_MOC_LITERAL(46, 727, 3), // "btn"
QT_MOC_LITERAL(47, 731, 16), // "changeLogChanged"
QT_MOC_LITERAL(48, 748, 7), // "nwrites"
QT_MOC_LITERAL(49, 756, 21), // "changeLogStashChanged"
QT_MOC_LITERAL(50, 778, 19) // "markPositionChanged"

    },
    "PaintingWidget\0imageChanged\0\0image\0"
    "cellScaleParametersChanged\0width\0"
    "height\0scale\0createGrid\0QPixmap&\0pm\0"
    "QVector<QPointF>\0water_object_area\0"
    "islands_area\0std::list<QPointF>\0"
    "mark_pos\0color\0line_width\0deleteGrid\0"
    "drawGridInPixmap\0map\0getEdittedMapPixmap\0"
    "QPixmap*\0pixmap\0getMapImage\0QImage*\0"
    "setScenePixmap\0prepareGraphicsView\0"
    "file_path\0acceptChangesButtonPressed\0"
    "discardAllChangesButtonPressed\0"
    "updateMapButtonPressed\0"
    "discardLastChandesButtonPressed\0"
    "returnLastChangesButtonPressed\0"
    "showChangesButtonPressed\0PaintStyle\0"
    "style\0brushType1ButtonPressed\0"
    "brushType2ButtonPressed\0brushType3ButtonPressed\0"
    "brushType4ButtonPressed\0updateGridButtonPressed\0"
    "enableGridButtonPressed\0"
    "shadowNonWOButtonPressed\0"
    "saveChangesButtonClicked\0QAbstractButton*\0"
    "btn\0changeLogChanged\0nwrites\0"
    "changeLogStashChanged\0markPositionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintingWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  159,    2, 0x06 /* Public */,
       4,    3,  162,    2, 0x06 /* Public */,
       8,    6,  169,    2, 0x06 /* Public */,
      18,    0,  182,    2, 0x06 /* Public */,
      19,    3,  183,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    1,  190,    2, 0x0a /* Public */,
      21,    0,  193,    2, 0x2a /* Public | MethodCloned */,
      24,    1,  194,    2, 0x0a /* Public */,
      24,    0,  197,    2, 0x2a /* Public | MethodCloned */,
      26,    1,  198,    2, 0x0a /* Public */,
      27,    1,  201,    2, 0x0a /* Public */,
      29,    0,  204,    2, 0x08 /* Private */,
      30,    0,  205,    2, 0x08 /* Private */,
      31,    0,  206,    2, 0x08 /* Private */,
      32,    0,  207,    2, 0x08 /* Private */,
      33,    0,  208,    2, 0x08 /* Private */,
      34,    1,  209,    2, 0x08 /* Private */,
      34,    0,  212,    2, 0x28 /* Private | MethodCloned */,
      37,    0,  213,    2, 0x08 /* Private */,
      38,    0,  214,    2, 0x08 /* Private */,
      39,    0,  215,    2, 0x08 /* Private */,
      40,    0,  216,    2, 0x08 /* Private */,
      41,    0,  217,    2, 0x08 /* Private */,
      42,    0,  218,    2, 0x08 /* Private */,
      43,    0,  219,    2, 0x08 /* Private */,
      44,    1,  220,    2, 0x08 /* Private */,
      47,    1,  223,    2, 0x08 /* Private */,
      49,    1,  226,    2, 0x08 /* Private */,
      50,    0,  229,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 11, 0x80000000 | 14, QMetaType::QColor, QMetaType::Double,   10,   12,   13,   15,   16,   17,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QColor, QMetaType::Double,   20,   16,   17,

 // slots: parameters
    0x80000000 | 22, 0x80000000 | 22,   23,
    0x80000000 | 22,
    0x80000000 | 25, 0x80000000 | 25,    3,
    0x80000000 | 25,
    QMetaType::Void, QMetaType::QPixmap,   10,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QPixmap, 0x80000000 | 35,   36,
    QMetaType::QPixmap,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 45,   46,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void,

       0        // eod
};

void PaintingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PaintingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->imageChanged((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->cellScaleParametersChanged((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 2: _t->createGrid((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[2])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[3])),(*reinterpret_cast< const std::list<QPointF>(*)>(_a[4])),(*reinterpret_cast< const QColor(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 3: _t->deleteGrid(); break;
        case 4: _t->drawGridInPixmap((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: { QPixmap* _r = _t->getEdittedMapPixmap((*reinterpret_cast< QPixmap*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPixmap**>(_a[0]) = std::move(_r); }  break;
        case 6: { QPixmap* _r = _t->getEdittedMapPixmap();
            if (_a[0]) *reinterpret_cast< QPixmap**>(_a[0]) = std::move(_r); }  break;
        case 7: { QImage* _r = _t->getMapImage((*reinterpret_cast< QImage*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QImage**>(_a[0]) = std::move(_r); }  break;
        case 8: { QImage* _r = _t->getMapImage();
            if (_a[0]) *reinterpret_cast< QImage**>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setScenePixmap((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 10: _t->prepareGraphicsView((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->acceptChangesButtonPressed(); break;
        case 12: _t->discardAllChangesButtonPressed(); break;
        case 13: _t->updateMapButtonPressed(); break;
        case 14: _t->discardLastChandesButtonPressed(); break;
        case 15: _t->returnLastChangesButtonPressed(); break;
        case 16: { QPixmap _r = _t->showChangesButtonPressed((*reinterpret_cast< PaintStyle(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPixmap*>(_a[0]) = std::move(_r); }  break;
        case 17: { QPixmap _r = _t->showChangesButtonPressed();
            if (_a[0]) *reinterpret_cast< QPixmap*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->brushType1ButtonPressed(); break;
        case 19: _t->brushType2ButtonPressed(); break;
        case 20: _t->brushType3ButtonPressed(); break;
        case 21: _t->brushType4ButtonPressed(); break;
        case 22: _t->updateGridButtonPressed(); break;
        case 23: _t->enableGridButtonPressed(); break;
        case 24: _t->shadowNonWOButtonPressed(); break;
        case 25: _t->saveChangesButtonClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 26: _t->changeLogChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->changeLogStashChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->markPositionChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
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
            using _t = void (PaintingWidget::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintingWidget::imageChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PaintingWidget::*)(double , double , double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintingWidget::cellScaleParametersChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PaintingWidget::*)(QPixmap & , const QVector<QPointF> & , const QVector<QPointF> & , const std::list<QPointF> & , const QColor & , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintingWidget::createGrid)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PaintingWidget::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintingWidget::deleteGrid)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PaintingWidget::*)(QPixmap & , const QColor & , double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintingWidget::drawGridInPixmap)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PaintingWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PaintingWidget.data,
    qt_meta_data_PaintingWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PaintingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PaintingWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PaintingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void PaintingWidget::imageChanged(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PaintingWidget::cellScaleParametersChanged(double _t1, double _t2, double _t3)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(const_cast< PaintingWidget *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PaintingWidget::createGrid(QPixmap & _t1, const QVector<QPointF> & _t2, const QVector<QPointF> & _t3, const std::list<QPointF> & _t4, const QColor & _t5, double _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PaintingWidget::deleteGrid()const
{
    QMetaObject::activate(const_cast< PaintingWidget *>(this), &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PaintingWidget::drawGridInPixmap(QPixmap & _t1, const QColor & _t2, double _t3)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(const_cast< PaintingWidget *>(this), &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
