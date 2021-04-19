#ifndef PAINTINGWIDGET_HPP
#define PAINTINGWIDGET_HPP
// QT
#include <QWidget>
#include <QPixmap>
#include <QScreen>
#include <QKeyEvent>

// STL
#include <list>
#include <memory>
#include <variant>

// current project
#include "paintingwidget_utilities.hpp"
#include "painttablescene.hpp" // includes pch
#include "PollutionWidget/pollutionwidget_utilities.hpp"
#include "GridHandlerFiles/grid_handler_utilities.hpp"

// UI
#include "ui_paintingwidget.h"
#include "ui_grid_parameters.h"

namespace Ui {
    class PaintingWidget;
}


class PaintingWidget : public QWidget
{
    Q_OBJECT

public:
    static constexpr double s_image_width_aspect_ratio{ .75 };
    static constexpr double s_image_height_aspect_ratio{ .75 };

private: // data
    QPixmap m_map_pixmap; // hold source image (unchanged)

    /* this class in charge of action log; PaintTableScene emit signals which will change log in two cases:
     * 1) smth was drawn with mouse (mousePressEvent and MouseDoubleClickEvent)
     * 2) smth was deleted by PaintTableScene (mouseDoubleClickEvent)
     * all other cases must be tracked by PaintingWidget */
    std::list<ActionMakers> m_actions_buf; // contains log of buffering actions
    std::list<ActionMakers> m_stashed_actions; // contains log of stashing actions
    std::list<int> m_source_indexes_buffer; // contains indexes of sources where mark was added; used for marks (deletion and creation)
    std::list<int> m_stashed_indexes; // stashed source indexes; used for marks (deletion and creation)
    QVector<SourceType> m_sources_types_buf; // contains types of added sources

    struct {
        double m_scale;
        double m_cell_width;
        double m_cell_height;
    } m_grid_parameters_buffer;

    bool m_is_ctrl_held; // false by default
    bool m_is_grid_created; // false by default
    bool m_is_update_required; // false by default

    // ui
    QWidget m_grid_parameters_widget;
    std::unique_ptr<Ui::PaintingWidget> m_ui;
    std::unique_ptr<Ui::GridParameters> m_grid_parameters_ui;
    std::unique_ptr<PaintTableScene> m_scene;

public:
    PaintingWidget(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags{});

public slots:
    void setImage(QPixmap &image); // TAKES OWNERSHIP on image; connected with: MainWindow::[22] emits [1], [4], [8]
    void setImage(const QString &filepath, bool *operation_status = nullptr); // loads image; connected with MainWindow::[23] emits [1], [4], [8] if successed
    inline void acceptScale(double scale) { m_grid_parameters_ui->scale_double_spin_box->setValue(scale); } // connected with MainWindow::[16]
    inline void acceptCellWidth(double width) { m_grid_parameters_ui->cell_width_double_spin_box->setValue(width); } // connected with MainWindow::[17]
    inline void acceptCellHeight(double height) { m_grid_parameters_ui->cell_height_double_spin_box->setValue(height); } // connected with MainWindow::[18]
    inline void giveCurrentMapImage(QPixmap &pm) const { pm = m_map_pixmap; }

    //void saveEdittedMapInFile(const QString &filepath, bool *operation_status = nullptr); // connected with MainWindow::[7];

    void deleteSource(int source_index); // connected with MainWindow::[30]; no updateCoordinates is needed
    void appendNewSource(const PointSource &source); // connected with PollutionWidgetGenerator::[1]; emits: [6], {7}
    void appendNewSource(const DiffusionSource &source); // connected with PollutionWidgetGenerator::[3]; emits [6], {7}
    void updateSource(int source_index, const PointSource &source); // connected with PollutionWidgetGenerator::[2]; emits: [6], {7}
    void updateSource(int source_index, const DiffusionSource &source); // connected with PollutionWidgetGenerator::[4]; emits [6], {7}

    void saveState(QTextStream &stream, const char delim); // connected with InternalConfigurationFilesHandler::[5]
    // connected with InternalConfigurationFilesHandler::[6]; emits: [1], (5), (6), [7]
    void restoreState(QTextStream &stream, const char delim);

private slots:
    void waterObjectChanged(ChangeType change_type); // connected with PaintTableScene::[1]
    void islandsChanged(ChangeType /*unused*/); // connected with PaintTableScene::[2]; ChangeType deprecated now
    /* connected with PaintTableScene::[3]; ChangeType deprecated now;
     * if m_is_grid_created == true searches for the point in grid and rejects it if point will be not found*/
    void sourcesMarksChanged(ChangeType /*unused*/, const QPointF &pixel_pos); // emits: [6]
    void gridParametersUpdateRejected(); // connected with Ui::GridParameters::[1];
    void clearContentButtonPressed(); // connected with Ui::[1]; emits: {3}, {4}
    void returnButtonPressed(); // connected with Ui::[2]; emits: {3}, {4}
    void forwardButtonPressed(); // connected with Ui::[3]; emits: {3}
    void changeGridParametersButtonPressed(); // connected with Ui::[4];
    void createGridButtonPressed(PaintStyle style = PaintStyle::Ellipse); // connected with Ui::[5]; emits: [3]
    void saveChangesButtonPressed(); // connected with Ui::[6]; emits: [1],{3}, [7];
    void discardChangesButtonPressed(); // connected with Ui::[7]; emits: [1], {4}, [7]
    void sourceNameComboBoxIndexChanged(int index); // connected with Ui::[8]
    // connected with PaintTableScene::[4]; sets current index in given value
    inline void giveCurrentSourceIndex(int &will_be_index) const { will_be_index = m_ui->source_name_combo_box->currentIndex(); }
    inline void giveSourceType(int source_index, SourceType &will_be_type) const // connected with PaintTableScene::[5]; sets current source type in given value
    { will_be_type = m_sources_types_buf[source_index]; }
    /* connected with Ui::CellParameters[1];
     * emits: [2] */
    inline void updateGridParameters();

signals:
    void imageChanged(const QPixmap &image, bool is_grid_created) const; // [1]
    void gridParametersChanged(double scale, double cell_width, double cell_height) const; // [2]
    void createGrid(const QVector<QPointF> &wo_area, const QVector<QPointF> &islands_area) const; // [3]
    void deleteGrid() const; // [4]
    void drawGridOnPixmap(QPixmap &pm, const QColor &color, double line_width); // [5]
    void findMark(const QPointF &pos, QPoint *will_be_indexes) const; // [6]
    // transfers marks sources in meters (first) and there indexes on grid (second)
    void sourcesCoordinatesChanged(const QVector<QVector<QPointF>> &coordinates, const QVector<QVector<QPoint>> &indexes) const; // [7]
    void resetSources() const; // [8]; delete all sources in MainWindow and Computator

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

// helpers
private:
    void setupGridParametersConnections();
    void setupPaintTableSceneConnections();
    void setupUiConnections(); // NOTE: ???)

    void clearContent();
    void clearStashes();
    void actionMadeCheck(); // checks actions buffer and stash
    void deleteSourceChanges(int source_index); // deleting all log information about this source in action buffer
    void deleteLastWOChange(); // deleting last log information about water object in action buffer
    void repaintScene(PaintStyle style);

    void updateSourcesCoordinates() const; // emits [7]
};

// inline functions implementation
inline void PaintingWidget::updateGridParameters() { emit gridParametersChanged(m_grid_parameters_ui->scale_double_spin_box->value(),
                                                                      m_grid_parameters_ui->cell_width_double_spin_box->value(),
                                                                      m_grid_parameters_ui->cell_height_double_spin_box->value());
                                                     m_grid_parameters_buffer = {-1., -1., -1. }; }

#endif // PAINTINGWIDGET_HPP
