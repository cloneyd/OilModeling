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
        addEllipse(pos.x(), pos.y(), line_width, line_width, Qt::NoPen, water_object_color);
    }
    else if(button == Qt::MouseButton::RightButton) {
        m_island_area.append(pos);
        addEllipse(pos.x(), pos.y(), line_width, line_width, Qt::NoPen, islands_color);
    }
    event->accept();
}

void PaintTableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos{ event->scenePos() };

    auto distance = [](const QPointF &first, const QPointF &second) { return std::sqrt(std::pow((second.x() - first.x()), 2) + std::pow(second.y() - first.y(), 2)); };

    constexpr double length_ratio{ 2. };

    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) {
        auto last_pos{ m_water_area.back() };
        if(auto line_length{ distance(last_pos, pos) }; line_length <= line_width * length_ratio) {
            addLine(last_pos.x(), last_pos.y(), pos.x(), pos.y(), QPen(water_object_color, line_width, Qt::SolidLine, Qt::RoundCap));
            m_water_area.append(pos);
        }
        else {
            const auto xline_coord{ pos.x() - last_pos.x() };
            const auto yline_coord{ pos.y() - last_pos.y() };
            const auto xcos{ xline_coord / line_length };
            const auto ycos{ yline_coord / line_length };

            double cur_x{ last_pos.x() };
            double cur_y{ last_pos.y() };
            double last_x{ cur_x };
            double last_y{ cur_y };

            while(distance(QPointF(cur_x += length_ratio * line_width * xcos, cur_y += length_ratio * line_width * ycos), pos) > line_width * length_ratio) {
                m_water_area.append(QPointF(cur_x, cur_y));
                addLine(last_x, last_y, cur_x, cur_y, QPen(water_object_color, line_width, Qt::SolidLine, Qt::RoundCap));
                last_x = cur_x;
                last_y = cur_y;
            }
        }

    }
    else if(buttons.testFlag(Qt::MouseButton::RightButton)) {
        auto last_pos{ m_island_area.back() };
        if(auto line_length{ distance(last_pos, pos) }; line_length <= line_width * length_ratio) {
            addLine(last_pos.x(), last_pos.y(), pos.x(), pos.y(), QPen(islands_color, line_width, Qt::SolidLine, Qt::RoundCap));
            m_island_area.append(pos);
        }
        else {
            const auto xline_coord{ pos.x() - last_pos.x() };
            const auto yline_coord{ pos.y() - last_pos.y() };
            const auto xcos{ xline_coord / line_length };
            const auto ycos{ yline_coord / line_length };

            double cur_x{ last_pos.x() };
            double cur_y{ last_pos.y() };
            double last_x{ cur_x };
            double last_y{ cur_y };

            while(distance(QPointF(cur_x += length_ratio * line_width * xcos, cur_y += length_ratio * line_width * ycos), pos) > line_width * length_ratio) {
                m_island_area.append(QPointF(cur_x, cur_y));
                addLine(last_x, last_y, cur_x, cur_y, QPen(islands_color, line_width, Qt::SolidLine, Qt::RoundCap));
                last_x = cur_x;
                last_y = cur_y;
            }
       }
    }
    event->accept();
}
