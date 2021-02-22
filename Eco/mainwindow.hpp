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
    void setupTables(const QVector<QVector<QPair<bool, QPointF>>> &grid);

    void loadFronSiteButtonPressed();
    void loadFromPCButtonPressed();

    void loadHeightsFromFileButtonPressed();

    void editImageButtonPressed();
    void setImageInMapLabel(const QImage &image);

    void createGridSender(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area) const;
    void updateGridParameters(double cell_width, double cell_height, double scale) const;

    void saveHeightsFromTableSender(QTableWidget &table);
    void saveXSpeedsFromTableSender(QTableWidget &table);
    void saveYSpeedsFromTableSender(QTableWidget &table);

    void openMapVisualizationButtonPressed();
    void enterHeightsButtonPressed();
    void updateDepthTableValues(const QVector<QVector<QPair<bool, double>>> &heights);
    void saveHeightsTableButtonPressed();

    void enterSpeedVectorButtonPressed();
    void saveSpeedsButtonPressed();

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
