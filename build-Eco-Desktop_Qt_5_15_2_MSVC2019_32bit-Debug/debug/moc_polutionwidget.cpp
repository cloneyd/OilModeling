/****************************************************************************
** Meta object code from reading C++ file 'polutionwidget.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Eco/polutionwidget.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'polutionwidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PolutionWidget_t {
    QByteArrayData data[15];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PolutionWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PolutionWidget_t qt_meta_stringdata_PolutionWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PolutionWidget"
QT_MOC_LITERAL(1, 15, 13), // "sourceCreated"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 41), // "std::variant<PointSource,Diff..."
QT_MOC_LITERAL(4, 72, 6), // "source"
QT_MOC_LITERAL(5, 79, 23), // "QVector<PolutionMatter>"
QT_MOC_LITERAL(6, 103, 7), // "matters"
QT_MOC_LITERAL(7, 111, 13), // "sourceUpdated"
QT_MOC_LITERAL(8, 125, 5), // "index"
QT_MOC_LITERAL(9, 131, 11), // "typeChanged"
QT_MOC_LITERAL(10, 143, 4), // "type"
QT_MOC_LITERAL(11, 148, 25), // "addNewMatterButtonPressed"
QT_MOC_LITERAL(12, 174, 33), // "deleteSelectedMatterButtonPre..."
QT_MOC_LITERAL(13, 208, 18), // "saveButtonAccepted"
QT_MOC_LITERAL(14, 227, 18) // "saveButtonRejected"

    },
    "PolutionWidget\0sourceCreated\0\0"
    "std::variant<PointSource,DiffusionSource>\0"
    "source\0QVector<PolutionMatter>\0matters\0"
    "sourceUpdated\0index\0typeChanged\0type\0"
    "addNewMatterButtonPressed\0"
    "deleteSelectedMatterButtonPressed\0"
    "saveButtonAccepted\0saveButtonRejected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PolutionWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       7,    3,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   61,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,
      13,    0,   66,    2, 0x08 /* Private */,
      14,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 5,    8,    4,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PolutionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PolutionWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sourceCreated((*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 1: _t->sourceUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 2: _t->typeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->addNewMatterButtonPressed(); break;
        case 4: _t->deleteSelectedMatterButtonPressed(); break;
        case 5: _t->saveButtonAccepted(); break;
        case 6: _t->saveButtonRejected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PolutionWidget::*)(const std::variant<PointSource,DiffusionSource> & , const QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolutionWidget::sourceCreated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PolutionWidget::*)(int , const std::variant<PointSource,DiffusionSource> & , const QVector<PolutionMatter> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolutionWidget::sourceUpdated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PolutionWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PolutionWidget.data,
    qt_meta_data_PolutionWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PolutionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PolutionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PolutionWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PolutionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PolutionWidget::sourceCreated(const std::variant<PointSource,DiffusionSource> & _t1, const QVector<PolutionMatter> & _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(const_cast< PolutionWidget *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PolutionWidget::sourceUpdated(int _t1, const std::variant<PointSource,DiffusionSource> & _t2, const QVector<PolutionMatter> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
