#ifndef GRIDHANDLER_HPP
#define GRIDHANDLER_HPP
// QT
#include <QObject>
#include <QColor>

// FIXME: it should be replaced; ???
#include <QWidget>
#include <QScreen>
// FIXME: end of fixme block

// current project
#include "grid_handler_utilities.hpp"
#include "PaintingWidget/paint_table_scene_utilities.hpp"

class GridHandler : public QObject
{
    Q_OBJECT

// static constants
public:
    static inline double s_pixscale{ 1. }; // replace static variables to templates functions 

private: // data
    // when grid is created belongness flags is false
    GridType m_pixgrid; // left upper corner coordinates in pixels; empty by default;
    double m_scale; // in real meters; -1. by default (should be invalid)
    double m_cell_width; // in real metes; -1. by default
    double m_cell_height; // in real meters; -1. by default

public:
    explicit GridHandler(QObject *parent = nullptr);
    ~GridHandler();

public slots:
    inline void acceptScale(double scale);
    inline void acceptCellWidth(double cell_width) noexcept { m_cell_width = cell_width; }
    inline void acceptCellHeight(double cell_height) noexcept { m_cell_height = cell_height; }

    inline void givePixgrid(const GridType ** will_be_grid) noexcept { *will_be_grid = std::addressof(m_pixgrid); }

    const GridType& createGrid(const QVector<QPointF> &wo_area, const QVector<QPointF> &islands_area); // emits: gridChanged
    inline void deleteGrid() /*noexcept*/; // QVector::clear is not marker as noexcept; emits: gridChanged

    void drawGridInPixmap(QPixmap &pm, const QColor &color = QColor{ QRgb{ 0x000000 } } , double line_width = 1.) const;
    /* searching for a pos in grid; if pos not exist or belongs to island - returns {-1, -1 }; if search_result is not nullptr,
       result copies to this values; .x() - contain index of x, .y() - contains index of y */
    QPoint findPoint(const QPointF &pixel_pos, QPoint *search_result = nullptr) const;

signals:
    void gridChanged(const GridType &grid) const;

// helpers
private:
    [[nodiscard]] bool verifyGridParameters() const; // true if parameters OK, else false
    [[nodiscard]] bool isBelongToGridSector(int row, int col, const QPointF &pos) const;

    void includeWaterObject(QVector<QPointF> water_object_area);
    void excludeIslands(QVector<QPointF> islands_area);
};

// inline funcitons realization
inline void GridHandler::acceptScale(double scale)
{
    m_scale = scale;
    s_pixscale = QWidget{}.screen()->physicalDotsPerInch() / 2.54 / scale; // FIXME: how to do this without QWIdget{}?
}

inline void GridHandler::deleteGrid() /*noexcept*/
{
    m_pixgrid.clear();
    emit gridChanged(m_pixgrid);
}

#endif // GRIDHANDLER_HPP
