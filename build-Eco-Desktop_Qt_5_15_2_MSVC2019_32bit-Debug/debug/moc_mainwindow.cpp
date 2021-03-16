/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Eco/mainwindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
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
    QByteArrayData data[96];
    char stringdata0[1707];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "setupTable"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "QTableWidget&"
QT_MOC_LITERAL(4, 37, 5), // "table"
QT_MOC_LITERAL(5, 43, 10), // "createGrid"
QT_MOC_LITERAL(6, 54, 8), // "QPixmap&"
QT_MOC_LITERAL(7, 63, 2), // "pm"
QT_MOC_LITERAL(8, 66, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(9, 83, 17), // "water_object_area"
QT_MOC_LITERAL(10, 101, 12), // "islands_area"
QT_MOC_LITERAL(11, 114, 18), // "std::list<QPointF>"
QT_MOC_LITERAL(12, 133, 8), // "mark_pos"
QT_MOC_LITERAL(13, 142, 5), // "color"
QT_MOC_LITERAL(14, 148, 10), // "line_width"
QT_MOC_LITERAL(15, 159, 16), // "drawGridInPixmap"
QT_MOC_LITERAL(16, 176, 3), // "map"
QT_MOC_LITERAL(17, 180, 10), // "deleteGrid"
QT_MOC_LITERAL(18, 191, 20), // "saveHeightsFromTable"
QT_MOC_LITERAL(19, 212, 20), // "saveXSpeedsFromTable"
QT_MOC_LITERAL(20, 233, 20), // "saveYSpeedsFromTable"
QT_MOC_LITERAL(21, 254, 16), // "sendAzimuthState"
QT_MOC_LITERAL(22, 271, 18), // "QPair<double,bool>"
QT_MOC_LITERAL(23, 290, 4), // "pair"
QT_MOC_LITERAL(24, 295, 15), // "sendSystemState"
QT_MOC_LITERAL(25, 311, 15), // "QPair<int,bool>"
QT_MOC_LITERAL(26, 327, 23), // "sendComputationDistance"
QT_MOC_LITERAL(27, 351, 14), // "saveMapAsExcel"
QT_MOC_LITERAL(28, 366, 9), // "file_path"
QT_MOC_LITERAL(29, 376, 25), // "loadHeightsFromFileSender"
QT_MOC_LITERAL(30, 402, 17), // "saveSpeedsAsExcel"
QT_MOC_LITERAL(31, 420, 8), // "filepath"
QT_MOC_LITERAL(32, 429, 22), // "forceAbsSpeedDecompose"
QT_MOC_LITERAL(33, 452, 15), // "computateSpeeds"
QT_MOC_LITERAL(34, 468, 12), // "addNewSource"
QT_MOC_LITERAL(35, 481, 21), // "displaySelectedSource"
QT_MOC_LITERAL(36, 503, 5), // "index"
QT_MOC_LITERAL(37, 509, 20), // "deleteSelectedSource"
QT_MOC_LITERAL(38, 530, 11), // "getMapImage"
QT_MOC_LITERAL(39, 542, 7), // "QImage*"
QT_MOC_LITERAL(40, 550, 5), // "image"
QT_MOC_LITERAL(41, 556, 19), // "getEdittedMapPixmap"
QT_MOC_LITERAL(42, 576, 8), // "QPixmap*"
QT_MOC_LITERAL(43, 585, 9), // "loadImage"
QT_MOC_LITERAL(44, 595, 18), // "showPaintingWidget"
QT_MOC_LITERAL(45, 614, 11), // "setupTables"
QT_MOC_LITERAL(46, 626, 39), // "QVector<QVector<QPair<bool,QP..."
QT_MOC_LITERAL(47, 666, 4), // "grid"
QT_MOC_LITERAL(48, 671, 16), // "createGridSender"
QT_MOC_LITERAL(49, 688, 20), // "updateGridParameters"
QT_MOC_LITERAL(50, 709, 10), // "cell_width"
QT_MOC_LITERAL(51, 720, 11), // "cell_height"
QT_MOC_LITERAL(52, 732, 5), // "scale"
QT_MOC_LITERAL(53, 738, 16), // "deleteGridSender"
QT_MOC_LITERAL(54, 755, 22), // "drawGridInPixmapSender"
QT_MOC_LITERAL(55, 778, 26), // "saveHeightsFromTableSender"
QT_MOC_LITERAL(56, 805, 26), // "saveXSpeedsFromTableSender"
QT_MOC_LITERAL(57, 832, 26), // "saveYSpeedsFromTableSender"
QT_MOC_LITERAL(58, 859, 16), // "updateXWindTable"
QT_MOC_LITERAL(59, 876, 25), // "QVector<QVector<double> >"
QT_MOC_LITERAL(60, 902, 5), // "speed"
QT_MOC_LITERAL(61, 908, 16), // "updateYWindTable"
QT_MOC_LITERAL(62, 925, 33), // "openMapVisualizationButtonPre..."
QT_MOC_LITERAL(63, 959, 25), // "enterHeightsButtonPressed"
QT_MOC_LITERAL(64, 985, 22), // "updateDepthTableValues"
QT_MOC_LITERAL(65, 1008, 38), // "QVector<QVector<QPair<bool,do..."
QT_MOC_LITERAL(66, 1047, 7), // "heights"
QT_MOC_LITERAL(67, 1055, 17), // "enableSpeedsSaver"
QT_MOC_LITERAL(68, 1073, 26), // "setCurrentMapImageInPixmap"
QT_MOC_LITERAL(69, 1100, 10), // "setFlowMap"
QT_MOC_LITERAL(70, 1111, 16), // "addSourceToTable"
QT_MOC_LITERAL(71, 1128, 11), // "PointSource"
QT_MOC_LITERAL(72, 1140, 6), // "source"
QT_MOC_LITERAL(73, 1147, 23), // "QVector<PolutionMatter>"
QT_MOC_LITERAL(74, 1171, 7), // "matters"
QT_MOC_LITERAL(75, 1179, 15), // "DiffusionSource"
QT_MOC_LITERAL(76, 1195, 19), // "updateSourceInTable"
QT_MOC_LITERAL(77, 1215, 25), // "loadFromSiteButtonPressed"
QT_MOC_LITERAL(78, 1241, 23), // "loadFromPCButtonPressed"
QT_MOC_LITERAL(79, 1265, 32), // "loadHeightsFromFileButtonPressed"
QT_MOC_LITERAL(80, 1298, 22), // "editImageButtonPressed"
QT_MOC_LITERAL(81, 1321, 18), // "setImageInMapLabel"
QT_MOC_LITERAL(82, 1340, 29), // "saveHeightsTableButtonPressed"
QT_MOC_LITERAL(83, 1370, 29), // "enterSpeedVectorButtonPressed"
QT_MOC_LITERAL(84, 1400, 23), // "saveSpeedsButtonPressed"
QT_MOC_LITERAL(85, 1424, 20), // "saveMapButtonPressed"
QT_MOC_LITERAL(86, 1445, 28), // "computateSpeedsButtonPressed"
QT_MOC_LITERAL(87, 1474, 27), // "azimuthCheckBoxStateChanged"
QT_MOC_LITERAL(88, 1502, 8), // "newstate"
QT_MOC_LITERAL(89, 1511, 26), // "systemCheckBoxStateChanged"
QT_MOC_LITERAL(90, 1538, 35), // "forceAbsSpeedDecomposeButtonP..."
QT_MOC_LITERAL(91, 1574, 19), // "azimuthValueChanged"
QT_MOC_LITERAL(92, 1594, 18), // "systemIndexChanged"
QT_MOC_LITERAL(93, 1613, 25), // "addNewSourceButtonPressed"
QT_MOC_LITERAL(94, 1639, 34), // "displaySelectedSourceButtonPr..."
QT_MOC_LITERAL(95, 1674, 32) // "deleteSelectedSouceButtonPressed"

    },
    "MainWindow\0setupTable\0\0QTableWidget&\0"
    "table\0createGrid\0QPixmap&\0pm\0"
    "QVector<QPointF>\0water_object_area\0"
    "islands_area\0std::list<QPointF>\0"
    "mark_pos\0color\0line_width\0drawGridInPixmap\0"
    "map\0deleteGrid\0saveHeightsFromTable\0"
    "saveXSpeedsFromTable\0saveYSpeedsFromTable\0"
    "sendAzimuthState\0QPair<double,bool>\0"
    "pair\0sendSystemState\0QPair<int,bool>\0"
    "sendComputationDistance\0saveMapAsExcel\0"
    "file_path\0loadHeightsFromFileSender\0"
    "saveSpeedsAsExcel\0filepath\0"
    "forceAbsSpeedDecompose\0computateSpeeds\0"
    "addNewSource\0displaySelectedSource\0"
    "index\0deleteSelectedSource\0getMapImage\0"
    "QImage*\0image\0getEdittedMapPixmap\0"
    "QPixmap*\0loadImage\0showPaintingWidget\0"
    "setupTables\0QVector<QVector<QPair<bool,QPointF> > >\0"
    "grid\0createGridSender\0updateGridParameters\0"
    "cell_width\0cell_height\0scale\0"
    "deleteGridSender\0drawGridInPixmapSender\0"
    "saveHeightsFromTableSender\0"
    "saveXSpeedsFromTableSender\0"
    "saveYSpeedsFromTableSender\0updateXWindTable\0"
    "QVector<QVector<double> >\0speed\0"
    "updateYWindTable\0openMapVisualizationButtonPressed\0"
    "enterHeightsButtonPressed\0"
    "updateDepthTableValues\0"
    "QVector<QVector<QPair<bool,double> > >\0"
    "heights\0enableSpeedsSaver\0"
    "setCurrentMapImageInPixmap\0setFlowMap\0"
    "addSourceToTable\0PointSource\0source\0"
    "QVector<PolutionMatter>\0matters\0"
    "DiffusionSource\0updateSourceInTable\0"
    "loadFromSiteButtonPressed\0"
    "loadFromPCButtonPressed\0"
    "loadHeightsFromFileButtonPressed\0"
    "editImageButtonPressed\0setImageInMapLabel\0"
    "saveHeightsTableButtonPressed\0"
    "enterSpeedVectorButtonPressed\0"
    "saveSpeedsButtonPressed\0saveMapButtonPressed\0"
    "computateSpeedsButtonPressed\0"
    "azimuthCheckBoxStateChanged\0newstate\0"
    "systemCheckBoxStateChanged\0"
    "forceAbsSpeedDecomposeButtonPressed\0"
    "azimuthValueChanged\0systemIndexChanged\0"
    "addNewSourceButtonPressed\0"
    "displaySelectedSourceButtonPressed\0"
    "deleteSelectedSouceButtonPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      61,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      23,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  319,    2, 0x06 /* Public */,
       5,    6,  322,    2, 0x06 /* Public */,
      15,    3,  335,    2, 0x06 /* Public */,
      17,    0,  342,    2, 0x06 /* Public */,
      18,    1,  343,    2, 0x06 /* Public */,
      19,    1,  346,    2, 0x06 /* Public */,
      20,    1,  349,    2, 0x06 /* Public */,
      21,    1,  352,    2, 0x06 /* Public */,
      24,    1,  355,    2, 0x06 /* Public */,
      26,    1,  358,    2, 0x06 /* Public */,
      27,    1,  361,    2, 0x06 /* Public */,
      29,    1,  364,    2, 0x06 /* Public */,
      30,    1,  367,    2, 0x06 /* Public */,
      32,    0,  370,    2, 0x06 /* Public */,
      33,    0,  371,    2, 0x06 /* Public */,
      34,    0,  372,    2, 0x06 /* Public */,
      35,    1,  373,    2, 0x06 /* Public */,
      37,    1,  376,    2, 0x06 /* Public */,
      38,    1,  379,    2, 0x06 /* Public */,
      41,    1,  382,    2, 0x06 /* Public */,
      43,    1,  385,    2, 0x06 /* Public */,
      43,    1,  388,    2, 0x06 /* Public */,
      44,    0,  391,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      45,    1,  392,    2, 0x0a /* Public */,
      48,    6,  395,    2, 0x0a /* Public */,
      49,    3,  408,    2, 0x0a /* Public */,
      53,    0,  415,    2, 0x0a /* Public */,
      54,    3,  416,    2, 0x0a /* Public */,
      55,    1,  423,    2, 0x0a /* Public */,
      56,    1,  426,    2, 0x0a /* Public */,
      57,    1,  429,    2, 0x0a /* Public */,
      58,    1,  432,    2, 0x0a /* Public */,
      61,    1,  435,    2, 0x0a /* Public */,
      62,    0,  438,    2, 0x0a /* Public */,
      63,    0,  439,    2, 0x0a /* Public */,
      64,    1,  440,    2, 0x0a /* Public */,
      67,    0,  443,    2, 0x0a /* Public */,
      68,    1,  444,    2, 0x0a /* Public */,
      69,    1,  447,    2, 0x0a /* Public */,
      70,    2,  450,    2, 0x0a /* Public */,
      70,    2,  455,    2, 0x0a /* Public */,
      76,    3,  460,    2, 0x0a /* Public */,
      76,    3,  467,    2, 0x0a /* Public */,
      77,    0,  474,    2, 0x08 /* Private */,
      78,    0,  475,    2, 0x08 /* Private */,
      79,    0,  476,    2, 0x08 /* Private */,
      80,    0,  477,    2, 0x08 /* Private */,
      81,    1,  478,    2, 0x08 /* Private */,
      82,    0,  481,    2, 0x08 /* Private */,
      83,    0,  482,    2, 0x08 /* Private */,
      84,    0,  483,    2, 0x08 /* Private */,
      85,    0,  484,    2, 0x08 /* Private */,
      86,    0,  485,    2, 0x08 /* Private */,
      87,    1,  486,    2, 0x08 /* Private */,
      89,    1,  489,    2, 0x08 /* Private */,
      90,    0,  492,    2, 0x08 /* Private */,
      91,    1,  493,    2, 0x08 /* Private */,
      92,    1,  496,    2, 0x08 /* Private */,
      93,    0,  499,    2, 0x08 /* Private */,
      94,    0,  500,    2, 0x08 /* Private */,
      95,    0,  501,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 8, 0x80000000 | 11, QMetaType::QColor, QMetaType::Double,    7,    9,   10,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QColor, QMetaType::Double,   16,   13,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 25,   23,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   36,
    QMetaType::Void, QMetaType::Int,   36,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 42,   16,
    QMetaType::Void, QMetaType::QPixmap,   16,
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 46,   47,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8, 0x80000000 | 8, 0x80000000 | 11, QMetaType::QColor, QMetaType::Double,    7,    9,   10,   12,   13,   14,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   50,   51,   52,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QColor, QMetaType::Double,   16,   13,   14,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 59,   60,
    QMetaType::Void, 0x80000000 | 59,   60,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 65,   66,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,   16,
    QMetaType::Void, QMetaType::QPixmap,    7,
    QMetaType::Void, 0x80000000 | 71, 0x80000000 | 73,   72,   74,
    QMetaType::Void, 0x80000000 | 75, 0x80000000 | 73,   72,   74,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 71, 0x80000000 | 73,   36,   72,   74,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 75, 0x80000000 | 73,   36,   72,   74,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   40,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   88,
    QMetaType::Void, QMetaType::Bool,   88,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setupTable((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 1: _t->createGrid((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[2])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[3])),(*reinterpret_cast< const std::list<QPointF>(*)>(_a[4])),(*reinterpret_cast< const QColor(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 2: _t->drawGridInPixmap((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 3: _t->deleteGrid(); break;
        case 4: _t->saveHeightsFromTable((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 5: _t->saveXSpeedsFromTable((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 6: _t->saveYSpeedsFromTable((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 7: _t->sendAzimuthState((*reinterpret_cast< const QPair<double,bool>(*)>(_a[1]))); break;
        case 8: _t->sendSystemState((*reinterpret_cast< const QPair<int,bool>(*)>(_a[1]))); break;
        case 9: _t->sendComputationDistance((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->saveMapAsExcel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->loadHeightsFromFileSender((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->saveSpeedsAsExcel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->forceAbsSpeedDecompose(); break;
        case 14: _t->computateSpeeds(); break;
        case 15: _t->addNewSource(); break;
        case 16: _t->displaySelectedSource((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->deleteSelectedSource((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->getMapImage((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 19: _t->getEdittedMapPixmap((*reinterpret_cast< QPixmap*(*)>(_a[1]))); break;
        case 20: _t->loadImage((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 21: _t->loadImage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->showPaintingWidget(); break;
        case 23: _t->setupTables((*reinterpret_cast< const QVector<QVector<QPair<bool,QPointF> > >(*)>(_a[1]))); break;
        case 24: _t->createGridSender((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[2])),(*reinterpret_cast< const QVector<QPointF>(*)>(_a[3])),(*reinterpret_cast< const std::list<QPointF>(*)>(_a[4])),(*reinterpret_cast< const QColor(*)>(_a[5])),(*reinterpret_cast< double(*)>(_a[6]))); break;
        case 25: _t->updateGridParameters((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 26: _t->deleteGridSender(); break;
        case 27: _t->drawGridInPixmapSender((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 28: _t->saveHeightsFromTableSender((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 29: _t->saveXSpeedsFromTableSender((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 30: _t->saveYSpeedsFromTableSender((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 31: _t->updateXWindTable((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 32: _t->updateYWindTable((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 33: _t->openMapVisualizationButtonPressed(); break;
        case 34: _t->enterHeightsButtonPressed(); break;
        case 35: _t->updateDepthTableValues((*reinterpret_cast< const QVector<QVector<QPair<bool,double> > >(*)>(_a[1]))); break;
        case 36: _t->enableSpeedsSaver(); break;
        case 37: _t->setCurrentMapImageInPixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 38: _t->setFlowMap((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 39: _t->addSourceToTable((*reinterpret_cast< const PointSource(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 40: _t->addSourceToTable((*reinterpret_cast< const DiffusionSource(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 41: _t->updateSourceInTable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const PointSource(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 42: _t->updateSourceInTable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const DiffusionSource(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 43: _t->loadFromSiteButtonPressed(); break;
        case 44: _t->loadFromPCButtonPressed(); break;
        case 45: _t->loadHeightsFromFileButtonPressed(); break;
        case 46: _t->editImageButtonPressed(); break;
        case 47: _t->setImageInMapLabel((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 48: _t->saveHeightsTableButtonPressed(); break;
        case 49: _t->enterSpeedVectorButtonPressed(); break;
        case 50: _t->saveSpeedsButtonPressed(); break;
        case 51: _t->saveMapButtonPressed(); break;
        case 52: _t->computateSpeedsButtonPressed(); break;
        case 53: _t->azimuthCheckBoxStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->systemCheckBoxStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 55: _t->forceAbsSpeedDecomposeButtonPressed(); break;
        case 56: _t->azimuthValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 57: _t->systemIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 58: _t->addNewSourceButtonPressed(); break;
        case 59: _t->displaySelectedSourceButtonPressed(); break;
        case 60: _t->deleteSelectedSouceButtonPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 32:
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
            using _t = void (MainWindow::*)(QTableWidget & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::setupTable)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QPixmap & , const QVector<QPointF> & , const QVector<QPointF> & , const std::list<QPointF> & , const QColor & , double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::createGrid)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QPixmap & , const QColor & , double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::drawGridInPixmap)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::deleteGrid)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QTableWidget & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::saveHeightsFromTable)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QTableWidget & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::saveXSpeedsFromTable)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QTableWidget & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::saveYSpeedsFromTable)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QPair<double,bool> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendAzimuthState)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QPair<int,bool> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendSystemState)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendComputationDistance)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::saveMapAsExcel)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::loadHeightsFromFileSender)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::saveSpeedsAsExcel)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::forceAbsSpeedDecompose)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::computateSpeeds)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::addNewSource)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::displaySelectedSource)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::deleteSelectedSource)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QImage * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::getMapImage)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QPixmap * ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::getEdittedMapPixmap)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QPixmap & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::loadImage)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::loadImage)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::showPaintingWidget)) {
                *result = 22;
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
        if (_id < 61)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 61;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 61)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 61;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::setupTable(QTableWidget & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::createGrid(QPixmap & _t1, const QVector<QPointF> & _t2, const QVector<QPointF> & _t3, const std::list<QPointF> & _t4, const QColor & _t5, double _t6)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::drawGridInPixmap(QPixmap & _t1, const QColor & _t2, double _t3)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::deleteGrid()const
{
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::saveHeightsFromTable(QTableWidget & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::saveXSpeedsFromTable(QTableWidget & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::saveYSpeedsFromTable(QTableWidget & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MainWindow::sendAzimuthState(const QPair<double,bool> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::sendSystemState(const QPair<int,bool> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::sendComputationDistance(double _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::saveMapAsExcel(const QString & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::loadHeightsFromFileSender(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::saveSpeedsAsExcel(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::forceAbsSpeedDecompose()const
{
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void MainWindow::computateSpeeds()const
{
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void MainWindow::addNewSource()const
{
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void MainWindow::displaySelectedSource(int _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::deleteSelectedSource(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::getMapImage(QImage * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 18, _a);
}

// SIGNAL 19
void MainWindow::getEdittedMapPixmap(QPixmap * _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 19, _a);
}

// SIGNAL 20
void MainWindow::loadImage(const QPixmap & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 20, _a);
}

// SIGNAL 21
void MainWindow::loadImage(const QString & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 21, _a);
}

// SIGNAL 22
void MainWindow::showPaintingWidget()const
{
    QMetaObject::activate(const_cast< MainWindow *>(this), &staticMetaObject, 22, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
