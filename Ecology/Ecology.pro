QT       += core gui datavisualization webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Computations/computator.cpp \
    GridHandlerFiles/gridhandler.cpp \
    Helpers/databasenote.cpp \
    Helpers/excelworker.cpp \
    Helpers/internalconfigurationfileshandler.cpp \
    Helpers/pch.cpp \
    Helpers/tablecontainer.cpp \
    PaintingWidget/paintingwidget.cpp \
    PaintingWidget/painttablescene.cpp \
    PollutionWidget/pollutionwidget.cpp \
    PollutionWidget/pollutionwidgetgenerator.cpp \
    Visualization3D/object3d.cpp \
    Visualization3D/object3dcontainer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Computations/computator.hpp \
    Computations/computator_utilities.hpp \
    GridHandlerFiles/grid_handler_utilities.hpp \
    GridHandlerFiles/gridhandler.hpp \
    Helpers/databasenote.hpp \
    Helpers/errorstatusstructures.hpp \
    Helpers/excelworker.hpp \
    Helpers/internalconfigurationfileshandler.hpp \
    Helpers/pch.hpp \
    Helpers/tablecontainer.hpp \
    PaintingWidget/paint_table_scene_utilities.hpp \
    PaintingWidget/paintingwidget.hpp \
    PaintingWidget/paintingwidget_utilities.hpp \
    PaintingWidget/painttablescene.hpp \
    PollutionWidget/pollution_source_types.hpp \
    PollutionWidget/pollutionwidget.hpp \
    PollutionWidget/pollutionwidget_utilities.hpp \
    PollutionWidget/pollutionwidgetgenerator.hpp \
    Visualization3D/object3d.hpp \
    Visualization3D/object3d_utilities.hpp \
    Visualization3D/object3dcontainer.hpp \
    mainwindow.hpp

FORMS += \
    Helpers/databasenote.ui \
    PaintingWidget/grid_parameters.ui \
    PaintingWidget/paintingwidget.ui \
    PollutionWidget/pollutionwidget.ui \
    mainwindow.ui

include(../QtXlsxWriter/src/xlsx/qtxlsx.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Helpers/resoures.qrc
