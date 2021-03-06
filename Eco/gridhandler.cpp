#include "gridhandler.hpp"

#include <QWidget>
#include <QMessageBox>
#include <QPainter>
#include <QScreen>

#include <algorithm>

GridHandler::GridHandler() :
    QObject{},
    m_cell_width{},
    m_cell_height{},
    m_scale{}
{
    realscale = QWidget{}.screen()->physicalDotsPerInch() / 2.54;
}


// public slots
void GridHandler::createGrid(QPixmap &pm, const QVector<QPointF> &water_object_area, const QVector<QPointF> &islands_area, const QColor &color, double line_width)
{
    m_grid.clear();

    auto water_object_area_size{ water_object_area.size() };
    if(water_object_area_size == 0) return;

    auto xmin{ water_object_area[0].x() };
    auto xmax{ xmin };
    auto ymin{ water_object_area[0].y() };
    auto ymax{ ymin };

    for(int i{ 1 }; i < water_object_area_size; ++i){
        auto x{ water_object_area[i].x() };
        auto y{ water_object_area[i].y() };

        xmin = std::min(xmin, x);
        xmax = std::max(xmax, x);
        ymin = std::min(ymin, y);
        ymax = std::max(ymax, y);
    }

    auto cell_width{ realscale * m_cell_width };
    auto cell_height{ realscale * m_cell_height };
    m_grid.reserve(static_cast<int>(std::ceil((ymax - ymin) / cell_height)));
    for(auto y{ ymin }; ymax - y > 0; y += cell_height){
        QVector<QPair<bool, QPointF>> tmp;
        tmp.reserve(static_cast<int>(std::ceil((xmax - xmin) / cell_width)));
        for(auto x{ xmin }; xmax - x > 0; x += cell_width){
            tmp.append(qMakePair(false, QPointF(x, y)));
        }
        m_grid.append(std::move(tmp));
    }

    if((m_scale / ((m_cell_height + m_cell_width)) / 2.) > max_parameters_diff) {
        QMessageBox::warning(nullptr, QString("Погрешность разбиения"), QString("Внимание:\nтак как разница между размерами ячейки и\nмасштабом слишком большая,\n возможны неточности"));
    }

    includeWaterObjectArea(water_object_area, islands_area);
    drawGridInPixmap(pm, color, line_width);

    emit gridChanged(m_grid);
}

void GridHandler::deleteGrid()
{
    m_grid.clear();
    emit gridChanged(m_grid);
}

void GridHandler::drawGridInPixmap(QPixmap &pm, const QColor &color, double line_width) const
{
    QPainter painter;

    painter.begin(&pm);
    painter.setPen({ color, line_width });
    auto grid_size{m_grid.size()};
    auto cell_width{ realscale * m_cell_width };
    auto cell_height{ realscale * m_cell_height };
    for(int i{}; i < grid_size; ++i){
        auto size {m_grid[i].size()};
        for(int j{}; j < size; ++j) {
            if(m_grid[i][j].first) {
                auto x{ m_grid[i][j].second.x() };
                auto y{ m_grid[i][j].second.y() };
                painter.drawLines({ QLineF(m_grid[i][j].second, QPointF(x + cell_width, y)),
                                    QLineF(QPointF(x + cell_width, y), QPointF(x + cell_width, y + cell_height)),
                                    QLineF(QPointF(x + cell_width, y + cell_height), QPointF(x, y + cell_height)),
                                    QLineF(QPointF(x, y + cell_height), m_grid[i][j].second)});
            }
        }
    }
    painter.end();
}


// setters
void GridHandler::setScale(double scale) noexcept
{
    if(scale < max_spin_error) {
        realscale = 1.;
        m_scale = 0.;
    }
    else {
        realscale = QWidget{}.screen()->physicalDotsPerInch() / 2.54;
        realscale /= scale;
        m_scale = scale;
    }
}

void GridHandler::setCellWidth(double cell_width) noexcept
{
    m_cell_width = cell_width;
    emit xStepChanged(m_cell_width);
}

void GridHandler::setCellHeight(double cell_height) noexcept
{
    m_cell_height = cell_height;
    emit yStepChanged(m_cell_height);
}


// private functions
void GridHandler::includeWaterObjectArea(QVector<QPointF> water_object_area, QVector<QPointF> islands_area) // takes to copies
{
    auto rows {m_grid.size() };
    auto cols{ rows > 0 ? m_grid[0].size() : 0 };
    auto cell_height{ realscale * m_cell_height };
    auto cell_width{ realscale * m_cell_width };

    auto water_area_size{ water_object_area.size() };
    std::sort(water_object_area.begin(), water_object_area.end(), [](QPointF first, QPointF second) {return (first.y() - second.y()) < 0.; }); // WARNING: floating point number comparation)
    QVector<QVector<int>> water_object_width_indexes(rows);
    QVector<QVector<int>> water_object_height_indexes(cols);

// FIXME: islands exclusion
    auto islands_area_size{ islands_area.size() };
    QVector<QVector<int>> islands_width_indexes;
    QVector<QVector<int>> islands_height_indexes;
    if(islands_area_size > 0) {
        std::sort(islands_area.begin(), islands_area.end(), [](QPointF first, QPointF second) {return (first.y() - second.y()) < 0.; }); // WARNING: floating point number comparation)
        islands_width_indexes.resize(rows);
        islands_height_indexes.resize(cols);
    }

    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            for(int k{ }; k < water_area_size; ++k) {
                // WARNING: if the cell size will be small enough (relative to scale) there is will be empty spaces
                if(water_object_area[k].x() >= m_grid[i][j].second.x() && // WARNING: float point number compare
                    water_object_area[k].x() <= m_grid[i][j].second.x() + cell_width &&
                    water_object_area[k].y() >= m_grid[i][j].second.y() &&
                    water_object_area[k].y() <= m_grid[i][j].second.y() + cell_height) {
                    m_grid[i][j].first = true;
                    water_object_width_indexes[i].append(j);
                    water_object_height_indexes[j].append(i);
                }
            }

            for(int k{}; k < islands_area_size; ++k) {
                if(islands_area[k].x() >= m_grid[i][j].second.x() && // WARNING: float point number compare
                    islands_area[k].x() <= m_grid[i][j].second.x() + cell_width &&
                    islands_area[k].y() >= m_grid[i][j].second.y() &&
                    islands_area[k].y() <= m_grid[i][j].second.y() + cell_height) {
                    m_grid[i][j].first = true;
                    islands_width_indexes[i].append(j);
                    islands_height_indexes[j].append(i);
                }
            }
        }

    }

    for(int i{}; i < rows; ++i) {
        if(auto size{ water_object_width_indexes[i].size() }; size < 2) {
            if(size == 0) {
                water_object_width_indexes[i].append(QVector{ cols, -1 });
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

    for(int i{}; i < cols; ++i) {
        if(auto size{ water_object_height_indexes[i].size() }; size < 2) {
            if(size == 0) {
                water_object_height_indexes[i].append(QVector{ rows, -1 });
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

    if(islands_area_size > 0) {
        for(int i{}; i < rows; ++i) {
            if(auto size{ islands_width_indexes[i].size() }; size < 2) {
                if(size == 0) {
                    islands_width_indexes[i].append(QVector{ cols, -1 });
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

       for(int i{}; i < cols; ++i) {
            if(auto size{ islands_height_indexes[i].size() }; size < 2) {
                if(size == 0) {
                    islands_height_indexes[i].append(QVector{ rows, -1 });
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

    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(!m_grid[i][j].first) {
                if(j > water_object_width_indexes[i][0] &&
                    j < water_object_width_indexes[i][water_object_width_indexes[i].size() - 1] &&
                    i > water_object_height_indexes[j][0] &&
                    i < water_object_height_indexes[j][water_object_height_indexes[j].size() - 1]) {
                    m_grid[i][j].first = true;
                }
            }
        }
    }

    if(islands_area_size > 0) {
        for(int i{}; i < rows; ++i) {
            for(int j{}; j < cols; ++j) {
                if(j > islands_width_indexes[i][0] &&
                    j < islands_width_indexes[i][islands_width_indexes[i].size() - 1] &&
                    i > islands_height_indexes[j][0] &&
                    i < islands_height_indexes[j][islands_height_indexes[j].size() - 1])
                {
                    m_grid[i][j].first = false;
                }
            }
        }
    }
}

void GridHandler::searchMarkInGrid(int source_index, const QPointF &mark, QPoint *sector) const
{
    auto nrows { m_grid.size() };
    if(nrows == 0)  return;
    auto ncols{ m_grid[0].size() };
    if(ncols == 0) return;

    auto cell_width{ realscale * m_cell_width };
    auto cell_height{ realscale * m_cell_height };

    if(mark.x() < m_grid[0][0].second.x() || mark.x() > m_grid[0][ncols - 1].second.x() ||
       mark.y() < m_grid[0][0].second.y() || mark.y() > m_grid[nrows - 1][0].second.y()) {
         QMessageBox::warning(nullptr, QString("Ошибка"), QString("Источник загрязнения вне водного объекта.\n"));
         emit denyLastMark(source_index);
         return;
    }

    for(int i{}; i < nrows; ++i) {
        if(mark.y() >= m_grid[i][0].second.y() && mark.y() <= m_grid[i][0].second.y() + cell_height) {
            for(int j{}; j < ncols; ++j) {
                if(mark.x() >= m_grid[i][j].second.x() && mark.x() <= m_grid[i][j].second.x() + cell_width) {
                    if(!m_grid[i][j].first) {
                        QMessageBox::warning(nullptr, "Ошибка метки", "Источник загрязнения лежит на острове.\n");
                        emit denyLastMark(source_index);
                    }
                    else {
                        if(sector) {
                            sector->setX(j);
                            sector->setY(i);
                        }
                    }
                }
            }
        }
    }
}


// non member functions
double toRealMetres(double pixels) { return pixels / GridHandler::realscale; }

double fromRealMetres(double metres) { return metres * GridHandler::realscale; }
