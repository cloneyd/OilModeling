#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP
// Qt
#include <QObject>
#include <QLinearGradient>
#include <Q3DSurface>

// STL
#include <memory>

// current project
#include "object3d_utilities.hpp"
#include <GridHandlerFiles/grid_handler_utilities.hpp>

class Object3D : public QObject
{
    Q_OBJECT

private: // data
    const GridType *m_pixgrid_ptr; // pointer to pixel grid (which must be contained in GridHandler; aggregate acquisition, nullptr by default
    DepthType m_depth; // store a depth in real meters
    QLinearGradient m_gr; // depth gradient
    std::unique_ptr<QtDataVisualization::Q3DSurface> m_graph; // 3d object

public:
    Object3D(QObject *parent = nullptr);
    Object3D(QtDataVisualization::Q3DSurface *graph, QObject *parent = nullptr); // TAKES OWNERSHIP on graph

// setters
public:
    inline void setGridPtr(const GridType *pixgrid_ptr) noexcept { m_pixgrid_ptr = pixgrid_ptr; }
    inline void setDepth(DepthType &&depth) noexcept { m_depth = std::move(depth); } // TAKES OWNERSHIP
    inline void resetGraph(QtDataVisualization::Q3DSurface *graph = nullptr) { m_graph.reset(graph); } // TAKES OWNERSHIP on graph

// getters
public:
    [[nodiscard]] GridType getRealMetersGrid() const;
    [[nodiscard]] inline const DepthType& getDepth() const noexcept { return m_depth; }
    [[nodiscard]] QPixmap getGradientPixmap() const;

// modifiers
public:
    void repaint();
    inline void show() { m_graph->show(); }

// helpers
private:
    void setupSeries(const QVector<QVector<QVector3D>> &coords);
    void setupAxes(float xmax, float ymax, float zmax);
};

#endif // OBJECT3D_HPP
