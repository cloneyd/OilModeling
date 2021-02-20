#include <QApplication>

#include "mainwindow.hpp"
#include "computator.hpp"
#include "gridhandler.hpp"
#include "visualization3dcontainer.hpp"
#include "excelworker.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    GridHandler grid_handler;
    auto& graphics3D { window.getVisualizationContainer() }; // ref to window's object
    ExcelWorker excel_worker;
    Computator computator;

    // connections between MainWindow and GridHandler
    QObject::connect(window.getScaleDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &grid_handler, SLOT(setScale(double)));
    QObject::connect(window.getCellWidthDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &grid_handler, SLOT(setCellWidth(double)));
    QObject::connect(window.getCellHeightDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &grid_handler, SLOT(setCellHeight(double)));
    QObject::connect(&window, SIGNAL(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &)),
                     &grid_handler, SLOT(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &)));

    // connections between MainWindow and Visualization3DContainer
    QObject::connect(window.getScaleDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &graphics3D, SLOT(setupScale(double)));

    // connections between MainWindow and Computator
    QObject::connect(window.getARatioDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &computator, SLOT(setARatio(double)));
    QObject::connect(window.getWaterObjectComboBox(), SIGNAL(currentIndexChanged(int)),
                     &computator, SLOT(setWOType(int)));


    // connections between GridHandler and MainWindow
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &window, SLOT(setupTables(const QVector<QVector<QPair<bool, QPointF>>> &)));

    // connections between GridHandler and Visualization3DContainer
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &graphics3D, SLOT(setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &)));


    // connections between GridHandler and ExcelWorker
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &excel_worker, SLOT(acceptGrid(const QVector<QVector<QPair<bool, QPointF>>> &)));


    // connectons between Visualization3DContainer and ExcelWorker
    QObject::connect(&graphics3D, SIGNAL(heightsChanged(const QVector<QVector<QPair<bool, double>>> &)),
                     &excel_worker, SLOT(updateHeights(const QVector<QVector<QPair<bool, double>>> &)));

    window.show();
    return app.exec();
}
