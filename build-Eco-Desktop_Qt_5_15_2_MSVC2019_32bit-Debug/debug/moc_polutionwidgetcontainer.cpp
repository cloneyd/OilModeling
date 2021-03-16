/****************************************************************************
** Meta object code from reading C++ file 'polutionwidgetcontainer.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Eco/polutionwidgetcontainer.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'polutionwidgetcontainer.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PolutionWidgetContainer_t {
    QByteArrayData data[17];
    char stringdata0[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PolutionWidgetContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PolutionWidgetContainer_t qt_meta_stringdata_PolutionWidgetContainer = {
    {
QT_MOC_LITERAL(0, 0, 23), // "PolutionWidgetContainer"
QT_MOC_LITERAL(1, 24, 13), // "getSourceInfo"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "index"
QT_MOC_LITERAL(4, 45, 42), // "std::variant<PointSource,Diff..."
QT_MOC_LITERAL(5, 88, 6), // "source"
QT_MOC_LITERAL(6, 95, 24), // "QVector<PolutionMatter>&"
QT_MOC_LITERAL(7, 120, 7), // "matters"
QT_MOC_LITERAL(8, 128, 13), // "sourceCreated"
QT_MOC_LITERAL(9, 142, 41), // "std::variant<PointSource,Diff..."
QT_MOC_LITERAL(10, 184, 23), // "QVector<PolutionMatter>"
QT_MOC_LITERAL(11, 208, 13), // "sourceUpdated"
QT_MOC_LITERAL(12, 222, 23), // "createNewPolutionWidget"
QT_MOC_LITERAL(13, 246, 21), // "displaySelectedSource"
QT_MOC_LITERAL(14, 268, 19), // "sourceCreatedSender"
QT_MOC_LITERAL(15, 288, 19), // "sourceUpdatedSender"
QT_MOC_LITERAL(16, 308, 16) // "heldWidgetClosed"

    },
    "PolutionWidgetContainer\0getSourceInfo\0"
    "\0index\0std::variant<PointSource,DiffusionSource>&\0"
    "source\0QVector<PolutionMatter>&\0matters\0"
    "sourceCreated\0std::variant<PointSource,DiffusionSource>\0"
    "QVector<PolutionMatter>\0sourceUpdated\0"
    "createNewPolutionWidget\0displaySelectedSource\0"
    "sourceCreatedSender\0sourceUpdatedSender\0"
    "heldWidgetClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PolutionWidgetContainer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       8,    2,   61,    2, 0x06 /* Public */,
      11,    3,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   73,    2, 0x0a /* Public */,
      13,    1,   74,    2, 0x0a /* Public */,
      14,    2,   77,    2, 0x08 /* Private */,
      15,    3,   82,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 10,    5,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9, 0x80000000 | 10,    3,    5,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 10,    5,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9, 0x80000000 | 10,    3,    5,    7,
    QMetaType::Void,

       0        // eod
};

void PolutionWidgetContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PolutionWidgetContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getSourceInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::variant<PointSource,DiffusionSource>(*)>(_a[2])),(*reinterpret_cast< QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 1: _t->sourceCreated((*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 2: _t->sourceUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 3: _t->createNewPolutionWidget(); break;
        case 4: _t->displaySelectedSource((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sourceCreatedSender((*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 6: _t->sourceUpdatedSender((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 7: _t->heldWidgetClosed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PolutionWidgetContainer::*)(int , std::variant<PointSource,DiffusionSource> & , QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolutionWidgetContainer::getSourceInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PolutionWidgetContainer::*)(const std::variant<PointSource,DiffusionSource> & , const QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolutionWidgetContainer::sourceCreated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PolutionWidgetContainer::*)(int , const std::variant<PointSource,DiffusionSource> & , const QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PolutionWidgetContainer::sourceUpdated)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PolutionWidgetContainer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PolutionWidgetContainer.data,
    qt_meta_data_PolutionWidgetContainer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PolutionWidgetContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PolutionWidgetContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PolutionWidgetContainer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PolutionWidgetContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PolutionWidgetContainer::getSourceInfo(int _t1, std::variant<PointSource,DiffusionSource> & _t2, QVector<PolutionMatter> & _t3)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(const_cast< PolutionWidgetContainer *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PolutionWidgetContainer::sourceCreated(const std::variant<PointSource,DiffusionSource> & _t1, const QVector<PolutionMatter> & _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(const_cast< PolutionWidgetContainer *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PolutionWidgetContainer::sourceUpdated(int _t1, const std::variant<PointSource,DiffusionSource> & _t2, const QVector<PolutionMatter> & _t3)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(const_cast< PolutionWidgetContainer *>(this), &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
