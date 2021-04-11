#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
// QT
#include <QMainWindow>
#include <QTableWidget>

// STL
#include <memory>

// current project
#include "Visualization3D/object3d_utilities.hpp"
#include "GridHandlerFiles/grid_handler_utilities.hpp"
#include "PollutionWidget/pollutionwidget_utilities.hpp"
#include "PaintingWidget/paint_table_scene_utilities.hpp"
#include "Computations/computator_utilities.hpp"
#include "Helpers/tablecontainer.hpp"

// ui
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/* TODO:
 * 1) put image on grid
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private: // data
    std::unique_ptr<Ui::MainWindow> m_ui;
    // tables
    TableContainer m_depth_table;
    TableContainer m_xprojections_table;
    TableContainer m_yprojections_table;

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void acceptGrid(const GridType &grid); // connected with GridHandler::[1]
    void acceptXProjections(const QVector<QVector<double>> &speed); // connected with Computator::[10]
    void acceptYProjections(const QVector<QVector<double>> &speed); // connected with Computator::[11]
    void acceptDepth(const DepthType &depth); // connected with Object3DContainer::[1]
    void acceptNewSourceCoordinates(const QVector<QVector<QPointF>> &coordinates); // connected with PaintingWidget::[7]
    void acceptMapImage(const QPixmap &image, bool is_grid_created); // connected with PaintingWidget::[1]; emits: [31]
    inline void resetSources() { resetSourcesTable(); }; // connected with PaintingWidget::[8]
    inline void updateGridParameters(double scale, double width, double height); // connected with PaintingWidget::[2]; must block spin box signals
    inline void acceptFlowMap(const QPixmap &pm); // connected with Computator::[8]

    // connected with PollutionWidgetGenerator::[1]; matters currently unused; it will use two functions: appendNewSourceToTable and
    // appendNewMatter
    inline void appendNewSource(const PointSource &source, const QVector<PollutionMatter> &/*matters*/) { appendNewSourceToTable(source); }
    // connected with PollutionWidgetGenerator::[2]; matters currently unused
    inline void updateSource(int source_index, const PointSource &source, const QVector<PollutionMatter> &/*matters*/) { updateSourceInTable(source_index, source); }
    // connected with PollutionWidgetGenerator::[3]; matters currently unused
    inline void appendNewSource(const DiffusionSource &source, const QVector<PollutionMatter> &/*matters*/) { appendNewSourceToTable(source); }
    // connected with PollutionWidgetGenerator::[4]; matters currently unused
    inline void updateSource(int source_index, const DiffusionSource &source, const QVector<PollutionMatter> &/*matters*/) { updateSourceInTable(source_index, source); }

    // should parse tables and create vectors
    void saveDepthTable(const QTableWidget &table); // connected with TableContainer::[1]; emits: [1]
    void saveXProjectionTable(const QTableWidget &table); // connected with TableContainer::[1]; emits: [2]
    void saveYProjectionTable(const QTableWidget &table); // connected with TableContainer::[1]; emits: [3]

private slots:
    void loadFromSiteButton(); // connected with Ui::[1]; emits: [22]
    void loadFromPCButtonPressed(); // connected with Ui::[2]; emits: [23]
    void loadDepthFromFile(); // connected with Ui::[13]; emits: [20]
    void displaySelectedSourceButtonPressed() const; // connected with Ui::[29]; emits: [26]
    void deleteSelectedSourceButtonPressed(); // connected with Ui::[30]; emits: [30]
    void forceSpeedDecomposeButtonPressed() const; // connected with Ui::[10]; emits: [19]
    void computateSpeedsButtonPressed() const; // connected with Ui::[11]; emits: [21]
    void computatePollutionButtonPressed() const; // connected with Ui::[14]; emits: [27]
    inline void editImageButtonPressed() const { emit showPaintingWidget(); } // connected with Ui::[3]; emits: [24]
    inline void addNewSourceButtonPressed() const { emit addNewPollutionSource(); } // connected with Ui::[28]; emits: [25]

    // connected with UI::[4]
    inline void openVisualizationButtonPressed() { m_ui->display_info_tool_box->setCurrentIndex(2); m_ui->relief_tab_page->setCurrentIndex(0); }
     // connected with Ui::[12];
    inline void enterDepthButtonPressed() { m_ui->display_info_tool_box->setCurrentIndex(2); m_ui->relief_tab_page->setCurrentIndex(1); }
    // connected with Ui::[9]
    inline void enterSpeedsButtonPressed() { m_ui->display_info_tool_box->setCurrentIndex(3); m_ui->winds_direction_tab->setCurrentIndex(1); }

    void saveMapInFileButtonPressed(); // connected with Ui::[5]; emits; {7}
    void saveDepthInFileButtonPressed(); // connected with Ui::[6]; emits: [5]
    void saveSpeedsInFileButtonPressed(); // connected with UI::[7]; emits: [4]
    void createCommonOutputFileButtonPressed(); // connected with Ui::[8]; emits: [6]

    void azimuthStateChangedSender(int state); // connected with Ui::[25]; emits: [8], [9]
    void systemStateChangedSender(int state); // connected with Ui::[26]; emits: [8], [9]
    // connected with  Ui::[15]; emits: [16]
    inline void scaleValueChangedSender(double scale) const { emit scaleChanged(scale); }
    // connected with Ui::[16]; emits: [17]
    inline void cellWidthValueChangedSender(double width) const { emit cellWidthChanged(width); }
    // connected with Ui::[17]; emits: [18]
    inline void cellHeightValueChangedSender(double height) const { emit cellHeightChanged(height); }
    // connected with Ui::[18]; emits: [11]
    inline void woComboBoxCurrentIndexChangedSender(int index) const;
    // connected with Ui::[19]; emits: [12]
    inline void horizonValueChangedSender(double horizon) const { emit horizonChanged(horizon); }
    // connected with Ui::[20]; emits: [10]
    inline void aRatioValueChangedSender(double ratio) const { emit aRatioChanged(ratio); }
    // connected with Ui::[21]; emits: [13]
    inline void atolValueChangedSender(double atol) const { emit atolChanged(atol); }
    // connected with Ui::[22]; emits: [14]
    inline void absSpeedValueChangedSender(double value) const { emit absSpeedChanged(value); }
    // connected wtih Ui::[23]; emits: [28]
    inline void azimuthValueChangedSenderSender(double value) const { emit azimuthValueChanged(value); }
    // connected with Ui::[24]; emits: [29]
    inline void systemCurrentIndexChangedSender(int index) const;
    // connected with Ui::[27]; emits: [15]
    inline void maxComputationDistanceChangedSender(double distance) const { emit maxComputationDistanceChanged(distance); }

signals:
    // NOTE: operation status indicates that operation done successfully
    void saveDepth(DepthType &depth); // [1]; Transfers ownership
    void saveXProjections(QVector<QVector<double>> &speeds); // [2]; Transfers ownership
    void saveYProjections(QVector<QVector<double>> &speeds); // [3]; Transfers ownership
    void saveSpeedsInFile(const QString &filepath, bool *operation_status) const; // [4]
    void saveDepthInFile(const QString &filepath, bool *operation_status) const; // [5]
    void saveOutput(const QString &filepath, bool *operation_status) const; // [6]
    void saveMapInFile(const QString &filepath, bool *operation_status) const; // [7]

    void azimuthStateChanged(const QPair<bool, double> &state) const; // [8]
    void windSystemStateChanged(const QPair<bool, WindDirection> &state) const; // [9]
    void aRatioChanged(double ratio) const; // [10]
    void waterObjectTypeChanged(WaterObjectType type) const; // [11]
    void horizonChanged(double horizon) const; // [12]
    void atolChanged(double atol) const; // [13]
    void absSpeedChanged(double speed) const; // [14]
    void maxComputationDistanceChanged(double distance) const; // [15]
    void scaleChanged(double scale) const; // [16]
    void cellWidthChanged(double width) const; // [17]
    void cellHeightChanged(double height) const; // [18]
    void azimuthValueChanged(double value) const; // [28]
    void systemDirectionChanged(WindDirection direction) const; // [29]

    void forceAbsSpeedDecompose(bool *operation_status) const; // [19]
    void loadDepthFromFile(const QString &filepath, bool *operation_status); // [20]
    void computateSpeeds(bool *operation_status) const; // [21]
    void setImage(QPixmap &pm); // [22]; Transfers ownership
    void setImage(const QString &filepath, bool *operation_status); // [23]
    void showPaintingWidget() const; // [24]
    void addNewPollutionSource() const; // [25]
    void displaySelectedSource(int source_index) const; // [26]
    void deleteSelectedSource(int source_index) const; // [30]
    void computatePollution(bool *operation_status) const; // [27]
    void getPixgrid(const GridType **will_be_grid); // [31]

// setters
public:
    inline void append3DVisualizationObject(QWidget *container) { m_ui->relief_tab_page->addTab(container, "3D глубины"); } // TAKES OWNERSHIP

// nonmodifier helper function
public:
    void emitInitialSignals() const; // emits initial signals: [8] - [18], [28], [29]

private:
    void resetSourcesTable(); // clear table (but saves information row(1))
    void appendNewSourceToTable(const PointSource &source);
    void updateSourceInTable(int source_index, const PointSource &source);
    void appendNewSourceToTable(const DiffusionSource &source);
    void updateSourceInTable(int source_index, const DiffusionSource &source);
    void createGridBackgroundedTables(); // emits: [31]
    void drawBackgroundInTable(QTableWidget &table, const GridType *pixgrid_ptr);
    void setupTableToNewGrid(TableContainer &table_container, const GridType &grid);
    void clearTables();

    template <class...Flags>
    [[nodiscard]] QTableWidgetItem* createTableWidgetItem(const QString &text, Flags&&... flags) const;
    [[nodiscard]] QTableWidgetItem* createTableWidgetItem(const QString &text) const;
    void createSourcesTableFirstRow();
    [[nodiscard]] QPixmap getPixmapFromWebEngine() const;
    [[nodiscard]] QString getFormatsFromComboBox(const QComboBox *box) const;

    void applyNewInstanceSettings(bool setEnabled); // clear all tables, setup sources table; disable non image load buttons;
    void applyNewImageLoadedSettings(bool setEnabled);
    void applyNewGridCreatedSettings(bool setEnabled);
    void setupUiConnections();
    void setupFieldsConnections();
};

// inline functions implementation
inline void MainWindow::updateGridParameters(double scale, double width, double height)
{
    // FIXME: will impilitely try to update values in PaintingWidget; how to block it?
    m_ui->scale_spin_box->setValue(scale);
    m_ui->cell_width_spin_box->setValue(width);
    m_ui->cell_height_spin_box->setValue(height);
}

inline void MainWindow::acceptFlowMap(const QPixmap &pm)
{
    m_ui->map_with_winds_label->clear();
    m_ui->map_with_winds_label->setPixmap(pm);
    m_ui->map_with_winds_label->setScaledContents(true);
    m_ui->display_info_tool_box->setCurrentIndex(3);
    m_ui->winds_direction_tab->setCurrentIndex(0);
}

inline void MainWindow::woComboBoxCurrentIndexChangedSender(int index) const
{
    Q_ASSERT_X(index >= static_cast<int>(WaterObjectType::MIN) && index <= static_cast<int>(WaterObjectType::MAX),
               "Class - MainWIndow", "Finction - woComboBoxIndexChangedSender, problem - invalid index");
    emit waterObjectTypeChanged(static_cast<WaterObjectType>(index));
}

inline void MainWindow::systemCurrentIndexChangedSender(int index) const
{
    Q_ASSERT_X(index >= static_cast<int>(WindDirection::MIN) && index <= static_cast<int>(WindDirection::MAX),
               "Class - Computator", "Function - systemCurrentIndexChangedSener, problem - invalid index");
    emit systemDirectionChanged(static_cast<WindDirection>(index));
}
#endif // MAINWINDOW_HPP
