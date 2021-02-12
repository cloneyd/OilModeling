#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QMainWindow>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QString>

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QLabel *m_map_label;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadMapButtonPressed(); // connected with load_map_button (ui)

    void openMapButtonPressed(); // connected with open_map_button (ui)
    void openMapVisualizationButtonPressed(); // connected with open_map_visualization_button (ui)

    void saveMapAsExcelButtonPressed(); // connected with save_map_as_excel_button (ui)
    void saveMapAsImageButtonPressed(); // connected with save_map_as_image_button (ui)

    void enterHeightsButtonPressed(); // connected with enter_heights_button (ui)
    void enterSpeedVectorsButtonPressed(); // connected with enter_speed_vectors_button (ui)

    void updateFullMapButtonPressed(); // connected with update_map_button (ui)
    void updateGridButtonPressed(); // connected with update_grid_button (ui)

    void saveMapInLabel(QPixmap pm); // connected with GridCreatorWidget (signal - saveMapInLabel)

signals:
    void createGrid(const QString &filepath);
    void updateFullMap();
    void updateGrid();

    void openMapVisualization();
    void displayDeepsTableWidget();
    void displaySpeedsTableWidget();

    void saveMapAsExcel(const QString &filepath);

// getters
public:
    [[nodiscard]] inline const QDoubleSpinBox* getCellWidthBox() const noexcept { return ui->cell_width_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getCellHeightBox() const noexcept { return ui->cell_height_spin_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getScaleBox() const noexcept { return ui->scale_spin_box; }
    [[nodiscard]] inline const QComboBox* getWaterObjectTypeComboBox() const noexcept { return ui->water_object_type_combo_box; }
    [[nodiscard]] inline const QDoubleSpinBox* getARatioSpinBox() const noexcept { return ui->ratio_double_spin_box; }
};
#endif // MAINWINDOW_HPP
