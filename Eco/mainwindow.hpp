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
    Ui::MainWindow *ui;

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

    void loadFronSiteButtonPressed(); // connected with ui->load_from_site_button
    void loadFromPCButtonPressed(); // connected with ui->load_from_pc_button

    void loadHeightsFromFileButtonPressed(); // connected with ui->load_heights_from_file_button

    void editImageButtonPressed(); // connected with ui->edit_image_button
    void setImageInMapLabel(const QImage &image); // connected with PaintingWidget; signal - imageChanged(same)

    void createGridSender(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area) const; // connected with PaintingWidget; signal - createGrid(same)
    void updateGridParameters(double cell_width, double cell_height, double scale) const; // connected with PaintingWidget; signal cellScaleParametersChanged(same)

    void saveHeightsFromTableSender(QTableWidget &table); // connected with TableContainer; signal - saveButtonPressed(same)
    void saveXSpeedsFromTableSender(QTableWidget &table); // connected with TableContainer; signal - saveButtonPressed(same)
    void saveYSpeedsFromTableSender(QTableWidget &table); // connected with TableContainer; signal - saveButtonPressed(same)

    void openMapVisualizationButtonPressed(); // connected with ui->open_map_visualization_button
    void enterHeightsButtonPressed(); // connected with ui->enter_heights_button
    void updateDepthTableValues(const QVector<QVector<QPair<bool, double>>> &heights); // connected with Visualization3DContainer; signal - heightsChanged(same)
    void saveHeightsTableButtonPressed(); // connected with ui->save_heights_table_button

    void enterSpeedVectorButtonPressed(); // connected with ui->enter_speed_vectors_button
    void saveSpeedsButtonPressed(); // connected with ui->save_speeds_button

    void saveMapButtonPressed();

signals:
    void setupTable(QTableWidget &table);

    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area) const;

    void saveHeightsFromTable(QTableWidget &table);
    void saveXSpeedsFromTable(QTableWidget &table);
    void saveYSpeedsFromTable(QTableWidget &table);

    void saveMapAsExcel(const QString &file_path) const;
    void loadHeightsFromFileSender(const QString &file_path);

    void saveSpeedsAsExcel(const QString &filepath);

// Getters
public:
    [[nodiscard]] inline const QDoubleSpinBox* getScaleDoubleSpinBox() const noexcept { return ui->scale_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getCellWidthDoubleSpinBox() const noexcept { return ui->cell_width_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getCellHeightDoubleSpinBox() const noexcept {return ui->cell_height_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getARatioDoubleSpinBox() const noexcept { return ui->ratio_double_spin_box; }
    [[nodiscard]] inline const QComboBox* getWaterObjectComboBox() const noexcept { return ui->water_object_type_combo_box; }
    [[nodiscard]] inline const Visualization3DContainer& getVisualizationContainer() const noexcept { return m_visualization_container; }

// Helpers
private:
    QPixmap getPixmapFromScene() const;
    QPixmap getPixmapFromWebEngine() const;

    void connectPaintingSignalsWithMainWindow();
};
#endif // MAINWINDOW_H
