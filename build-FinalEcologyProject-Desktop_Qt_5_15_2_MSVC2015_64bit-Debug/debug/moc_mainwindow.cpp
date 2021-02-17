/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FinalEcologyProject/mainwindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[400];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "createGrid"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "filepath"
QT_MOC_LITERAL(4, 32, 13), // "updateFullMap"
QT_MOC_LITERAL(5, 46, 10), // "updateGrid"
QT_MOC_LITERAL(6, 57, 20), // "openMapVisualization"
QT_MOC_LITERAL(7, 78, 23), // "displayDeepsTableWidget"
QT_MOC_LITERAL(8, 102, 24), // "displaySpeedsTableWidget"
QT_MOC_LITERAL(9, 127, 14), // "saveMapAsExcel"
QT_MOC_LITERAL(10, 142, 20), // "loadMapButtonPressed"
QT_MOC_LITERAL(11, 163, 20), // "openMapButtonPressed"
QT_MOC_LITERAL(12, 184, 33), // "openMapVisualizationButtonPre..."
QT_MOC_LITERAL(13, 218, 27), // "saveMapAsExcelButtonPressed"
QT_MOC_LITERAL(14, 246, 27), // "saveMapAsImageButtonPressed"
QT_MOC_LITERAL(15, 274, 25), // "enterHeightsButtonPressed"
QT_MOC_LITERAL(16, 300, 30), // "enterSpeedVectorsButtonPressed"
QT_MOC_LITERAL(17, 331, 26), // "updateFullMapButtonPressed"
QT_MOC_LITERAL(18, 358, 23), // "updateGridButtonPressed"
QT_MOC_LITERAL(19, 382, 14), // "saveMapInLabel"
QT_MOC_LITERAL(20, 397, 2) // "pm"

    },
    "MainWindow\0createGrid\0\0filepath\0"
    "updateFullMap\0updateGrid\0openMapVisualization\0"
    "displayDeepsTableWidget\0"
    "displaySpeedsTableWidget\0saveMapAsExcel\0"
    "loadMapButtonPressed\0openMapButtonPressed\0"
    "openMapVisualizationButtonPressed\0"
    "saveMapAsExcelButtonPressed\0"
    "saveMapAsImageButtonPressed\0"
    "enterHeightsButtonPressed\0"
    "enterSpeedVectorsButtonPressed\0"
    "updateFullMapButtonPressed\0"
    "updateGridButtonPressed\0saveMapInLabel\0"
    "pm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    0,  102,    2, 0x06 /* Public */,
       5,    0,  103,    2, 0x06 /* Public */,
       6,    0,  104,    2, 0x06 /* Public */,
       7,    0,  105,    2, 0x06 /* Public */,
       8,    0,  106,    2, 0x06 /* Public */,
       9,    1,  107,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  110,    2, 0x0a /* Public */,
      11,    0,  111,    2, 0x0a /* Public */,
      12,    0,  112,    2, 0x0a /* Public */,
      13,    0,  113,    2, 0x0a /* Public */,
      14,    0,  114,    2, 0x0a /* Public */,
      15,    0,  115,    2, 0x0a /* Public */,
      16,    0,  116,    2, 0x0a /* Public */,
      17,    0,  117,    2, 0x0a /* Public */,
      18,    0,  118,    2, 0x0a /* Public */,
      19,    1,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createGrid((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->updateFullMap(); break;
        case 2: _t->updateGrid(); break;
        case 3: _t->openMapVisualization(); break;
        case 4: _t->displayDeepsTableWidget(); break;
        case 5: _t->displaySpeedsTableWidget(); break;
        case 6: _t->saveMapAsExcel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->loadMapButtonPressed(); break;
        case 8: _t->openMapButtonPressed(); break;
        case 9: _t->openMapVisualizationButtonPressed(); break;
        case 10: _t->saveMapAsExcelButtonPressed(); break;
        case 11: _t->saveMapAsImageButtonPressed(); break;
        case 12: _t->enterHeightsButtonPressed(); break;
        case 13: _t->enterSpeedVectorsButtonPressed(); break;
        case 14: _t->updateFullMapButtonPressed(); break;
        case 15: _t->updateGridButtonPressed(); break;
        case 16: _t->saveMapInLabel((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::createGrid)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateFullMap)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateGrid)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::openMapVisualization)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::displayDeepsTableWidget)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::displaySpeedsTableWidget)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::saveMapAsExcel)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::createGrid(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::updateFullMap()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::updateGrid()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::openMapVisualization()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::displayDeepsTableWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::displaySpeedsTableWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::saveMapAsExcel(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
