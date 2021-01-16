#include "painttablescene.hpp"

// Ctors
PaintTableScene::PaintTableScene(QObject *parent) :
    QGraphicsScene(parent),
    m_area_points{}
{
    // PASS
}


// private slots
void PaintTableScene::clear()
{
    m_area_points.clear();
    QGraphicsScene::clear();
}


// Public getters
[[nodiscard]] const QVector<QPointF>& PaintTableScene::getAreaPoints() const noexcept
{
    return m_area_points;
}

// Public member access methods
[[nodiscard]] QVector<QPointF>&& PaintTableScene::releaseAreaPoints() noexcept
{
    return std::move(m_area_points);
}


// Protected overridden functions
void PaintTableScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos{ event->scenePos() };
    m_area_points.append(pos);
    addEllipse(pos.x(), pos.y(), 3, 3, Qt::NoPen, Qt::red);
}

void PaintTableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos{ event->scenePos() };
    auto prev_point{ m_area_points.back() };
    addLine(prev_point.x(), prev_point.y(), pos.x(), pos.y(), QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
    m_area_points.append(pos);
}
