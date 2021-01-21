#include "mainwindow.hpp"
#include "HelperEntities/excelworker.hpp"
#include "MapWithGridFiles/gridcreatorwidget.hpp"
#include "SurfaceFiles/surfacecontainer.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    GridCreatorWidget grid_map;
    SurfaceContainer surface;
    ExcelWorker excel_worker;

    // connections between MainWindow and GridCreatorWidget
    QObject::connect(window.getCellWidthBox(), SIGNAL(valueChanged(double)),
                     &grid_map, SLOT(updateCellWidth(double)));
    QObject::connect(window.getCellHeightBox(), SIGNAL(valueChanged(double)),
                     &grid_map, SLOT(updateCellHeight(double)));
    QObject::connect(window.getScaleBox(), SIGNAL(valueChanged(double)),
                     &grid_map, SLOT(updateScale(double)));

    QObject::connect(&window, SIGNAL(createGrid(const QString&)),
                     &grid_map, SLOT(createGridArea(const QString&)));
    QObject::connect(&window, SIGNAL(updateFullMap()),
                     &grid_map, SLOT(updateFullMap()));
    QObject::connect(&window, SIGNAL(updateGrid()),
                     &grid_map, SLOT(updateGrid()));
    QObject::connect(&window, SIGNAL( editGrid(TableWidget *)),
                     &grid_map, SLOT(editGrid(TableWidget *)));


    // connections between MainWindow and SurfaceContainer
    QObject::connect(window.getScaleBox(), SIGNAL(valueChanged(double)),
                     &surface, SLOT(setupScale(double)));

    QObject::connect(&window, SIGNAL(setupTableWidget(TableWidget *)),
                     &surface, SLOT(setupTableWidget(TableWidget *)));
    QObject::connect(&window, SIGNAL(openMapVisualization()),
                     &surface, SLOT(showWidget()));

    // connections between MainWindow and ExcelWorker
    QObject::connect(&window, SIGNAL(saveMapAsExcel(const QString &)),
                     &excel_worker, SLOT(saveHeightsFile(const QString &)));


    // connections between GridCreatorWidget and MainWindow
    QObject::connect(&grid_map, SIGNAL(saveMapInLabel(QPixmap)),
                     &window, SLOT(saveMapInLabel(QPixmap)));

    // connections between GridCreatorWidget and SurfaceContainer
    QObject::connect(&grid_map, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &surface, SLOT(setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &)));

    // connections between GridCreatorWidget and ExcelWorker
    QObject::connect(&grid_map, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &excel_worker, SLOT(updateHeightsFile(const QVector<QVector<QPair<bool, QPointF>>> &)));


    // connections between SurfaceContainer and ExcelWorker
    QObject::connect(&surface, SIGNAL(heightsChanged(const QVector<QVector<QPair<bool, double>>> &)),
                     &excel_worker, SLOT(updateHeights(const QVector<QVector<QPair<bool, double>>> &)));
    window.show();
    return app.exec();
}
