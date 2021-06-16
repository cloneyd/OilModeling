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

    for(int row_index{ 1 }; row_index < wo_npoints; ++row_index){
        auto x{ wo_area[row_index].x() };
        auto y{ wo_area[row_index].y() };

        xmin = std::min(xmin, x);
        xmax = std::max(xmax, x);
        ymin = std::min(ymin, y);
        ymax = std::max(ymax, y);
    }

    const auto islands_npoints{ islands_area.size() };
    for(int row_index{ 1 }; row_index < islands_npoints; ++row_index){
        auto x{ islands_area[row_index].x() };
        auto y{ islands_area[row_index].y() };

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
    for(int row_index{}; row_index < nrows; ++row_index){
        for(int col_index{}; col_index < ncols; ++col_index) {
            if(m_pixgrid[row_index][col_index].first) {
                auto x{ m_pixgrid[row_index][col_index].second.x() };
                auto y{ m_pixgrid[row_index][col_index].second.y() };
                painter.drawLines({ QLineF(m_pixgrid[row_index][col_index].second, QPointF(x + cell_width, y)),
                                    QLineF(QPointF(x + cell_width, y), QPointF(x + cell_width, y + cell_height)),
                                    QLineF(QPointF(x + cell_width, y + cell_height), QPointF(x, y + cell_height)),
                                    QLineF(QPointF(x, y + cell_height), m_pixgrid[row_index][col_index].second) });
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

    for(int row_index{}; row_index < nrows; ++row_index) {
        for(int col_index{}; col_index < ncols; ++col_index) {
            if(isBelongToGridSector(row_index, col_index, pixel_pos) && m_pixgrid[row_index][col_index].first) {
                result.setX(col_index);
                result.setY(row_index);

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

void GridHandler::saveState(QTextStream &stream, const char delim)
{
    const auto nrows{ m_pixgrid.size() };
    const auto ncols{ nrows > 0 ? m_pixgrid[0].size() : 0 };
    stream << nrows << '\t' << ncols << delim;
    if(nrows > 0 && ncols > 0) {
        for(int row_index{}; row_index < nrows; ++row_index) {
            for(int col_index{}; col_index < ncols; ++col_index) {
                stream << m_pixgrid[row_index][col_index].first << '\t';
                stream << m_pixgrid[row_index][col_index].second.x() << '\t' <<
                          m_pixgrid[row_index][col_index].second.y() << '\t';
            }
        }
    }
    stream << delim;
    // scale will be restored by MainWindow::restoreState
    // cell width will be restored by MainWindow::restoreState
    // cell height will be restored by MainWindow::restoreState
}

void GridHandler::restoreState(QTextStream &stream, const char delim)
{
    auto readUntilDelim = [&stream](const char delim) -> QString {
        QString result{};
        char sym{};
        for(stream >> sym; sym != delim; stream >> sym) {
            result += sym;
        }
        return result;
    };

    bool is_converted{};
    const auto nrows{ readUntilDelim('\t').toInt(&is_converted) };
    Q_ASSERT(is_converted);

    const auto ncols{ readUntilDelim(delim).toInt(&is_converted) };
    Q_ASSERT(is_converted);
    m_pixgrid.fill(QVector<QPair<bool, QPointF>>(ncols, qMakePair(false, QPointF(-1., -1.))), nrows);
    for(int row_index{}; row_index < nrows; ++row_index) {
        for(int col_index{}; col_index < ncols; ++col_index) {
            const bool belongness = readUntilDelim('\t').toInt(&is_converted); // narrows
            Q_ASSERT(is_converted);

            const double x{ readUntilDelim('\t').toDouble(&is_converted) };
            Q_ASSERT(is_converted);

            const double y{ readUntilDelim('\t').toDouble(&is_converted) };
            Q_ASSERT(is_converted);

            m_pixgrid[row_index][col_index] = qMakePair(belongness, QPointF(x, y));
        }
    }

    char control_delim{};
    stream >> control_delim;
    Q_ASSERT(control_delim == delim);

    emit gridChanged(m_pixgrid);
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
        return true;
    }
    return false;
}

void GridHandler::includeWaterObject(QVector<QPointF> water_object_area) // takes to copies
{
    const auto nrows { m_pixgrid.size() };
    if(nrows == 0)  return;
    const auto ncols{ m_pixgrid[0].size() };
    if(ncols == 0)  return;

    auto water_area_size{ water_object_area.size() };
    QVector<QVector<int>> width_indexes(nrows);
    QVector<QVector<int>> height_indexes(ncols);

    for(int row_index{}; row_index < nrows; ++row_index) {
        auto last_row{ -1 };
        for(int col_index{}; col_index < ncols; ++col_index) {
            auto last_col{ -1 };
            for(int point_index{ }; point_index < water_area_size; ++point_index) {
                if(isBelongToGridSector(row_index, col_index, water_object_area[point_index])) {
                    if(row_index != last_row || col_index != last_col) {
                        m_pixgrid[row_index][col_index].first = true;
                        width_indexes[row_index].append(col_index);
                        height_indexes[col_index].append(row_index);
                        last_row = row_index;
                        last_col = col_index;
                    }
                }
            }
        }

    }

    for(int row_index{}; row_index < nrows; ++row_index) {
        if(auto size{ width_indexes[row_index].size() }; size < 2) {
            switch(size) {
            case 0:
                width_indexes[row_index].append(QVector{ ncols, -1 });
                break;

            case 1:
                width_indexes[row_index].append(width_indexes.front());
                break;

            default:
                Q_ASSERT(false);
            }
        }
    }

    for(int col_index{}; col_index < ncols; ++col_index) {
        if(auto size{ height_indexes[col_index].size() }; size < 2) {
            switch (size) {
            case 0:
                height_indexes[col_index].append(QVector{ nrows, -1 });
                break;

            case 1:
                height_indexes[col_index].append(height_indexes[col_index].front());
                break;

            default:
                Q_ASSERT(false);
            }
        }
    }

    for(int row_index{}; row_index < nrows; ++row_index) {
        if(width_indexes[row_index].back() > 0.) {
            std::sort(width_indexes[row_index].begin(), width_indexes[row_index].end());
        }
    }

    for(int col_index{}; col_index < ncols; ++col_index) {
        if(height_indexes[col_index].back() > 0.) {
            std::sort(height_indexes[col_index].begin(), height_indexes[col_index].end());
        }
    }

    for(int row_index{}; row_index < nrows; ++row_index) {
        for(int col_index{}; col_index < ncols; ++col_index) {
            if(!m_pixgrid[row_index][col_index].first) {
                if(col_index >= width_indexes[row_index].front() &&
                    col_index <= width_indexes[row_index].back() &&
                    row_index >= height_indexes[col_index].front() &&
                    row_index <= height_indexes[col_index].back()) {
                    m_pixgrid[row_index][col_index].first = true;
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

    QVector<QVector<int>> width_indexes;
    QVector<QVector<int>> height_indexes;
    width_indexes.resize(nrows);
    height_indexes.resize(ncols);

    for(int row_index{}; row_index < nrows; ++row_index) {
        auto last_row{ -1 };
        for(int col_index{}; col_index < ncols; ++col_index) {
            auto last_col{ -1 };
            for(int point_index{}; point_index < islands_area_size; ++point_index) {
                if(isBelongToGridSector(row_index, col_index, islands_area[point_index])) {
                    if(row_index != last_row || col_index != last_col) {
                        m_pixgrid[row_index][col_index].first = true;
                        width_indexes[row_index].append(col_index);
                        height_indexes[col_index].append(row_index);
                        last_row = row_index;
                        last_col = col_index;
                    }
                }
            }
        }
    }

    for(int row_index{}; row_index < nrows; ++row_index) {
        if(auto size{ width_indexes[row_index].size() }; size < 2) {
            switch (size) {
            case 0:
                width_indexes[row_index].append(QVector{ ncols, -1 });
                break;

            case 1:
                width_indexes[row_index].append(width_indexes[row_index].front());
                break;

            default:
                Q_ASSERT(false);
            }
        }
    }

    for(int col_index{}; col_index < ncols; ++col_index) {
        if(auto size{ height_indexes[col_index].size() }; size < 2) {
            switch (size) {
            case 0:
                height_indexes[col_index].append(QVector{ nrows, -1 });
                break;

            case 1:
                height_indexes[col_index].append(height_indexes[col_index].front());
                break;

            default:
                Q_ASSERT(false);
            }
        }
    }

    for(int row_index{}; row_index < nrows; ++row_index) {
        if(width_indexes[row_index].back() > 0.) {
            std::sort(width_indexes[row_index].begin(), width_indexes[row_index].end());
        }
    }

    for(int col_index{}; col_index < ncols; ++col_index) {
        if(height_indexes[col_index].back() > 0.) {
            std::sort(height_indexes[col_index].begin(), height_indexes[col_index].end());
        }
    }

    for(int row_index{}; row_index < nrows; ++row_index) {
        for(int col_index{}; col_index < ncols; ++col_index) {
            if(col_index > width_indexes[row_index].front() &&
                col_index < width_indexes[row_index].back() &&
                row_index > height_indexes[col_index].front() &&
                row_index < height_indexes[col_index].back())
            {
                m_pixgrid[row_index][col_index].first = false;
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
