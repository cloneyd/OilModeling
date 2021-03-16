QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    computator.cpp \
    excelworker.cpp \
    gridhandler.cpp \
    helperentities.cpp \
    main.cpp \
    mainwindow.cpp \
    paintingwidget.cpp \
    painttablescene.cpp \
    polutionwidget.cpp \
    polutionwidgetcontainer.cpp \
    tablecontainer.cpp \
    visualization3dcontainer.cpp \
    visualization3dobject.cpp

HEADERS += \
    computator.hpp \
    computator_utilities.hpp \
    excelworker.hpp \
    grid_handler_utilities.hpp \
    gridhandler.hpp \
    mainwindow.hpp \
    paintingwidget.hpp \
    painttablescene.hpp \
    pollution_widget_utilities.hpp \
    polutionwidget.hpp \
    polutionwidgetcontainer.hpp \
    source_types.hpp \
    tablecontainer.hpp \
    visualization3dcontainer.hpp \
    visualization3dobject.hpp

FORMS += \
    cell_scale_parameters.ui \
    mainwindow.ui \
    paintingwidget.ui \
    polutionwidget.ui

QT += webenginewidgets
QT += datavisualization
include(../QtXlsxWriter/src/xlsx/qtxlsx.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
