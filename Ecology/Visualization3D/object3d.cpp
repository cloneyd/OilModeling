// QT
#include <QPainter>

// current project
#include "object3d.hpp"

Object3D::Object3D(QObject *parent) :
    QObject(parent),
    m_pixgrid_ptr{},
    m_depth{},
    m_gr(0, 0, 1, 480), // a bit magic
    m_graph{}
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

Object3D::Object3D(QtDataVisualization::Q3DSurface *graph, QObject *parent) :
    Object3D(parent)
{
    m_graph.reset(graph);
}


// getters
[[nodiscard]] GridType Object3D::getRealMetersGrid() const
{
    const auto nrows{ m_pixgrid_ptr->size() };
    if(nrows == 0)  return {};
    const auto ncols{ (*m_pixgrid_ptr)[0].size() };
    if(ncols == 0)  return {};

    GridType grid(nrows, QVector<QPair<bool, QPointF>>(ncols));
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            grid[i][j].first = (*m_pixgrid_ptr)[i][j].first;
            grid[i][j].second = { toMeters((*m_pixgrid_ptr)[i][j].second.x()), toMeters((*m_pixgrid_ptr)[i][j].second.y()) };
        }
    }

    return grid;
}

[[nodiscard]] QPixmap Object3D::getGradientPixmap() const
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

    double max_depth{};
    if(m_depth.empty()) {
        max_depth = 100.;
    }
    else {
        auto nrows(m_depth.size());
        auto ncols{ m_depth[0].size() };
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                if(m_depth[i][j].first) {
                    max_depth = std::max(max_depth, m_depth[i][j].second);
                }
            }
        }
    }
    const double pieces {max_depth / ncolors}; // distance between pieces
    double step = (height - 2. * border) / ncolors;
    for (std::uint8_t i{}; i <= ncolors; ++i) {
        const std::uint16_t yPos{static_cast<const std::uint16_t>(i * step + border)};
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 м").arg(max_depth - (i * pieces)));
    }

    return pm;
}


// public modifiers
void Object3D::repaint()
{
    if(auto series{ m_graph->seriesList() }; !(series.empty())) m_graph->removeSeries(series.at(0)); // if m_graph have old series, it must be deleted
    if(m_pixgrid_ptr->empty())   return; // if there is no new grid

    auto nrows { m_pixgrid_ptr->size() };
    auto ncols{ (*m_pixgrid_ptr)[0].size() };
    if(ncols == 0)  return;

    QVector<QVector<QVector3D>> coords(nrows, QVector<QVector3D>(ncols));
    // Note: Q3DVisualization3DObject standart axis a bit confusing: Y axe is the height axe
    if(m_depth.empty()) {
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                // WARNING: implicit narrow convertions; normalize to zero
                coords[i][j] = QVector3D(toMeters((*m_pixgrid_ptr)[i][j].second.x()) - toMeters((*m_pixgrid_ptr)[0][0].second.x()),
                                         0.,
                                         toMeters((*m_pixgrid_ptr)[i][j].second.y()) - toMeters((*m_pixgrid_ptr)[0][0].second.y()));
            }
        }
    }
    else {
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                // WARNING: implicit narrow convertions
                coords[i][j] = QVector3D(toMeters((*m_pixgrid_ptr)[i][j].second.x()) - toMeters((*m_pixgrid_ptr)[0][0].second.x()),
                                         m_depth[i][j].second > 0. ? m_depth[i][j].second : 0.f,
                                         toMeters((*m_pixgrid_ptr)[i][j].second.y()) - toMeters((*m_pixgrid_ptr)[0][0].second.y()));
            }
        }
    }

    // looking for maximum to apply it to axes
    float xmax{ coords[0][0].x() };
    float ymax{ coords[0][0].y() };
    float zmax{ coords[0][0].z() };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_pixgrid_ptr)[i][j].first) {
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

    if(!(m_graph->axes().empty())){ // if axes was already created them must be deleted
        m_graph->releaseAxis(m_graph->axisX());
        m_graph->releaseAxis(m_graph->axisY());
        m_graph->releaseAxis(m_graph->axisZ());
    }
    setupAxes(xmax, ymax, zmax);
    setupSeries(coords);
}


// private functions
void Object3D::setupSeries(const QVector<QVector<QVector3D>> &coords)
{
    auto series{ new QtDataVisualization::QSurface3DSeries(m_graph.get()) }; // WARNING: may throw
    series->setItemLabelFormat(QStringLiteral("@xLabel; @zLabel; @yLabel"));
    series->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurface);
    series->setBaseColor(Qt::blue);
    series->setBaseGradient(m_gr);
    series->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);

    auto array{new QtDataVisualization::QSurfaceDataArray }; // WARNING: may throw
    const auto nrows{ coords.size() };
    auto ncols{ coords[0].size() };
    for(int i{}; i < nrows; ++i){
        auto row = new QtDataVisualization::QSurfaceDataRow; // WARNING: may throw
        for(int j{}; j < ncols; ++j){
            *row << coords[i][j];
        }
        *array << row;
    }
    series->dataProxy()->resetArray(array); // transfer ownership over the array
    m_graph->addSeries(series); // transfer ownership over the series
}

void Object3D::setupAxes(float xmax, float ymax, float zmax)
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
