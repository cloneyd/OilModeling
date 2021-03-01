#ifndef PAINTINGWIDGET_HPP
#define PAINTINGWIDGET_HPP

#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QString>

#include "ui_cell_scale_parameters.h"
// TODO: thickness bar have not slot

namespace Ui {
class PaintingWidget;
}

class PaintingWidget : public QWidget
{
    Q_OBJECT

public:
    static constexpr double image_scale_ratio { .75 };

private:
    Ui::PaintingWidget *m_painting_ui;
    Ui::cell_scale_parametres *m_cell_scale_parameters_ui;

    QImage m_map_image;

    QWidget m_cell_scale_parameters;

    bool m_is_accept_changes_flag; // if show changes button pressed flag become false, if accept changes button pressed flag become true; true by default

public:
    explicit PaintingWidget(QWidget *parent = nullptr);
    ~PaintingWidget();

public slots:
    void acceptChangesButtonPressed(); // connected with painting_ui->accept_changes_button
    void discardAllChangesButtonPressed(); // connected with painting_ui->discard_all_changes_button
    void updateMapButtonPressed(); // connected with painting_ui->update_map_button
    void discardLastChandesButtonPressed(); // connected with painting_ui->discard_last_changes_button
    void returnLastChangesButtonPressed(); // connected with paiting_ui->return_last_changes_button
    void showChangesButtonPressed(); // connected with painting_ui->show_changes_button

    void brushType1ButtonPressed(); // connected with painting_ui->brush_type_1_button
    void brushType2ButtonPressed(); // connected with painting_ui->brush_type_2_button
    void brushType3ButtonPressed(); // connected with painting_ui->brush_type_3_button
    void brushType4ButtonPressed(); // connected with painting_ui->brush_type_4_button

    void updateGridButtonPressed(); // connected with painting_ui->update_grid_button

    void enableGridButtonPressed(); // connected with painting_ui->enable_grid_button
    void shadowNonWOButtonPressed(); // connected with painting_ui->shadow_non_wo_button

    void saveChangesButtonClicked(QAbstractButton *btn); // connected with cell_scale_width->save_changes_button

signals:
    void imageChanged(const QImage &image);

    void cellScaleParametersChanged(double width, double height, double scale) const;

    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area);
    void deleteGrid() const;

// setters
public:
    void setScenePixmap(const QPixmap &pm);

// getters
public:
    QPixmap getEdittedMapPixmap() const;

    [[nodiscard]] inline const QImage& getMapImage() const noexcept { return m_map_image; }

// redefined functions
public:
    void close();

// modificators
public:
    void prepareGraphicsView(const QString &file_path);

// helpers
private:
    void setupConnectionsWithCellScaleParametersWidget();

    QPixmap drawAreasInMap();
};

#endif // PAINTINGWIDGET_HPP