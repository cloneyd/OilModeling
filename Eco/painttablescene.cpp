#include "painttablescene.hpp"

// Ctors
PaintTableScene::PaintTableScene(QObject *parent) :
    QGraphicsScene(parent),
    m_wo_buffer{},
    m_islands_buffer{},
    m_wo_stash{},
    m_islands_stash{},
    m_last_changes{},
    m_last_changes_stash{}
{
    // PASS
}


// private slots
void PaintTableScene::clear()
{
    m_wo_buffer.clear();
    m_islands_buffer.clear();

    m_wo_stash.clear();
    m_islands_stash.clear();

    m_last_changes.clear();
    m_last_changes_stash.clear();

    QGraphicsScene::clear();
}


// Getters
[[nodiscard]] QVector<QPointF> PaintTableScene::getWaterObjectCoords()
{
    auto buffer_size{ m_wo_buffer.size() };

    QVector<QPointF> area;
    if(buffer_size == 0)    return area;

    int full_size{}; // for one time memoty reserve
    for(int i{}; i < buffer_size; ++i) {
        full_size += m_wo_buffer[i].size();
    }
    area.reserve(full_size);


    for(int i{}; i < buffer_size; ++i) {
        auto size{ m_wo_buffer[i].size() };
        for(int j{}; j < size; ++j) {
            area.append(m_wo_buffer[i][j]);
        }
    }

    return area;
}

[[nodiscard]] QVector<QPointF> PaintTableScene::getIslandsCoords()
{
    auto buffer_size{ m_islands_buffer.size() };

    QVector<QPointF> area;
    if(buffer_size == 0)    return area;

    int full_size{}; // for one time memoty reserve
    for(int i{}; i < buffer_size; ++i) {
        full_size += m_islands_buffer[i].size();
    }
    area.reserve(full_size);


    for(int i{}; i < buffer_size; ++i) {
        auto size{ m_islands_buffer[i].size() };
        for(int j{}; j < size; ++j) {
            area.append(m_islands_buffer[i][j]);
        }
    }

    return area;
}


// Protected overridden functions
void PaintTableScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos{ event->scenePos() };
    QVector<QPointF> new_writes(1);
    new_writes[0] = pos;

    if(auto button{ event->button() }; button == Qt::MouseButton::LeftButton) {
        m_wo_buffer.append(std::move(new_writes));
        addEllipse(pos.x(), pos.y(), line_width, line_width, Qt::NoPen, water_object_color);
        m_last_changes.append(LastChanger::water_object);
    }
    else if(button == Qt::MouseButton::RightButton) {
        m_islands_buffer.append(std::move(new_writes));
        addEllipse(pos.x(), pos.y(), line_width, line_width, Qt::NoPen, islands_color);
        m_last_changes.append(LastChanger::island);
    }
    event->accept();
}

void PaintTableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos{ event->scenePos() };

    auto distance = [](const QPointF &first, const QPointF &second) { return std::sqrt(std::pow((second.x() - first.x()), 2) + std::pow(second.y() - first.y(), 2)); };

    constexpr double length_ratio{ 2. };

    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) {
        auto size{ m_wo_buffer.size() };
        auto last_pos{ m_wo_buffer[size - 1].back() };
        if(auto line_length{ distance(last_pos, pos) }; line_length <= line_width * length_ratio) {
            addLine(last_pos.x(), last_pos.y(), pos.x(), pos.y(), QPen(water_object_color, line_width, Qt::SolidLine, Qt::RoundCap));
            m_wo_buffer[size - 1].append(pos);
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
                m_wo_buffer[size - 1].append(QPointF(cur_x, cur_y));
                addLine(last_x, last_y, cur_x, cur_y, QPen(water_object_color, line_width, Qt::SolidLine, Qt::RoundCap));
                last_x = cur_x;
                last_y = cur_y;
            }
        }

    }
    else if(buttons.testFlag(Qt::MouseButton::RightButton)) {
        auto size{ m_islands_buffer.size() };
        auto last_pos{ m_islands_buffer[size - 1].back() };
        if(auto line_length{ distance(last_pos, pos) }; line_length <= line_width * length_ratio) {
            addLine(last_pos.x(), last_pos.y(), pos.x(), pos.y(), QPen(islands_color, line_width, Qt::SolidLine, Qt::RoundCap));
            m_islands_buffer[size - 1].append(pos);
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
                m_islands_buffer[size - 1].append(QPointF(cur_x, cur_y));
                addLine(last_x, last_y, cur_x, cur_y, QPen(islands_color, line_width, Qt::SolidLine, Qt::RoundCap));
                last_x = cur_x;
                last_y = cur_y;
            }
       }
    }
    event->accept();
}


// public modifiers
void PaintTableScene::hideToStash()
{
    if(m_last_changes.size() == 0)  return;

    auto last_change{ m_last_changes.back() };
    if(last_change== LastChanger::water_object) {
        m_wo_stash.append(std::move(m_wo_buffer.back()));
        m_wo_buffer.removeLast();
    }
    else {
        m_islands_stash.append(std::move(std::move(m_islands_buffer.back())));
        m_islands_buffer.removeLast();
    }

    m_last_changes.removeLast();
    m_last_changes_stash.append(std::move(last_change));
}

void PaintTableScene::getFromStash()
{
    if(m_last_changes_stash.size() == 0)    return;

    auto change{ m_last_changes_stash.back() };
    if(change == LastChanger::water_object) {
        m_wo_buffer.append(std::move(m_wo_stash.back()));
        m_wo_stash.removeLast();
    }
    else {
        m_islands_buffer.append(std::move(m_islands_stash.back()));
        m_islands_stash.removeLast();
    }

    m_last_changes_stash.removeLast();
    m_last_changes.append(std::move(change));
}
