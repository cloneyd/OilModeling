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

    QFile styleF(":/qss/qss/ManjaroMix.qss");
    styleF.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleF.readAll());
    app.setStyleSheet(styleSheet);

    // connections between MainWindow and GridHandler
    QObject::connect(window.getScaleDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &grid_handler, SLOT(setScale(double)));
    QObject::connect(window.getCellWidthDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &grid_handler, SLOT(setCellWidth(double)));
    QObject::connect(window.getCellHeightDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &grid_handler, SLOT(setCellHeight(double)));
    QObject::connect(&window, SIGNAL(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &, const QColor &)),
                     &grid_handler, SLOT(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &, const QColor &)));
    QObject::connect(&window, SIGNAL(deleteGrid()),
                     &grid_handler, SLOT(deleteGrid()));


    // connections between MainWindow and Visualization3DContainer
    QObject::connect(window.getScaleDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &graphics3D, SLOT(setupScale(double)));
    QObject::connect(&window, SIGNAL(saveHeightsFromTable(QTableWidget &)),
                     &graphics3D, SLOT(setupHeights(QTableWidget &)));

    // connections between MainWindow and Computator
    QObject::connect(window.getARatioDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &computator, SLOT(setARatio(double)));
    QObject::connect(window.getWaterObjectComboBox(), SIGNAL(currentIndexChanged(int)),
                     &computator, SLOT(setWOType(int)));
    QObject::connect(&window, SIGNAL(saveXSpeedsFromTable(QTableWidget &)),
                     &computator, SLOT(acceptXSpeedsFromTable(QTableWidget &)));
    QObject::connect(&window, SIGNAL(saveYSpeedsFromTable(QTableWidget &)),
                     &computator, SLOT(acceptYSpeedsFromTable(QTableWidget &)));
    QObject::connect(&window, SIGNAL(computateSpeeds()),
                     &computator, SLOT(computateSpeeds()));
    QObject::connect(window.getHorizonDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &computator, SLOT(acceptHorizon(const double)));
<<<<<<< Updated upstream
=======
    QObject::connect(window.getKsiAtolSpinBox(), SIGNAL(valueChanged(double)),
                     &computator, SLOT(acceptKsiAtol(double)));
    QObject::connect(&window, SIGNAL(sendAzimuthState(const QPair<double, bool> &)),
                     &computator, SLOT(acceptAzimuth(const QPair<double, bool> &)));
    QObject::connect(&window, SIGNAL(sendSystemState(const QPair<int, bool> &)),
                     &computator, SLOT(acceptWindDirection(const QPair<int, bool> &)));
    QObject::connect(&window, SIGNAL(forceAbsSpeedDecompose()),
                     &computator, SLOT(decomposeAbsSpeed()));
    QObject::connect(window.getSpeedAbsDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &computator, SLOT(acceptAbsSpeed(double)));
    QObject::connect(window.getMaxComputationDistanceDoubleSpinBox(), SIGNAL(valueChanged(double)),
                     &computator, SLOT(acceptDistance(double)));
    QObject::connect(&window, SIGNAL(deleteSelectedSource(int)),
                     &computator, SLOT(deleteSource(int)));
    QObject::connect(&window, SIGNAL(computatePollution()),
                     &computator, SLOT(computatePollution()));
    QObject::connect(&window, SIGNAL(resetSources()),
                     &computator, SLOT(resetSettings()));
>>>>>>> Stashed changes

    // connections between MainWindow and ExcelWorker
    QObject::connect(&window, SIGNAL(saveMapAsExcel(const QString &)),
                     &excel_worker, SLOT(saveHeightsFile(const QString &)));
    QObject::connect(&window, SIGNAL(loadHeightsFromFileSender(const QString &)),
                     &excel_worker, SLOT(loadHeightsFromFile(const QString &)));
    QObject::connect(&window, SIGNAL(saveSpeedsAsExcel(const QString &)),
                     &excel_worker, SLOT(saveSpeedsAsExcel(const QString &)));


    // connections between GridHandler and MainWindow
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &window, SLOT(setupTables(const QVector<QVector<QPair<bool, QPointF>>> &)));

    // connections between GridHandler and Visualization3DContainer
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &graphics3D, SLOT(setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &)));

    // connections between GridHangler and Computator
    QObject::connect(&grid_handler, SIGNAL(xStepChanged(const double)),
                     &computator, SLOT(acceptXStep(const double)));
    QObject::connect(&grid_handler, SIGNAL(yStepChanged(const double)),
                     &computator, SLOT(acceptYStep(const double)));

    // connections between GridHandler and ExcelWorker
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &)),
                     &excel_worker, SLOT(acceptGrid(const QVector<QVector<QPair<bool, QPointF>>> &)));



    // connections between Visualization3DContainer and MainWindow
    QObject::connect(&graphics3D, SIGNAL(heightsChanged(const QVector<QVector<QPair<bool, double>>> &)),
                     &window, SLOT(updateDepthTableValues(const QVector<QVector<QPair<bool, double>>> &)));

    // connections between Visualization3DContainer and Computator
    QObject::connect(&graphics3D, SIGNAL(heightsChanged(const QVector<QVector<QPair<bool, double>>> &)),
                     &computator, SLOT(setupHeights(const QVector<QVector<QPair<bool, double>>> &)));

    // connectons between Visualization3DContainer and ExcelWorker
    QObject::connect(&graphics3D, SIGNAL(heightsChanged(const QVector<QVector<QPair<bool, double>>> &)),
                     &excel_worker, SLOT(updateHeights(const QVector<QVector<QPair<bool, double>>> &)));


    // connections between Computator and ExcelWorker
    QObject::connect(&computator, SIGNAL(xSpeedChanged(const QVector<QVector<double>> &)),
                     &excel_worker, SLOT(updateXSpeeds(const QVector<QVector<double>> &)));
    QObject::connect(&computator, SIGNAL(ySpeedChanged(const QVector<QVector<double>> &)),
                     &excel_worker, SLOT(updateYSpeeds(const QVector<QVector<double>> &)));


    // connections  between ExcelWorker and Visualization3DContainer
    QObject::connect(&excel_worker, SIGNAL(heightsLoaded(QVector<QVector<QPair<bool, double>>> &)),
                     &graphics3D, SLOT(setupHeights(QVector<QVector<QPair<bool, double>>> &)));

<<<<<<< Updated upstream
=======

    // connections between PaintingWidget and MainWindow
    QObject::connect(&painting_widget, SIGNAL(imageChanged(const QImage &)),
                     &window, SLOT(setImageInMapLabel(const QImage &)));
     QObject::connect(&painting_widget, SIGNAL(cellScaleParametersChanged(double, double, double)),
                     &window, SLOT(updateGridParameters(double, double, double)));

    // connection between PaintingWidget and GridHandler
    QObject::connect(&painting_widget, SIGNAL(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &,
                                                         const QColor &, double)),
                     &grid_handler, SLOT(createGrid(QPixmap &, const QVector<QPointF> &, const QVector<QPointF> &,
                                                    const QColor &, double)));
    QObject::connect(&painting_widget, SIGNAL(deleteGrid()),
                     &grid_handler, SLOT(deleteGrid()));
    QObject::connect(&painting_widget, SIGNAL(drawGridInPixmap(QPixmap &, const QColor &, double)),
                     &grid_handler, SLOT(drawGridInPixmap(QPixmap &, const QColor &, double)));
    QObject::connect(&painting_widget, SIGNAL(findMark(int, const QPointF &, QPoint *)), // find source in grid
                     &grid_handler, SLOT(searchMarkInGrid(int, const QPointF &, QPoint *)));

    // connections between PaintingWidget and Computator
    QObject::connect(&painting_widget, SIGNAL(updateCoordinates(const QVector<QVector<QPointF>> &, const QVector<QVector<QPoint>> &)),
                     &computator, SLOT(updateCoordinates(const QVector<QVector<QPointF>> &, const QVector<QVector<QPoint>> &)));
    QObject::connect(&painting_widget, SIGNAL(deleteLastMarkInSource(int)),
                     &computator, SLOT(deleteLastMarkInSource(int)));


    // connections between PolutionWidgetContainer and Computator
    QObject::connect(&polution_widget_container, SIGNAL(sourceCreated(const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)),
                     &computator, SLOT(addNewSource(const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)));    
    QObject::connect(&polution_widget_container, SIGNAL(getSourceInfo(int, std::variant<PointSource, DiffusionSource> &, QVector<PolutionMatter> &)),
                     &computator, SLOT(giveSourceInfo(int, std::variant<PointSource, DiffusionSource> &, QVector<PolutionMatter> &)));    
    QObject::connect(&polution_widget_container, SIGNAL(sourceUpdated(int, const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)),
                     &computator, SLOT(updateSource(int, const std::variant<PointSource, DiffusionSource> &, const QVector<PolutionMatter> &)));

    window.emitUiSignal(); // emit connected ui stuff signals

>>>>>>> Stashed changes
    window.show();
    return app.exec();
}
