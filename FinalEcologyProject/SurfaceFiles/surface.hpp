#ifndef SURFACE_HPP
#define SURFACE_HPP
#include <QObject>
#include <Q3DSurface>
#include <QSurface3DSeries>
#include <QValue3DAxis>
#include <QPixmap>
#include <QVector3D>
#include <QLinearGradient>

#include "HelperEntities/pch.hpp"

class Surface: public QObject
{
    Q_OBJECT

private:
    QVector<QVector<QPair<bool, QPointF>>> m_grid; // contains the coorinats of left upper corner in real mertres
    QVector<QVector<QPair<bool, double>>> m_heights;
    QtDataVisualization::Q3DSurface *m_graph;
    double m_realscale;
    QLinearGradient m_gr;

public:
    explicit Surface(QtDataVisualization::Q3DSurface *graph);
    ~Surface() noexcept;

// Setters
public:
    void setGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid) /*noexcept*/;
    void setHeights(const QVector<QVector<QPair<bool, double>>> &heights) /*noexcept*/;
    void setScale(double scale) noexcept;

// Getters
public:
    [[nodiscard]] inline const QVector<QVector<QPair<bool, QPointF>>>& getGrid() const noexcept { return m_grid; }
    [[nodiscard]] inline const QVector<QVector<QPair<bool, double>>>& getHeights() const noexcept { return m_heights; }
    [[nodiscard]] QPixmap getGradientPixmap() const;

// Methods
public:
    void updateMap();

// Helper functions
private:
    void setupSeries(const QVector<QVector<QVector3D>> &coords);
    void setupAxes(double xmax, double ymax, double zmax);
};

#endif // SURFACE_HPP
