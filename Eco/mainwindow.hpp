#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QVector>
#include <QPointF>
#include <QPair>
#include <QImage>

#include "visualization3dcontainer.hpp"
#include "painttablescene.hpp"
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

    TableContainer m_deeps_table_container;
    TableContainer m_xwind_table_container;
    TableContainer m_ywind_table_container;

    Visualization3DContainter m_visualization_container;
    QImage m_map_image;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setupTables(const QVector<QVector<QPair<bool, QPointF>>> &grid);

    void loadFronSiteButtonPressed(); // FIXME: empty
    void loadFromPCButtonPressed();

    void editImageButtonPressed();
    void saveButtonBoxClicked(QAbstractButton *btn);

signals:
    void setupTable(QTableWidget &table);

    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area);

// Getters
public:
    [[nodiscard]] inline const QDoubleSpinBox* getScaleDoubleSpinBox() const noexcept { return ui->scale_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getCellWidthDoubleSpinBox() const noexcept { return ui->cell_width_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getCellHeightDoubleSpinBox() const noexcept {return ui->cell_height_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getARatioDoubleSpinBox() const noexcept { return ui->ratio_double_spin_box; }
    [[nodiscard]] inline const QComboBox* getWaterObjectComboBox() const noexcept { return ui->water_object_type_combo_box; }
    [[nodiscard]] inline const Visualization3DContainter& getVisualizationContainer() const noexcept { return m_visualization_container; }

// Helpers
private:
    QPixmap getPixmapFromScene() const;
    QPixmap getPixmapFromWebEngine() const;
};
#endif // MAINWINDOW_H
