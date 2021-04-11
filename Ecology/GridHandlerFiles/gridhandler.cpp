// QT
#include <QPainter>

// STL
#include <cmath>
#include <algorithm>

// current project
#include "gridhandler.hpp"

GridHandler::GridHandler(QObject *parent) :
    QObject(parent), // explicitly use nullptr
    m_pixgrid{},
    m_scale{ -1. },
    m_cell_width{ -1. },
    m_cell_height{ -1. }
{ /*PASS*/ }


GridHandler::~GridHandler()
{
    deleteGrid();
}


// public slots
const GridType& GridHandler::createGrid(const QVector<QPointF> &wo_area, const QVector<QPointF> &islands_area)
{
    m_pixgrid.clear();

    if(!verifyGridParameters()) {
        emit gridChanged(m_pixgrid);
        return m_pixgrid;
    }

    const auto wo_npoints{ wo_area.size() };
    if(wo_npoints == 0) {
        emit gridChanged(m_pixgrid);
        return m_pixgrid;
    }

    auto xmin{ wo_area[0].x() };
    auto xmax{ xmin };
    auto ymin{ wo_area[0].y() };
    auto ymax{ ymin };

    for(int i{ 1 }; i < wo_npoints; ++i){
        auto x{ wo_area[i].x() };
        auto y{ wo_area[i].y() };

        xmin = std::min(xmin, x);
        xmax = std::max(xmax, x);
        ymin = std::min(ymin, y);
        ymax = std::max(ymax, y);
    }

    const auto islands_npoints{ islands_area.size() };
    for(int i{ 1 }; i < islands_npoints; ++i){
        auto x{ islands_area[i].x() };
        auto y{ islands_area[i].y() };

        xmin = std::min(xmin, x);
        xmax = std::max(xmax, x);
        ymin = std::min(ymin, y);
        ymax = std::max(ymax, y);
    }

    const auto cell_width{ s_pixscale * m_cell_width };
    const auto cell_height{ s_pixscale * m_cell_height };
    auto nrows { static_cast<int>(std::ceil((ymax - ymin) / cell_height)) };
    const auto ncols{ static_cast<int>(std::ceil((xmax - xmin) / cell_width)) };

    if(nrows == 0 || ncols == 0) {
        emit gridChanged(m_pixgrid);
        return m_pixgrid;
    }

    m_pixgrid.reserve(nrows);
    for(auto y{ ymin }; ymax - y > 0; y += cell_height){
        QVector<QPair<bool, QPointF>> tmp;
        tmp.reserve(ncols);
        tmp.reserve(static_cast<int>(std::ceil((xmax - xmin) / cell_width)));
        for(auto x{ xmin }; xmax - x > 0; x += cell_width){
            tmp.append(qMakePair(false, QPointF(x, y)));
        }
        m_pixgrid.append(std::move(tmp));
    }

    includeWaterObject(wo_area);
    excludeIslands(islands_area);

    emit gridChanged(m_pixgrid);
    return m_pixgrid;
}

void GridHandler::drawGridInPixmap(QPixmap &pm, const QColor &color, double line_width) const
{
    const auto nrows{m_pixgrid.size()};
    if(nrows == 0)  return;

    const auto ncols{ m_pixgrid.front().size() };
    if(ncols == 0) return;

    QPainter painter(&pm);
    painter.setPen({ color, line_width });
    auto cell_width{ s_pixscale * m_cell_width };
    auto cell_height{ s_pixscale * m_cell_height };
    for(int i{}; i < nrows; ++i){
        for(int j{}; j < ncols; ++j) {
            if(m_pixgrid[i][j].first) {
                auto x{ m_pixgrid[i][j].second.x() };
                auto y{ m_pixgrid[i][j].second.y() };
                painter.drawLines({ QLineF(m_pixgrid[i][j].second, QPointF(x + cell_width, y)),
                                    QLineF(QPointF(x + cell_width, y), QPointF(x + cell_width, y + cell_height)),
                                    QLineF(QPointF(x + cell_width, y + cell_height), QPointF(x, y + cell_height)),
                                    QLineF(QPointF(x, y + cell_height), m_pixgrid[i][j].second)});
            }
        }
    }
}

QPoint GridHandler::findPoint(const QPointF &pixel_pos, QPoint *search_result) const
{
    QPoint result{ -1, -1 };

    auto nrows{ m_pixgrid.size() };
    if(nrows == 0) {
        if(search_result) {
            *search_result = result;
        }
        return result;
    }

    auto ncols{ m_pixgrid[0].size() };
    if(ncols == 0) {
        if(search_result) {
            *search_result = result;
        }
        return result;
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(isBelongToGridSector(i, j, pixel_pos)) {
                 result.setX(j);
                result.setY(i);

                if(search_result) {
                    *search_result = result;
                }
                return result;
            }
        }
    }

    if(search_result) {
        *search_result = result;
    }
    return result;
}


// private functions
bool GridHandler::verifyGridParameters() const
{
    if(m_scale < GridHandlerConstants::s_max_error) { // even less than error
        QMessageBox::warning(nullptr, "Ошибка", "Значение масштаба слишком мало.\nПожалуйста, увеличьте его.");
        return false;
    }

    if(m_cell_width < GridHandlerConstants::s_max_error) { // even less than error
        QMessageBox::warning(nullptr, "Ошибка", "Значение ширины ячейки слишком мало.\nПожалуйста, увеличьте ее.");
        return false;
    }

    if(m_scale < GridHandlerConstants::s_max_error) { // even less than error
        QMessageBox::warning(nullptr, "Ошибка", "Значение высоты ячейки слишком мало.\nПожалуйста, увеличьте его.");
        return false;
    }

    if(std::sqrt(std::pow(s_pixscale * m_cell_height, 2) + std::pow(s_pixscale * m_cell_width, 2))
            < PaintTableSceneConstants::s_line_width * PaintTableSceneConstants::s_length_ratio) {
        QMessageBox::warning(nullptr, "Предупреждение", "Слишком маленький шаг сетки.\nВозможны ошибки разбиения");
    }

    return true;
}

bool GridHandler::isBelongToGridSector(int row, int col, const QPointF &pos) const
{
    const auto cell_width{ s_pixscale * m_cell_width };
    const auto cell_height{ s_pixscale * m_cell_height };

    if(pos.x() >= m_pixgrid[row][col].second.x() &&
       pos.x() <= m_pixgrid[row][col].second.x() + cell_width &&
       pos.y() >= m_pixgrid[row][col].second.y() &&
       pos.y() <= m_pixgrid[row][col].second.y() + cell_height) {
        return true && m_pixgrid[row][col].first;
    }
    return false;
}

void GridHandler::includeWaterObject(QVector<QPointF> water_object_area) // takes to copies
{
    const auto nrows {m_pixgrid.size() };
    const auto ncols{ nrows > 0 ? m_pixgrid[0].size() : 0 };
    const auto cell_height{ s_pixscale * m_cell_height };
    const auto cell_width{ s_pixscale * m_cell_width };

    auto water_area_size{ water_object_area.size() };
    std::sort(water_object_area.begin(), water_object_area.end(), [](QPointF first, QPointF second) {return (first.y() - second.y()) < 0.; }); // WARNING: floating point number comparation)
    QVector<QVector<int>> water_object_width_indexes(nrows);
    QVector<QVector<int>> water_object_height_indexes(ncols);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            for(int k{ }; k < water_area_size; ++k) {
                // WARNING: if the cell size will be small enough (relative to scale) there is will be empty spaces
                if(water_object_area[k].x() >= m_pixgrid[i][j].second.x() && // WARNING: float point number compare
                    water_object_area[k].x() <= m_pixgrid[i][j].second.x() + cell_width &&
                    water_object_area[k].y() >= m_pixgrid[i][j].second.y() &&
                    water_object_area[k].y() <= m_pixgrid[i][j].second.y() + cell_height) {
                    m_pixgrid[i][j].first = true;
                    water_object_width_indexes[i].append(j);
                    water_object_height_indexes[j].append(i);
                }
            }
        }

    }

    for(int i{}; i < nrows; ++i) {
        if(auto size{ water_object_width_indexes[i].size() }; size < 2) {
            if(size == 0) {
                water_object_width_indexes[i].append(QVector{ ncols, -1 });
            }
            else {
                if(i == 0) {
                    water_object_width_indexes[i].append(water_object_width_indexes[i][0]);
                }
                else {
                    water_object_width_indexes[i].append(water_object_width_indexes[i - 1][water_object_width_indexes[i - 1].size() - 1]);
                }
            }
        }
    }

    for(int i{}; i < ncols; ++i) {
        if(auto size{ water_object_height_indexes[i].size() }; size < 2) {
            if(size == 0) {
                water_object_height_indexes[i].append(QVector{ nrows, -1 });
            }
            else {
                if(i == 0) {
                    water_object_height_indexes[i].append(water_object_height_indexes[i][0]);
                }
                else {
                    water_object_height_indexes[i].append(water_object_height_indexes[i - 1][water_object_height_indexes[i - 1].size() - 1]);
                }
            }
        }
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(!m_pixgrid[i][j].first) {
                if(j > water_object_width_indexes[i][0] &&
                    j < water_object_width_indexes[i][water_object_width_indexes[i].size() - 1] &&
                    i > water_object_height_indexes[j][0] &&
                    i < water_object_height_indexes[j][water_object_height_indexes[j].size() - 1]) {
                    m_pixgrid[i][j].first = true;
                }
            }
        }
    }
}

void GridHandler::excludeIslands(QVector<QPointF> islands_area)
{
    auto islands_area_size{ islands_area.size() };
    if(islands_area_size == 0)  return;

    const auto nrows {m_pixgrid.size() };
    if(nrows == 0)  return;
    const auto ncols{ m_pixgrid[0].size() };
    if(ncols == 0)  return;
    const auto cell_height{ s_pixscale * m_cell_height };
    const auto cell_width{ s_pixscale * m_cell_width };

    QVector<QVector<int>> islands_width_indexes;
    QVector<QVector<int>> islands_height_indexes;
    std::sort(islands_area.begin(), islands_area.end(), [](QPointF first, QPointF second) {return (first.y() - second.y()) < 0.; }); // WARNING: floating point number comparation)
    islands_width_indexes.resize(nrows);
    islands_height_indexes.resize(ncols);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            for(int k{}; k < islands_area_size; ++k) {
                if(islands_area[k].x() >= m_pixgrid[i][j].second.x() && // WARNING: float point number compare
                    islands_area[k].x() <= m_pixgrid[i][j].second.x() + cell_width &&
                    islands_area[k].y() >= m_pixgrid[i][j].second.y() &&
                    islands_area[k].y() <= m_pixgrid[i][j].second.y() + cell_height) {
                    m_pixgrid[i][j].first = true;
                    islands_width_indexes[i].append(j);
                    islands_height_indexes[j].append(i);
                }
            }
        }
    }

    if(islands_area_size > 0) {
        for(int i{}; i < nrows; ++i) {
            if(auto size{ islands_width_indexes[i].size() }; size < 2) {
                if(size == 0) {
                    islands_width_indexes[i].append(QVector{ ncols, -1 });
                }
                else {
                    if(i == 0) {
                        islands_width_indexes[i].append(islands_width_indexes[i][0]);
                    }
                    else {
                        islands_width_indexes[i].append(islands_width_indexes[i - 1][islands_width_indexes[i - 1].size() - 1]);
                    }
                }
            }
        }

       for(int i{}; i < ncols; ++i) {
            if(auto size{ islands_height_indexes[i].size() }; size < 2) {
                if(size == 0) {
                    islands_height_indexes[i].append(QVector{ nrows, -1 });
                }
                else {
                    if(i == 0) {
                        islands_height_indexes[i].append(islands_height_indexes[i][0]);
                    }
                    else {
                        islands_height_indexes[i].append(islands_height_indexes[i - 1][islands_height_indexes[i - 1].size() - 1]);
                    }
                }
            }
        }
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(j > islands_width_indexes[i][0] &&
                j < islands_width_indexes[i][islands_width_indexes[i].size() - 1] &&
                i > islands_height_indexes[j][0] &&
                i < islands_height_indexes[j][islands_height_indexes[j].size() - 1])
            {
                m_pixgrid[i][j].first = false;
            }
        }
    }
}


// grid_handler_utilities.hpp functions
[[nodiscard]] double toPixels(double meters) noexcept
{
    return meters * GridHandler::s_pixscale;
}

[[nodiscard]] double toMeters(double pixels) noexcept
{
    return pixels / GridHandler::s_pixscale;
}
