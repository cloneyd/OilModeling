#include "visualization3dobject.hpp"

#include <algorithm>
#include <QPainter>
#include <Q3DTheme>


// ctors and dtor
Visualization3DObject::Visualization3DObject(QtDataVisualization::Q3DSurface *graph) :
    QObject(nullptr),
    m_grid{},
    m_heights{},
    m_graph{ graph },
    m_realscale{},
    m_gr(0, 0, 1, 480) // magic numbers
{
    // gradient setup
    m_gr.setColorAt(1.f, QColor(0x9F6342));
    m_gr.setColorAt(.99f, Qt::darkBlue);
    m_gr.setColorAt(.9f, Qt::blue);
    m_gr.setColorAt(.8f, Qt::cyan);
    m_gr.setColorAt(.7f, Qt::gray);
    m_gr.setColorAt(.6f, Qt::darkGreen);
    m_gr.setColorAt(.5f, Qt::green);
    m_gr.setColorAt(.4f, Qt::darkYellow);
    m_gr.setColorAt(.3f, Qt::yellow);
    m_gr.setColorAt(.2f, Qt::red);
    m_gr.setColorAt(.1f, Qt::darkRed);
    m_gr.setColorAt(.0f, Qt::darkMagenta);
}

Visualization3DObject::~Visualization3DObject() noexcept
{
    delete m_graph;
}

// setters (public methods)
void Visualization3DObject::setGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid) /*noexcept*/
{
    m_grid = grid;
    auto rows {m_grid.size() };
    auto cols{ rows > 0 ? grid[0].size() : 0 };
    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            m_grid[i][j].second /= m_realscale;
        }
    }
    m_heights.clear();
}

void Visualization3DObject::setHeights(const QVector<QVector<QPair<bool, double>>> &heights) /*noexcept*/
{
    m_heights = heights;
    updateMap();
}

void Visualization3DObject::setScale(double scale) noexcept
{
    m_realscale = scale;
    // no update is needed cause of GridCreatorWidget updates grid
}


// Getters (publics methods)
[[nodiscard]] QPixmap Visualization3DObject::getGradientPixmap() const
{
    const auto width{ 100 };
    const auto height{ 500 };
    const auto border{ 20 };
    const auto ncolors{ 10 };

    QPixmap pm(width, height); // gradiend map
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(m_gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border); // painting a map
    pmp.setPen(Qt::black);

    double max_map_height{};
    if(m_heights.empty()) {
        max_map_height = 100.;
    }
    else {
        auto rows(m_heights.size());
        auto cols{ rows > 0 ? m_heights[0].size() : 0 };
        for(int i{}; i < rows; ++i) {
            for(int j{}; j < cols; ++j) {
                if(m_heights[i][j].first) {
                    max_map_height = std::max(max_map_height, m_heights[i][j].second);
                }
            }
        }
    }
    const double pieces {max_map_height / ncolors}; // distance between pieces
    double step = (height - 2. * border) / ncolors;
    for (std::uint16_t i{}; i <= ncolors; ++i) {
        const std::uint16_t yPos{static_cast<const std::uint16_t>(i * step + border)};
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 м").arg(max_map_height - (i * pieces)));
    }

    return pm;
}


// Public methods
void Visualization3DObject::updateMap()
{
    if(auto series{ m_graph->seriesList() }; !(series.empty())) m_graph->removeSeries(series.at(0)); // if m_graph have old series, it must be deleted
    if(m_grid.empty())   return; // if there is no new grid

    auto rows {m_grid.size() };
    auto cols{ rows > 0 ? m_grid[0].size() : 0 };

    QVector<QVector<QVector3D>> coords(rows);
    // Note: Q3DVisualization3DObject standart axis a bit confusing: Y axe is the height axe
    if(m_heights.empty()) {
        for(int i{}; i < rows; ++i) {
            QVector<QVector3D> tmp(cols, {-1, -1, -1});
            for(int j{}; j < cols; ++j) {
                tmp[j] = QVector3D(m_grid[i][j].second.x() - m_grid[0][0].second.x(),
                         0.,
                         m_grid[i][j].second.y() - m_grid[0][0].second.y()); // WARNING: narrow from double to float
            }
            coords[i] = std::move(tmp);
        }
    }
    else {
        for(int i{}; i < rows; ++i) {
            QVector<QVector3D> tmp(cols, {-1, -1, -1});
            for(int j{}; j < cols; ++j) {
                tmp[j] = QVector3D(m_grid[i][j].second.x() - m_grid[0][0].second.x(),
                        m_heights[i][j].second > 0. ? m_heights[i][j].second : 0.,
                        m_grid[i][j].second.y() - m_grid[0][0].second.y()); // WARNING: narrow from double to float
            }
            coords[i] = std::move(tmp);
        }
    }

    float xmax{};
    float ymax{};
    float zmax{};
    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(m_grid[i][j].first) {
                xmax = std::max(xmax, coords[i][j].x());
                ymax = std::max(ymax, coords[i][j].y());
                zmax = std::max(zmax, coords[i][j].z());
            }
        }
    }

    m_graph->activeTheme()->setType(QtDataVisualization::Q3DTheme::ThemePrimaryColors);
    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(20);
    m_graph->activeTheme()->setFont(font);

    if(!(m_graph->axes().empty())){ // if axes was already created them must be deleted for next graph
        m_graph->releaseAxis(m_graph->axisX());
        m_graph->releaseAxis(m_graph->axisY());
        m_graph->releaseAxis(m_graph->axisZ());
    }
    setupAxes(xmax, ymax, zmax);
    setupSeries(coords);

    m_graph->show();
}


// Private methods
void Visualization3DObject::setupSeries(const QVector<QVector<QVector3D>> &coords)
{
    auto series{ new QtDataVisualization::QSurface3DSeries(m_graph) }; // WARNING: may throw
    series->setItemLabelFormat(QStringLiteral("@xLabel; @zLabel; @yLabel"));
    series->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurface);
    series->setBaseColor(Qt::blue);
    series->setBaseGradient(m_gr);
    series->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);

    auto array{new QtDataVisualization::QSurfaceDataArray }; // WARNING: may throw
    const auto rows{coords.size()};
    auto cols{ rows > 0 ? coords[0].size() : 0 };
    for(int i{}; i < rows; ++i){
        auto row = new QtDataVisualization::QSurfaceDataRow; // WARNING: may throw
        for(int j{}; j < cols; ++j){
            *row << coords[i][j];
        }
        *array << row;
    }
    series->dataProxy()->resetArray(array); // transfer ownership over the array
    m_graph->addSeries(series); // transfer ownership over the series
}

void Visualization3DObject::setupAxes(double xmax, double ymax, double zmax)
{
    m_graph->setAxisX(new QtDataVisualization::QValue3DAxis); // WARNING: may throw
    m_graph->setAxisY(new QtDataVisualization::QValue3DAxis); // WARNING: may throw
    m_graph->setAxisZ(new QtDataVisualization::QValue3DAxis); // WARNING: may throw
    m_graph->axisX()->setReversed(true);
    m_graph->axisY()->setReversed(true);

    m_graph->axisX()->setLabelFormat(QString("%i м"));
    m_graph->axisY()->setLabelFormat(QString("%i м"));
    m_graph->axisZ()->setLabelFormat(QString("%i м"));

    m_graph->axisX()->setTitle("OX");
    m_graph->axisY()->setTitle("OZ");
    m_graph->axisZ()->setTitle("OY");

    m_graph->axisX()->setTitleVisible(true);
    m_graph->axisY()->setTitleVisible(true);
    m_graph->axisZ()->setTitleVisible(true);

    m_graph->axisX()->setRange(0.f, xmax + 10.f);
    if(ymax < 1.)   m_graph->axisY()->setRange(0.f, 5.f);
    else    m_graph->axisY()->setRange(0.f, ymax);
    m_graph->axisZ()->setRange(0.f, zmax + 10.f);
}
