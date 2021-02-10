QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HelperEntities/Table/tablecontainer.cpp \
    HelperEntities/Table/tablewidget.cpp \
    HelperEntities/excelworker.cpp \
    HelperEntities/helper_functions.cpp \
    HelperEntities/pch.cpp \
    MapWithGridFiles/gridcreatorwidget.cpp \
    MapWithGridFiles/painttablescene.cpp \
    SurfaceFiles/surfacecontainer.cpp \
    SurfaceFiles/surface.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    HelperEntities/Table/tablecontainer.hpp \
    HelperEntities/Table/tablewidget.hpp \
    HelperEntities/excelworker.hpp \
    HelperEntities/pch.hpp \
    MapWithGridFiles/gridcreatorwidget.hpp \
    MapWithGridFiles/painttablescene.hpp \
    SurfaceFiles/surfacecontainer.hpp \
    SurfaceFiles/surface.hpp \
    mainwindow.hpp

FORMS += \
    MapWithGridFiles/gridcreatorwidget.ui \
    mainwindow.ui

QT += datavisualization
include(../../QtXlsxWriter/QtXlsxWriter/src/xlsx/qtxlsx.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Class_structure \
    TODO_list
