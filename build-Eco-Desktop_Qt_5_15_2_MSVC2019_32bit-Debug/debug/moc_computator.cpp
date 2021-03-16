/****************************************************************************
** Meta object code from reading C++ file 'computator.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Eco/computator.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'computator.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Computator_t {
    QByteArrayData data[69];
    char stringdata0[998];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Computator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Computator_t qt_meta_stringdata_Computator = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Computator"
QT_MOC_LITERAL(1, 11, 22), // "xWindProjectionChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 25), // "QVector<QVector<double> >"
QT_MOC_LITERAL(4, 61, 6), // "speeds"
QT_MOC_LITERAL(5, 68, 22), // "yWindProjectionChanged"
QT_MOC_LITERAL(6, 91, 14), // "uxSpeedChanged"
QT_MOC_LITERAL(7, 106, 6), // "xspeed"
QT_MOC_LITERAL(8, 113, 14), // "uySpeedChanged"
QT_MOC_LITERAL(9, 128, 6), // "yspeed"
QT_MOC_LITERAL(10, 135, 15), // "u0xSpeedChanged"
QT_MOC_LITERAL(11, 151, 15), // "u0ySpeedChanged"
QT_MOC_LITERAL(12, 167, 8), // "uChanged"
QT_MOC_LITERAL(13, 176, 5), // "speed"
QT_MOC_LITERAL(14, 182, 9), // "u0Changed"
QT_MOC_LITERAL(15, 192, 16), // "speedsComputated"
QT_MOC_LITERAL(16, 209, 18), // "getCurrentMapImage"
QT_MOC_LITERAL(17, 228, 8), // "QPixmap&"
QT_MOC_LITERAL(18, 237, 3), // "map"
QT_MOC_LITERAL(19, 241, 14), // "flowMapCreated"
QT_MOC_LITERAL(20, 256, 14), // "sourcesChanged"
QT_MOC_LITERAL(21, 271, 11), // "PointSource"
QT_MOC_LITERAL(22, 283, 6), // "source"
QT_MOC_LITERAL(23, 290, 23), // "QVector<PolutionMatter>"
QT_MOC_LITERAL(24, 314, 7), // "matters"
QT_MOC_LITERAL(25, 322, 15), // "DiffusionSource"
QT_MOC_LITERAL(26, 338, 13), // "sourceUpdated"
QT_MOC_LITERAL(27, 352, 5), // "index"
QT_MOC_LITERAL(28, 358, 9), // "setupGrid"
QT_MOC_LITERAL(29, 368, 39), // "QVector<QVector<QPair<bool,QP..."
QT_MOC_LITERAL(30, 408, 4), // "grid"
QT_MOC_LITERAL(31, 413, 12), // "setupHeights"
QT_MOC_LITERAL(32, 426, 38), // "QVector<QVector<QPair<bool,do..."
QT_MOC_LITERAL(33, 465, 7), // "heights"
QT_MOC_LITERAL(34, 473, 9), // "setARatio"
QT_MOC_LITERAL(35, 483, 5), // "ratio"
QT_MOC_LITERAL(36, 489, 9), // "setWOType"
QT_MOC_LITERAL(37, 499, 8), // "wo_index"
QT_MOC_LITERAL(38, 508, 22), // "acceptXSpeedsFromTable"
QT_MOC_LITERAL(39, 531, 13), // "QTableWidget&"
QT_MOC_LITERAL(40, 545, 5), // "table"
QT_MOC_LITERAL(41, 551, 22), // "acceptYSpeedsFromTable"
QT_MOC_LITERAL(42, 574, 11), // "acceptXStep"
QT_MOC_LITERAL(43, 586, 4), // "step"
QT_MOC_LITERAL(44, 591, 11), // "acceptYStep"
QT_MOC_LITERAL(45, 603, 13), // "acceptHorizon"
QT_MOC_LITERAL(46, 617, 7), // "horizon"
QT_MOC_LITERAL(47, 625, 18), // "acceptMarkPosition"
QT_MOC_LITERAL(48, 644, 14), // "QPair<int,int>"
QT_MOC_LITERAL(49, 659, 8), // "mark_pos"
QT_MOC_LITERAL(50, 668, 13), // "acceptKsiAtol"
QT_MOC_LITERAL(51, 682, 4), // "atol"
QT_MOC_LITERAL(52, 687, 14), // "acceptAbsSpeed"
QT_MOC_LITERAL(53, 702, 13), // "acceptAzimuth"
QT_MOC_LITERAL(54, 716, 18), // "QPair<double,bool>"
QT_MOC_LITERAL(55, 735, 4), // "pair"
QT_MOC_LITERAL(56, 740, 19), // "acceptWindDirection"
QT_MOC_LITERAL(57, 760, 15), // "QPair<int,bool>"
QT_MOC_LITERAL(58, 776, 14), // "acceptDistance"
QT_MOC_LITERAL(59, 791, 8), // "distance"
QT_MOC_LITERAL(60, 800, 14), // "giveSourceInfo"
QT_MOC_LITERAL(61, 815, 42), // "std::variant<PointSource,Diff..."
QT_MOC_LITERAL(62, 858, 24), // "QVector<PolutionMatter>&"
QT_MOC_LITERAL(63, 883, 12), // "addNewSource"
QT_MOC_LITERAL(64, 896, 41), // "std::variant<PointSource,Diff..."
QT_MOC_LITERAL(65, 938, 12), // "updateSource"
QT_MOC_LITERAL(66, 951, 12), // "deleteSource"
QT_MOC_LITERAL(67, 964, 17), // "decomposeAbsSpeed"
QT_MOC_LITERAL(68, 982, 15) // "computateSpeeds"

    },
    "Computator\0xWindProjectionChanged\0\0"
    "QVector<QVector<double> >\0speeds\0"
    "yWindProjectionChanged\0uxSpeedChanged\0"
    "xspeed\0uySpeedChanged\0yspeed\0"
    "u0xSpeedChanged\0u0ySpeedChanged\0"
    "uChanged\0speed\0u0Changed\0speedsComputated\0"
    "getCurrentMapImage\0QPixmap&\0map\0"
    "flowMapCreated\0sourcesChanged\0PointSource\0"
    "source\0QVector<PolutionMatter>\0matters\0"
    "DiffusionSource\0sourceUpdated\0index\0"
    "setupGrid\0QVector<QVector<QPair<bool,QPointF> > >\0"
    "grid\0setupHeights\0"
    "QVector<QVector<QPair<bool,double> > >\0"
    "heights\0setARatio\0ratio\0setWOType\0"
    "wo_index\0acceptXSpeedsFromTable\0"
    "QTableWidget&\0table\0acceptYSpeedsFromTable\0"
    "acceptXStep\0step\0acceptYStep\0acceptHorizon\0"
    "horizon\0acceptMarkPosition\0QPair<int,int>\0"
    "mark_pos\0acceptKsiAtol\0atol\0acceptAbsSpeed\0"
    "acceptAzimuth\0QPair<double,bool>\0pair\0"
    "acceptWindDirection\0QPair<int,bool>\0"
    "acceptDistance\0distance\0giveSourceInfo\0"
    "std::variant<PointSource,DiffusionSource>&\0"
    "QVector<PolutionMatter>&\0addNewSource\0"
    "std::variant<PointSource,DiffusionSource>\0"
    "updateSource\0deleteSource\0decomposeAbsSpeed\0"
    "computateSpeeds"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Computator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  194,    2, 0x06 /* Public */,
       5,    1,  197,    2, 0x06 /* Public */,
       6,    1,  200,    2, 0x06 /* Public */,
       8,    1,  203,    2, 0x06 /* Public */,
      10,    1,  206,    2, 0x06 /* Public */,
      11,    1,  209,    2, 0x06 /* Public */,
      12,    1,  212,    2, 0x06 /* Public */,
      14,    1,  215,    2, 0x06 /* Public */,
      15,    0,  218,    2, 0x06 /* Public */,
      16,    1,  219,    2, 0x06 /* Public */,
      19,    1,  222,    2, 0x06 /* Public */,
      20,    2,  225,    2, 0x06 /* Public */,
      20,    2,  230,    2, 0x06 /* Public */,
      26,    3,  235,    2, 0x06 /* Public */,
      26,    3,  242,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      28,    1,  249,    2, 0x0a /* Public */,
      31,    1,  252,    2, 0x0a /* Public */,
      34,    1,  255,    2, 0x0a /* Public */,
      36,    1,  258,    2, 0x0a /* Public */,
      38,    1,  261,    2, 0x0a /* Public */,
      41,    1,  264,    2, 0x0a /* Public */,
      42,    1,  267,    2, 0x0a /* Public */,
      44,    1,  270,    2, 0x0a /* Public */,
      45,    1,  273,    2, 0x0a /* Public */,
      47,    1,  276,    2, 0x0a /* Public */,
      50,    1,  279,    2, 0x0a /* Public */,
      52,    1,  282,    2, 0x0a /* Public */,
      53,    1,  285,    2, 0x0a /* Public */,
      56,    1,  288,    2, 0x0a /* Public */,
      58,    1,  291,    2, 0x0a /* Public */,
      60,    3,  294,    2, 0x0a /* Public */,
      63,    2,  301,    2, 0x0a /* Public */,
      65,    3,  306,    2, 0x0a /* Public */,
      66,    1,  313,    2, 0x0a /* Public */,
      67,    0,  316,    2, 0x0a /* Public */,
      68,    0,  317,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Void, 0x80000000 | 3,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::QPixmap,   18,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 23,   22,   24,
    QMetaType::Void, 0x80000000 | 25, 0x80000000 | 23,   22,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 21, 0x80000000 | 23,   27,   22,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 25, 0x80000000 | 23,   27,   22,   24,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, QMetaType::Double,   35,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, QMetaType::Double,   43,
    QMetaType::Void, QMetaType::Double,   43,
    QMetaType::Void, QMetaType::Double,   46,
    QMetaType::Void, 0x80000000 | 48,   49,
    QMetaType::Void, QMetaType::Double,   51,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void, 0x80000000 | 57,   55,
    QMetaType::Void, QMetaType::Double,   59,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 61, 0x80000000 | 62,   27,   22,   24,
    QMetaType::Void, 0x80000000 | 64, 0x80000000 | 23,   22,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 64, 0x80000000 | 23,   27,   22,   24,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Computator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Computator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->xWindProjectionChanged((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 1: _t->yWindProjectionChanged((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 2: _t->uxSpeedChanged((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 3: _t->uySpeedChanged((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 4: _t->u0xSpeedChanged((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 5: _t->u0ySpeedChanged((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 6: _t->uChanged((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 7: _t->u0Changed((*reinterpret_cast< const QVector<QVector<double> >(*)>(_a[1]))); break;
        case 8: _t->speedsComputated(); break;
        case 9: _t->getCurrentMapImage((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 10: _t->flowMapCreated((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 11: _t->sourcesChanged((*reinterpret_cast< const PointSource(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 12: _t->sourcesChanged((*reinterpret_cast< const DiffusionSource(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 13: _t->sourceUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const PointSource(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 14: _t->sourceUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const DiffusionSource(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 15: _t->setupGrid((*reinterpret_cast< const QVector<QVector<QPair<bool,QPointF> > >(*)>(_a[1]))); break;
        case 16: _t->setupHeights((*reinterpret_cast< const QVector<QVector<QPair<bool,double> > >(*)>(_a[1]))); break;
        case 17: _t->setARatio((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->setWOType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->acceptXSpeedsFromTable((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 20: _t->acceptYSpeedsFromTable((*reinterpret_cast< QTableWidget(*)>(_a[1]))); break;
        case 21: _t->acceptXStep((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 22: _t->acceptYStep((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 23: _t->acceptHorizon((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 24: _t->acceptMarkPosition((*reinterpret_cast< QPair<int,int>(*)>(_a[1]))); break;
        case 25: _t->acceptKsiAtol((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->acceptAbsSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->acceptAzimuth((*reinterpret_cast< const QPair<double,bool>(*)>(_a[1]))); break;
        case 28: _t->acceptWindDirection((*reinterpret_cast< const QPair<int,bool>(*)>(_a[1]))); break;
        case 29: _t->acceptDistance((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->giveSourceInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::variant<PointSource,DiffusionSource>(*)>(_a[2])),(*reinterpret_cast< QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 31: _t->addNewSource((*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[1])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[2]))); break;
        case 32: _t->updateSource((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::variant<PointSource,DiffusionSource>(*)>(_a[2])),(*reinterpret_cast< const QVector<PolutionMatter>(*)>(_a[3]))); break;
        case 33: _t->deleteSource((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->decomposeAbsSpeed(); break;
        case 35: _t->computateSpeeds(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::xWindProjectionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::yWindProjectionChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::uxSpeedChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::uySpeedChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::u0xSpeedChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::u0ySpeedChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::uChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QVector<QVector<double>> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::u0Changed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Computator::*)() const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::speedsComputated)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Computator::*)(QPixmap & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::getCurrentMapImage)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const QPixmap & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::flowMapCreated)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const PointSource & , const QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::sourcesChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Computator::*)(const DiffusionSource & , const QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::sourcesChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Computator::*)(int , const PointSource & , const QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::sourceUpdated)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (Computator::*)(int , const DiffusionSource & , const QVector<PolutionMatter> & ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Computator::sourceUpdated)) {
                *result = 14;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Computator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Computator.data,
    qt_meta_data_Computator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Computator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Computator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Computator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Computator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    return _id;
}

// SIGNAL 0
void Computator::xWindProjectionChanged(const QVector<QVector<double>> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Computator::yWindProjectionChanged(const QVector<QVector<double>> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Computator::uxSpeedChanged(const QVector<QVector<double>> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Computator::uySpeedChanged(const QVector<QVector<double>> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Computator::u0xSpeedChanged(const QVector<QVector<double>> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Computator::u0ySpeedChanged(const QVector<QVector<double>> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Computator::uChanged(const QVector<QVector<double>> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Computator::u0Changed(const QVector<QVector<double>> & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Computator::speedsComputated()const
{
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Computator::getCurrentMapImage(QPixmap & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Computator::flowMapCreated(const QPixmap & _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Computator::sourcesChanged(const PointSource & _t1, const QVector<PolutionMatter> & _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 11, _a);
}

// SIGNAL 12
void Computator::sourcesChanged(const DiffusionSource & _t1, const QVector<PolutionMatter> & _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 12, _a);
}

// SIGNAL 13
void Computator::sourceUpdated(int _t1, const PointSource & _t2, const QVector<PolutionMatter> & _t3)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 13, _a);
}

// SIGNAL 14
void Computator::sourceUpdated(int _t1, const DiffusionSource & _t2, const QVector<PolutionMatter> & _t3)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(const_cast< Computator *>(this), &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
