#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QVector>
#include <QPointF>
#include <QPair>

#include "paintingwidget.hpp"
#include "visualization3dcontainer.hpp"
#include "tablecontainer.hpp"

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *m_ui;

    PaintingWidget m_painting_widget;

    TableContainer m_deeps_table_container;
    TableContainer m_xwind_table_container;
    TableContainer m_ywind_table_container;

    Visualization3DContainer m_visualization_container;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setupTables(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridHandler; signal - gridChanged(same)

    void createGridSender(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area, const std::list<QPointF> &mark_pos,
                          const QColor &color, double line_width); // connected with PaintingWidget; signal - createGrid(same);
    void updateGridParameters(double cell_width, double cell_height, double scale) const; // connected with PaintingWidget; signal cellScaleParametersChanged(same);
    void deleteGridSender() const; // connected with PaintingWidget; signal - deleteGrid();
    void drawGridInPixmapSender(QPixmap &map, const QColor &color, double line_width) const; // public

    void saveHeightsFromTableSender(QTableWidget &table); // connected with TableContainer; signal - saveButtonPressed(same) // public
    void saveXSpeedsFromTableSender(QTableWidget &table); // connected with TableContainer; signal - saveButtonPressed(same) // public
    void saveYSpeedsFromTableSender(QTableWidget &table); // connected with TableContainer; signal - saveButtonPressed(same) // public

    void updateXWindTable(const QVector<QVector<double>> &speed);
    void updateYWindTable(const QVector<QVector<double>> &speed);

    void openMapVisualizationButtonPressed(); // connected with ui->open_map_visualization_button // private
    void enterHeightsButtonPressed(); // connected with ui->enter_heights_button // private
    void updateDepthTableValues(const QVector<QVector<QPair<bool, double>>> &heights); // connected with Visualization3DContainer; signal - heightsChanged(same) // public

    void enableSpeedsSaver(); // connected with Computator; signal - speedsComputated() // public

private slots:
    void loadFromSiteButtonPressed(); // connected with ui->load_from_site_button;
    void loadFromPCButtonPressed(); // connected with ui->load_from_pc_button;

    void loadHeightsFromFileButtonPressed(); // connected with ui->load_heights_from_file_button;

    void editImageButtonPressed(); // connected with ui->edit_image_button;
    void setImageInMapLabel(const QImage &image); // connected with PaintingWidget; signal - imageChanged(same);

    void saveHeightsTableButtonPressed(); // connected with ui->save_heights_table_button

    void enterSpeedVectorButtonPressed(); // connected with ui->enter_speed_vectors_button
    void saveSpeedsButtonPressed(); // connected with ui->save_speeds_button

    void saveMapButtonPressed(); // connected with ui->save_map_button; signal - pressed()

    void computateSpeedsButtonPressed() const; // connected with ui->computate_speeds_button

    void azimuthCheckBoxStateChanged(bool newstate); // connected with ui->azimuth_check_box
    void systemCheckBoxStateChanged(bool newstate); // connected with ui->system_check_box

    void forceAbsSpeedDecomposeButtonPressed() const;

    void azimuthValueChanged(double) const;
    void systemIndexChanged(int) const;

signals:
    void setupTable(QTableWidget &table);

    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area, const std::list<QPointF> &mark_pos,
                    const QColor &color, double line_width) const;
    void drawGridInPixmap(QPixmap &map, const QColor &color, double line_width) const;
    void deleteGrid() const;

    void saveHeightsFromTable(QTableWidget &table);
    void saveXSpeedsFromTable(QTableWidget &table);
    void saveYSpeedsFromTable(QTableWidget &table);

    void sendAzimuthState(const QPair<double, bool> &pair) const;
    void sendSystemState(const QPair<int, bool> &pair) const;

    void saveMapAsExcel(const QString &file_path) const;
    void loadHeightsFromFileSender(const QString &file_path);

    void saveSpeedsAsExcel(const QString &filepath);

    void forceAbsSpeedDecompose() const;

    void computateSpeeds() const;

// Getters
public:
    [[nodiscard]] inline const QDoubleSpinBox* getScaleDoubleSpinBox() const noexcept { return m_ui->scale_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getCellWidthDoubleSpinBox() const noexcept { return m_ui->cell_width_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getCellHeightDoubleSpinBox() const noexcept {return m_ui->cell_height_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getARatioDoubleSpinBox() const noexcept { return m_ui->ratio_double_spin_box; }
    [[nodiscard]] inline const QComboBox* getWaterObjectComboBox() const noexcept { return m_ui->water_object_type_combo_box; }
    [[nodiscard]] inline const Visualization3DContainer& getVisualizationContainer() const noexcept { return m_visualization_container; }
    [[nodiscard]] inline const QDoubleSpinBox* getHorizonDoubleSpinBox() const noexcept { return m_ui->horizon_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getKsiAtolSpinBox() const noexcept { return m_ui->atol_percents_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getSpeedAbsDoubleSpinBox() const noexcept { return m_ui->abs_wind_speed_spin_box; }

// methods
public:
    void emitUiSignal() const; // emitting all ui stuff connected signals

// Helpers
private:
    QPixmap getPixmapFromScene() const;
    QPixmap getPixmapFromWebEngine() const;
    QString getFormatsFromComboBox(const QComboBox *box) const;

    void enableInitButtonsSet();

    void setupIternalConnections();
    void connectPaintingSignalsWithMainWindow();
};
#endif // MAINWINDOW_H
