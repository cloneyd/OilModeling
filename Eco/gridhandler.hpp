#ifndef GRIDHANDLER_HPP
#define GRIDHANDLER_HPP
#include <QObject>
#include <QVector>
#include <QPointF>
#include <QPair>
#include <QPixmap>
#include <QTableWidget>

#include "grid_handler_utilities.hpp"

class GridHandler : public QObject
{
    Q_OBJECT

// constants
public:
    static constexpr double max_parameters_diff{ 5. }; // max difference between (cell_width + cell_height) / 2 and scale
    static constexpr double max_spin_error{ 1e-3 }; // max double spin box error
    static inline double realscale{ 1. };

private:
    double m_cell_width;
    double m_cell_height;
    double m_scale;

    QVector<QVector<QPair<bool, QPointF>>> m_grid; // QPair.first - belongness flag, QPair.second - vector of values

public:
    GridHandler();

public slots:
    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area, const QColor &color = Qt::cyan, double line_width = 3.); // connected with MainWindow; siganl - createGrid(same)
    void deleteGrid(); // connected with MainWindow; signal - deleteGrid()
    void drawGridInPixmap(QPixmap &pm, const QColor &color, double line_width) const;

    void searchMarkInGrid(int source_index, const QPointF &mark_pos, QPoint *sector = nullptr) const;

    void setScale(double scale) noexcept; // connected with DoubleSpinBox (from MainWindow); signal - valueChanged(same)
    void setCellWidth(double cell_width) noexcept; // connected with DoubleSpinBox (from MainWindow); signal - valueChanged(same)
    void setCellHeight(double cellHeight) noexcept; // connected with DoubleSpinBox (from MainWindow); signal - valueChanged(same

signals:
    void gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &grid) const;

    void xStepChanged(const double step) const;
    void yStepChanged(const double step) const;

    void denyLastMark(int source_index) const;    

// helper funtions
private:
    void includeWaterObjectArea(QVector<QPointF> water_object_area, QVector<QPointF> islands_area);
};

#endif // GRIDHANDLER_HPP
