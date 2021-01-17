#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QMainWindow>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QString>

#include "HelperEntities/tablewidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QLabel *m_map_label;
    TableWidget *m_table;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void loadMapButtonPressed(); // connected with load_map_button (ui)
    void openMapButtonPressed(); // connected with open_map_button (ui)
    void saveMapAsExcelButtonPressed(); // connected with save_map_as_excel_button (ui)
    void saveMapAsImageButtonPressed(); // connected with save_map_as_image_button (ui)
    void openMapVisualizationButtonPressed(); // connected with open_map_visualization_button (ui)
    void enterHeightsButtonPressed(); // connected with enter_heights_button (ui)
    void updateFullMapButtonPressed(); // connected with update_map_button (ui)
    void updateGridButtonPressed(); // connected with update_grid_button (ui)

    void saveMapInLabel(QPixmap pm); // connected with GridCreatorWidget (signal - saveMapInLabel)

signals:
    void createGrid(const QString &filepath);
    void updateFullMap();
    void updateGrid();

    void openMapVisualization();
    void setupTableWidget(TableWidget *table);

    void saveMapAsExcel(const QString &filepath);

// getters
public:
    [[nodiscard]] const QDoubleSpinBox* getCellWidthBox() const noexcept;
    [[nodiscard]] const QDoubleSpinBox* getCellHeightBox() const noexcept;
    [[nodiscard]] const QDoubleSpinBox* getScaleBox() const noexcept;

};
#endif // MAINWINDOW_HPP
