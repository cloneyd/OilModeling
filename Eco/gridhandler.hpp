#ifndef GRIDHANDLER_HPP
#define GRIDHANDLER_HPP

#include <QObject>
#include <QVector>
#include <QPointF>
#include <QPair>
#include <QPixmap>
#include <QTableWidget>

class GridHandler : public QObject
{
    Q_OBJECT
private:
    double m_cell_width;
    double m_cell_height;
    double m_scale;
    double m_realscale;

    QVector<QVector<QPair<bool, QPointF>>> m_grid; // QPair.first - belongness flag, QPair.second - vector of values

public:
    GridHandler();

public slots:
    void createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area); // connected with MainWindow; siganl - createGrid(same)
    void deleteGrid(); // connected with MainWindow; signal - deleteGrid()

    void setScale(double scale) noexcept; // connected with DoubleSpinBox (from MainWindow); signal - valueChanged(same)
    void setCellWidth(double cell_width) noexcept; // connected with DoubleSpinBox (from MainWindow); signal - valueChanged(same)
    void setCellHeight(double cellHeight) noexcept; // connected with DoubleSpinBox (from MainWindow); signal - valueChanged(same

signals:
    void gridChanged(const QVector<QVector<QPair<bool, QPointF>>> &grid);

// helper funtions
private:
    void includeWaterObjectArea(QVector<QPointF> water_object_area, QVector<QPointF> islands_area);

    void drawGridInPixmap(QPixmap &pm);
};

#endif // GRIDHANDLER_HPP
