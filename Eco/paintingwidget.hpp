#ifndef PAINTINGWIDGET_HPP
#define PAINTINGWIDGET_HPP
#include <QWidget>
#include <QPixmap>
#include <QImage>
#include <QString>

#include "ui_paintingwidget.h"

#include  "painttablescene.hpp"
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

    bool m_is_grid_drawn; // if grid was drawn becomes true; false by default
    bool m_is_ctrl_held; // if ctrl is helds become true
    bool m_is_change_made; // true if some changes on scene was made

public:
    explicit PaintingWidget(QWidget *parent = nullptr);
    ~PaintingWidget();

public slots:
    [[nodiscard]] QPixmap* getEdittedMapPixmap(QPixmap *pixmap = nullptr) const;
    [[nodiscard]] QImage* getMapImage(QImage *image = nullptr) const;

    void setScenePixmap(const QPixmap &pm);
    void prepareGraphicsView(const QString &file_path);
    void deleteLastMark(int source_index);

    void updateSources(int count, int index, SourceType type, const QString &name, const QPointF &pos);

private slots:
    void acceptChangesButtonPressed(); // connected with painting_ui->accept_changes_button
    void discardAllChangesButtonPressed(); // connected with painting_ui->discard_all_changes_button
    void updateMapButtonPressed(); // connected with painting_ui->update_map_button
    void discardLastChandesButtonPressed(); // connected with painting_ui->discard_last_changes_button
    void returnLastChangesButtonPressed(); // connected with paiting_ui->return_last_changes_button
    QPixmap showChangesButtonPressed(PaintStyle style = PaintStyle::ellipse); // connected with painting_ui->show_changes_button

    void brushType1ButtonPressed(); // connected with painting_ui->brush_type_1_button
    void brushType2ButtonPressed(); // connected with painting_ui->brush_type_2_button
    void brushType3ButtonPressed(); // connected with painting_ui->brush_type_3_button
    void brushType4ButtonPressed(); // connected with painting_ui->brush_type_4_button

    void updateGridButtonPressed(); // connected with painting_ui->update_grid_button

    void enableGridButtonPressed(); // connected with painting_ui->enable_grid_button
    void shadowNonWOButtonPressed(); // connected with painting_ui->shadow_non_wo_button

    void saveChangesButtonClicked(QAbstractButton *btn); // connected with cell_scale_width->save_changes_button

    void changeLogChanged(int nwrites);
    void changeLogStashChanged(int nwrites);
    void markPositionChanged(const QPointF &pos);
    inline void giveCurrentSourceIndex(int &index) { index = m_painting_ui->source_name_combo_box->currentIndex(); }

signals:
    void imageChanged(const QImage &image);

    void cellScaleParametersChanged(double width, double height, double scale) const;

    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area,
                    const QColor &color, double line_width);
    void deleteGrid() const;
    void drawGridInPixmap(QPixmap &map, const QColor &color, double line_width) const;
    void findMark(int source_index, const QPointF &pos, QPoint *sector = nullptr);
    void updateCoordinates(const QVector<QVector<QPointF>> &coordinates, const QVector<QVector<QPoint>> &indexes) const;

// overridden functions
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

// helpers
private:
    void setupConnectionsWithCellScaleParametersWidget();
    void repaint();
};

#endif // PAINTINGWIDGET_HPP
