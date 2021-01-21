#ifndef GRIDCREATORWIDGET_HPP
#define GRIDCREATORWIDGET_HPP
#include <QWidget>
#include <QCloseEvent>
#include <QPair>

#include "painttablescene.hpp"
#include "HelperEntities/pch.hpp"
#include "HelperEntities/tablewidget.hpp"

namespace Ui {
class GridCreatorWidget;
}

class GridCreatorWidget : public QWidget
{
    Q_OBJECT

private:
    // user defined parametres
    double m_cell_width;
    double m_cell_height;
    double m_scale;

    QString m_image_filepath;
    // grid contains QPairs with row's offset and QVector of QPointF which contains left upper corner
    QVector<QVector<QPair<bool, QPointF>>> m_grid; // QPair.first - belongness flag, QPair.second - vector of values

    Ui::GridCreatorWidget *ui;

public:
    explicit GridCreatorWidget(QWidget *parent = nullptr);
    ~GridCreatorWidget();

public slots:
    // cell parametres update
    void updateCellWidth(double width) noexcept; // connected with QDoubleSpinBox (which is contained in MainWindow) (signal - valueChanged(same))
    void updateCellHeight(double height) noexcept; // connected with QDoubleSpinBox (which is contained in MainWindow) (signal - valueChanged(same))
    void updateScale(double scale) noexcept; // connected with QDoubleSpinBox (which is contained in MainWindow) (singal - valueChanged(same))

    void createGridArea(const QString &image_filepath); // connected with MainWindow (signal - createGrid(same))
    void updateFullMap(); // connected with MainWindow (signal - updateFullMapButtonPressed())
    void updateGrid(); // connected with MainWindow (signal - updateGridButtonPressed())
    void editGrid(TableWidget *table); // connected with MainWindow (signal = editGridButtonPressed()); WARNING: makes implicit connection with TableWidget
    void tableWidgetClosed(TableWidget *table); // connected with TableWidget (signal - closeSignal(TableWidget)); WARNING: makes implicit disconnection with TableWidget

signals:
    void gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &grid); // emitted when grid changes (emit in function: closeEvent)

    // saves the current pixmap in MainWindow label
    void saveMapInLabel(QPixmap map); // is emitted when final map is ready (emit function: closeEvent)

// Overridden functions
protected:
    // redefines the base class function
    void closeEvent(QCloseEvent *event) override;

// helper methods
private:
    void gridCreation();
    void drawGrid(QPixmap& pixmap);
    QPixmap getPixmapFromScene(); // draw a cuurent scene in QPixmap
    void extraCellsDeletion();
};

#endif
