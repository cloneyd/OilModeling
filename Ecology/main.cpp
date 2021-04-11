// QT
#include <QApplication>

// current project
#include "mainwindow.hpp"
#include "GridHandlerFiles/gridhandler.hpp"
#include "PaintingWidget/paintingwidget.hpp"
#include "Visualization3D/object3dcontainer.hpp"
#include "Helpers/tablecontainer.hpp"
#include "PollutionWidget/pollutionwidgetgenerator.hpp"
#include "Computations/computator.hpp"
#include "Helpers/excelworker.hpp"


/* TODO:
 * 1) Наложение изображения на таблицу глубин (это точно возможно)
 * 2) Выделение ячеек рандомной областью (а это точно возможно?)
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window;
    GridHandler grid_handler;
    PaintingWidget painting_widget;
    ExcelWorker excel_worker;
    Object3DContainer graph;
    PollutionWidgetGenerator pollut_gen;
    Computator computator;

    
    // connections between MainWindow and GridHandler
    QObject::connect(&main_window, SIGNAL(scaleChanged(double /*scale*/)), // [16]
                     &grid_handler, SLOT(acceptScale(double /*scale*/)));
    
    QObject::connect(&main_window, SIGNAL(cellWidthChanged(double /*width*/)), // [17]
                     &grid_handler, SLOT(acceptCellWidth(double /*width*/)));

    QObject::connect(&main_window, SIGNAL(cellHeightChanged(double /*height*/)), // [18]
                     &grid_handler, SLOT(acceptCellHeight(double /*height*/)));

    QObject::connect(&main_window, SIGNAL(getPixgrid(const GridType **/*will be grid*/)), // [31]
                     &grid_handler, SLOT(givePixgrid(const GridType **)));

    // connections between MainWindow and PaintingWidget
    QObject::connect(&main_window, SIGNAL(setImage(QPixmap &/*image*/)), // [22], trasnsfer ownership
                     &painting_widget, SLOT(setImage(QPixmap &/*image*/)));

    QObject::connect(&main_window, SIGNAL(setImage(const QString &/*filepath*/, bool */*operation status*/)), // [23]
                     &painting_widget, SLOT(setImage(const QString &/*filepath*/, bool *)));

    QObject::connect(&main_window, SIGNAL(showPaintingWidget()), // [24]
                     &painting_widget, SLOT(show()));

    QObject::connect(&main_window, SIGNAL(scaleChanged(double /*scale*/)), // [16]
                     &painting_widget, SLOT(acceptScale(double /*scale*/)));

    QObject::connect(&main_window, SIGNAL(cellWidthChanged(double /*width*/)), // [17]
                     &painting_widget, SLOT(acceptCellWidth(double /*width*/)));

    QObject::connect(&main_window, SIGNAL(cellHeightChanged(double /*height*/)), // [18]
                     &painting_widget, SLOT(acceptCellHeight(double /*height*/)));

    //QObject::connect(&main_window, SIGNAL(saveMapInFile(const QString &/*filepath*/, bool */*operation status*/)), // [7]
       //              &painting_widget, SLOT(saveEdittedMapInFile(const QString &/*filepath*/, bool *)));

    QObject::connect(&main_window, SIGNAL(deleteSelectedSource(int /*source index*/)), // [30]
                     &painting_widget, SLOT(deleteSource(int /*source index*/)));
    
    // connections between MainWindow and Object3DContainer
    QObject::connect(&main_window, SIGNAL(saveDepth(DepthType &/*depth*/)), // [1]
                     &graph, SLOT(acceptDepth(DepthType &/*depth*/)));
    
    
    // connections between MainWindow and Computator
    QObject::connect(&main_window, SIGNAL(saveXProjections(QVector<QVector<double>> &/*speeds*/)), // [2], transfer ownership
                     &computator, SLOT(acceptXSpeedProjections(QVector<QVector<double>> & /*projections*/)));

    QObject::connect(&main_window, SIGNAL(saveYProjections(QVector<QVector<double>> &/*speeds*/)), // [3], transfer ownership
                     &computator, SLOT(acceptYSpeedProjections(QVector<QVector<double>> &/*projections*/)));
    
    QObject::connect(&main_window, SIGNAL(azimuthStateChanged(const QPair<bool, double> &/*new state*/)), // [8]
                     &computator, SLOT(acceptAzimuthState(const QPair<bool, double> &)));
    
    QObject::connect(&main_window, SIGNAL(windSystemStateChanged(const QPair<bool, WindDirection> &/*new state*/)), // [9]
                     &computator, SLOT(acceptSystemState(const QPair<bool, WindDirection> &/*new state*/)));
    
    QObject::connect(&main_window, SIGNAL(aRatioChanged(double /*ratio*/)), // [10]
                     &computator, SLOT(acceptARatio(double /*ratio*/)));
    
    QObject::connect(&main_window, SIGNAL(waterObjectTypeChanged(WaterObjectType /*object type*/)), // [11]
                     &computator, SLOT(acceptWaterObjectType(WaterObjectType /*object type*/)));
    
    QObject::connect(&main_window, SIGNAL(horizonChanged(double /*horizon*/)), // [12]
                     &computator, SLOT(acceptHorizon(double)));
    
    QObject::connect(&main_window, SIGNAL(atolChanged(double /*atol*/)), // [13]
                     &computator, SLOT(acceptAtol(double)));
    
    QObject::connect(&main_window, SIGNAL(absSpeedChanged(double /*speed*/)), // [14]
                     &computator, SLOT(acceptAbsSpeed(double)));
    
    QObject::connect(&main_window, SIGNAL(maxComputationDistanceChanged(double /*distance*/)), // [15]
                     &computator, SLOT(acceptMaxComputationDistance(double)));
    
    QObject::connect(&main_window, SIGNAL(computateSpeeds(bool */*operation status*/)), // [21]
                     &computator, SLOT(computateSpeeds(bool *)));
    
    QObject::connect(&main_window, SIGNAL(forceAbsSpeedDecompose(bool */*operation status*/)), // [19]
                     &computator, SLOT(decomposeAbsSpeed(bool *)));
    
    QObject::connect(&main_window, SIGNAL(cellWidthChanged(double /*width*/)), // [17
                     &computator, SLOT(acceptXStep(double /*xstep*/)));
    
    QObject::connect(&main_window, SIGNAL(cellHeightChanged(double /*height*/)), // [18]
                     &computator, SLOT(acceptYStep(double /*ystep*/)));
    
    QObject::connect(&main_window, SIGNAL(computatePollution(bool */*operation status*/)), // [27]
                     &computator, SLOT(computatePollution(bool *)));
    
    QObject::connect(&main_window, SIGNAL(azimuthValueChanged(double /*value*/)), // [28]
                     &computator, SLOT(azimuthValueChanged(double)));
    
    QObject::connect(&main_window, SIGNAL(systemDirectionChanged(WindDirection /*direction*/)), // [29]
                     &computator, SLOT(systemDirectionChanged(WindDirection)));
    
    QObject::connect(&main_window, SIGNAL(deleteSelectedSource(int /*source index*/)), // [30]
                     &computator, SLOT(deleteSource(int)));
    
    // connections between MainWindow and ExcelWorker
    QObject::connect(&main_window, SIGNAL(saveMapInFile(const QString &/*filepath*/, bool */*operation status*/)), // [7]
                     &excel_worker, SLOT(saveMap(const QString &, bool *)));
    
    QObject::connect(&main_window, SIGNAL(loadDepthFromFile(const QString &/*filepath*/, bool */*operation status*/)), // [20]
                     &excel_worker, SLOT(loadDepth(const QString &, bool *)));
    
    QObject::connect(&main_window, SIGNAL(saveSpeedsInFile(const QString &/*filepath*/, bool */*operation status*/)), // [4]
                     &excel_worker, SLOT(saveSpeeds(const QString &, bool *)));
    
    QObject::connect(&main_window, SIGNAL(saveDepthInFile(const QString &/*filepath*/, bool */*operation status*/)), // [5]
                     &excel_worker, SLOT(saveDepth(const QString &, bool *)));
    
    QObject::connect(&main_window, SIGNAL(saveOutput(const QString &/*filepath*/, bool */*operation status*/)), // [6]
                     &excel_worker, SLOT(saveOutput(const QString &, bool *)));
    
    // connections between MainWindow and PollutionWidgetGenerator
    QObject::connect(&main_window, SIGNAL(addNewPollutionSource()), // [25]
                     &pollut_gen, SLOT(createDefaultConstructedWidget()));    

    QObject::connect(&main_window, SIGNAL(displaySelectedSource(int /*source index*/)), // [26]
                     &pollut_gen, SLOT(createFilledWidget(int)));    
    
    // connections between GridHandler and MainWindow
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const GridType &/*pixel grid*/)), // [1]
                     &main_window, SLOT(acceptGrid(const GridType &)));

    QObject::connect(&grid_handler, SIGNAL(gridChanged(const GridType &/*pixel grid*/)), // [1]
                     &graph, SLOT(acceptPixGrid(const GridType &/*pixel grid*/)));

    // connections between GridHandler and Object3DContainer
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const GridType &/*pixel grid*/)), // [1]
                     &graph, SLOT(acceptPixGrid(const GridType &)));

    // connections between GridHandler and Computator
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const GridType &/*pixel grid*/)), // [1]
                     &computator, SLOT(acceptGrid(const GridType &)));

    // connections between GridHandler and ExcelWorker
    QObject::connect(&grid_handler, SIGNAL(gridChanged(const GridType &/*pixel grid*/)), // [1]
                     &excel_worker, SLOT(acceptGrid(const GridType &)));
    

    // connections between PaintingWidget and MainWindow
    QObject::connect(&painting_widget, SIGNAL(imageChanged(const QPixmap &/*image*/, bool /* is grid created*/)), // [1]
                     &main_window, SLOT(acceptMapImage(const QPixmap &, bool)));

    QObject::connect(&painting_widget, SIGNAL(resetSources()), // [8]
                     &main_window, SLOT(resetSources()));

    QObject::connect(&painting_widget, SIGNAL(gridParametersChanged(double/*scale*/, double/*cell width*/, double/*cell height*/)), // [2]
                     &main_window, SLOT(updateGridParameters(double, double, double)));

    QObject::connect(&painting_widget, SIGNAL(sourcesCoordinatesChanged(const QVector<QVector<QPointF>> &/*coordinates in real meters*/,
                                                                        const QVector<QVector<QPoint>> &/*their indexes on grid*/)), // [7]
                     &main_window, SLOT(acceptNewSourceCoordinates(const QVector<QVector<QPointF>> &/*takes only coordinates*/)));
    
    // connections between PaintingWidget and GridHandler
    QObject::connect(&painting_widget, SIGNAL(createGrid(const QVector<QPointF> &/*wo_area*/,
                                                         const QVector<QPointF> &/*islands_area*/)), // [3]
                     &grid_handler, SLOT(createGrid(const QVector<QPointF> &, const QVector<QPointF> &)));

    QObject::connect(&painting_widget, SIGNAL(deleteGrid()), // [4]
                     &grid_handler, SLOT(deleteGrid()));
    
    QObject::connect(&painting_widget, SIGNAL(drawGridOnPixmap(QPixmap &/*pixmap where grid will be drawn*/,
                                                               const QColor &/*line color*/, double /*line width*/)), // [5]
                     &grid_handler, SLOT(drawGridInPixmap(QPixmap &, const QColor &, double)));
    
    QObject::connect(&painting_widget, SIGNAL(findMark(const QPointF &/*mark position*/, QPoint */*callback indexes*/)), // [6]
                     &grid_handler, SLOT(findPoint(const QPointF &, QPoint *)));
    
    // connections between PaintingWidget and Computator
    QObject::connect(&painting_widget, SIGNAL(sourcesCoordinatesChanged(const QVector<QVector<QPointF>> &/*coordinates*/,
                                                                       const QVector<QVector<QPoint>> &/*indexes on grid*/)), // [7]
                     &computator, SLOT(acceptNewSourcesCoordinates(const QVector<QVector<QPointF>> &, const QVector<QVector<QPoint>> &)));
    
    QObject::connect(&painting_widget, SIGNAL(resetSources()), // [8]
                     &computator, SLOT(resetSources()));
    

    // connections between PollutionWidgetGenerator and Computator
    QObject::connect(&pollut_gen, SIGNAL(getSourceInfo(int /*source index*/, std::variant<PointSource, DiffusionSource> &/*callback source*/,
                                                       QVector<PollutionMatter> &/*callback matters*/)), // [5]
                     &computator, SLOT(giveSourceInfo(int, std::variant<PointSource, DiffusionSource> &, QVector<PollutionMatter> &)));    

    // connections between Computator and MainWindow
    QObject::connect(&computator, SIGNAL(flowMapCreated(const QPixmap &/*flow map image*/)), // [8]
                     &main_window, SLOT(acceptFlowMap(const QPixmap &)));

    QObject::connect(&computator, SIGNAL(xProjectionsDecomposed(const QVector<QVector<double>> &/*projections*/)), // [10]
                     &main_window, SLOT(acceptXProjections(const QVector<QVector<double>> &)));

    QObject::connect(&computator, SIGNAL(yProjectionsDecomposed(const QVector<QVector<double>> &/*projections*/)), // [11]
                     &main_window, SLOT(acceptYProjections(const QVector<QVector<double>> &)));

    // connections between Computator and ExcelWorker
    QObject::connect(&computator, SIGNAL(uxProjectionsComputated(const QVector<QVector<double>> &/*projections*/)), // [1]
                     &excel_worker, SLOT(acceptUXProjections(const QVector<QVector<double>> &)));

    QObject::connect(&computator, SIGNAL(uyProjectionsComputated(const QVector<QVector<double>> &/*projections*/)), // [2]
                     &excel_worker, SLOT(acceptUYProjections(const QVector<QVector<double>> &)));

    QObject::connect(&computator, SIGNAL(u0xProjectionsComputated(const QVector<QVector<double>> &/*projections*/)), // [3]
                     &excel_worker, SLOT(acceptU0XProjections(const QVector<QVector<double>> &)));

    QObject::connect(&computator, SIGNAL(u0yProjectionsComputated(const QVector<QVector<double>> &/*projections*/)), // [4]
                     &excel_worker, SLOT(acceptU0YProjections(const QVector<QVector<double>> &)));

    QObject::connect(&computator, SIGNAL(uComputated(const QVector<QVector<double>> &/*speeds*/)), // [5]
                     &excel_worker, SLOT(acceptU(const QVector<QVector<double>> &)));

    QObject::connect(&computator, SIGNAL(u0Computated(const QVector<QVector<double>> &/*speeds*/)), // [6]
                     &excel_worker, SLOT(acceptU0(const QVector<QVector<double>> &)));


    // connections between Object3DContainer and MainWindow
    QObject::connect(&graph, SIGNAL(depthChanged(const DepthType &/*depth*/)), // [1]
                     &main_window, SLOT(acceptDepth(const DepthType &)));
    
    // connections between Object3DContainer and Computator
    QObject::connect(&graph, SIGNAL(depthChanged(const DepthType &/*depth*/)), // [1]
                     &computator, SLOT(acceptDepth(const DepthType &)));

    // connections between Object3DContainer and ExcelWorker
    QObject::connect(&graph, SIGNAL(depthChanged(const DepthType &/*depth*/)), // [1]
                     &excel_worker, SLOT(acceptDepth(const DepthType &)));
    
    
    // connections between Computator and PaintingWidget
    QObject::connect(&computator, SIGNAL(getCurrentMapImage(QPixmap &/*callback image*/)), // [9]
                     &painting_widget, SLOT(giveCurrentMapImage(QPixmap &)));


    // connections between ExcelWorker and Object3DContainer
    QObject::connect(&excel_worker, SIGNAL(depthLoaded(DepthType &/*depth*/)), // [1]
                     &graph, SLOT(acceptDepth(DepthType &)));



    // Connections order important functions. MUST BE FIXED
    // connections between PollutionWidgetGenerator and MainWindow
    QObject::connect(&pollut_gen, SIGNAL(sourceCreated(const PointSource &/*source*/, const QVector<PollutionMatter> &/*source matters*/)), // [1]
                     &main_window, SLOT(appendNewSource(const PointSource &, const QVector<PollutionMatter> &)));

    QObject::connect(&pollut_gen, SIGNAL(sourceUpdated(int/*source index*/, const PointSource &/*source*/,
                                                       const QVector<PollutionMatter> &/*matters*/)), // [2]
                     &main_window, SLOT(updateSource(int, const PointSource &, const QVector<PollutionMatter> &)));

    QObject::connect(&pollut_gen, SIGNAL(sourceCreated(const DiffusionSource &/*source*/, const QVector<PollutionMatter> &/*matters*/)), // [3]
                     &main_window, SLOT(appendNewSource(const DiffusionSource &, const QVector<PollutionMatter> &)));

    QObject::connect(&pollut_gen, SIGNAL(sourceUpdated(int/*source index*/, const DiffusionSource &/*source*/,
                                                       const QVector<PollutionMatter> &/*matters*/)), // [4]
                     &main_window, SLOT(updateSource(int, const DiffusionSource &, const QVector<PollutionMatter> &)));

    // connections between PollutionWidgetGenerator and Computator
    QObject::connect(&pollut_gen, SIGNAL(sourceCreated(const PointSource &/*source*/, const QVector<PollutionMatter> &/*matters*/)), // [1]
                     &computator, SLOT(appendNewSource(const PointSource &, const QVector<PollutionMatter> &)));

    QObject::connect(&pollut_gen, SIGNAL(sourceUpdated(int /*source index*/, const PointSource &/*source*/,
                                                       const QVector<PollutionMatter> &/*matters*/)), // [2]
                     &computator, SLOT(updateSource(int, const PointSource &, const QVector<PollutionMatter> &)));

    QObject::connect(&pollut_gen, SIGNAL(sourceCreated(const DiffusionSource &/*source*/, const QVector<PollutionMatter> &/*matters*/)), // [3]
                     &computator, SLOT(appendNewSource(const DiffusionSource &, const QVector<PollutionMatter> &)));

    QObject::connect(&pollut_gen, SIGNAL(sourceUpdated(int /*source index*/, const DiffusionSource &/*source*/,
                                                       const QVector<PollutionMatter> &/*matters*/)), // [4]
                     &computator, SLOT(updateSource(int, const DiffusionSource &, const QVector<PollutionMatter> &)));

    // connections between PollutionWidgetGenerator and PaintingWidget
    QObject::connect(&pollut_gen, SIGNAL(sourceCreated(const PointSource &/*source*/, const QVector<PollutionMatter> &/*matters*/)), // [1]
                     &painting_widget, SLOT(appendNewSource(const PointSource &/*takes only source*/)));

    QObject::connect(&pollut_gen, SIGNAL(sourceUpdated(int /*source index*/, const PointSource &/*source*/,
                                                       const QVector<PollutionMatter> &/*matters*/)), // [2]
                     &painting_widget, SLOT(updateSource(int, const PointSource &/*takes only source*/)));

    QObject::connect(&pollut_gen, SIGNAL(sourceCreated(const DiffusionSource &/*source*/, const QVector<PollutionMatter> &/*matters*/)), // [3]
                     &painting_widget, SLOT(appendNewSource(const DiffusionSource &/*takes only source*/)));

    QObject::connect(&pollut_gen, SIGNAL(sourceUpdated(int /*source index*/, const DiffusionSource &/*source*/,
                                                       const QVector<PollutionMatter> &/*matters*/)), // [4]
                     &painting_widget, SLOT(updateSource(int, const DiffusionSource &/*takes only source*/)));


    // qss including
    QFile styleF(":/qss/QSS/ManjaroMix.qss");
    styleF.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleF.readAll());
    app.setStyleSheet(styleSheet);

    main_window.append3DVisualizationObject(&graph);
    graph.show();
    main_window.emitInitialSignals();
    main_window.show();
    return app.exec();
}
