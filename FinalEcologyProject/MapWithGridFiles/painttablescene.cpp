#include "painttablescene.hpp"

// Ctors
PaintTableScene::PaintTableScene(QObject *parent) :
    QGraphicsScene(parent),
    m_water_area{},
    m_island_area{}
{
    // PASS
}


// private slots
void PaintTableScene::clear()
{
    m_water_area.clear();
    m_island_area.clear();
    QGraphicsScene::clear();
}


// Protected overridden functions
void PaintTableScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos{ event->scenePos() };
    if(auto button{ event->button() }; button == Qt::MouseButton::LeftButton) {
        m_water_area.append(pos);
        addEllipse(pos.x(), pos.y(), 3, 3, Qt::NoPen, Qt::cyan);
    }
    else if(button == Qt::MouseButton::RightButton) {
        m_island_area.append(pos);
        addEllipse(pos.x(), pos.y(), 3, 3, Qt::NoPen, Qt::red);
    }
    event->accept();
}

void PaintTableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos{ event->scenePos() };
    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) {
        addLine(m_water_area.back().x(), m_water_area.back().y(), pos.x(), pos.y(), QPen(Qt::cyan, 3, Qt::SolidLine, Qt::RoundCap));
        m_water_area.append(pos);
    }
    else if(buttons.testFlag(Qt::MouseButton::RightButton)) {
        addLine(m_island_area.back().x(), m_island_area.back().y(), pos.x(), pos.y(), QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
        m_island_area.append(pos);
    }
    event->accept();
}
