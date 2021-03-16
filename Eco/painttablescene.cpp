#include "painttablescene.hpp"

#include <QMessageBox>
#include <QPainter>

// Ctors
PaintTableScene::PaintTableScene(QObject *parent) :
    QGraphicsScene(parent),
    m_wo_buffer{},
    m_islands_buffer{},
    m_mark_pos_buffer{},
    m_wo_stash{},
    m_islands_stash{},
    m_mark_pos_stash{},
    m_last_changes_log{},
    m_last_changes_log_stash{}
{
    // PASS
}


// public slots
void PaintTableScene::clear()
{
    m_wo_buffer.clear();
    m_islands_buffer.clear();

    m_wo_stash.clear();
    m_islands_stash.clear();

    m_last_changes_log.clear();
    m_last_changes_log_stash.clear();

    m_mark_pos_buffer.clear();
    m_mark_pos_stash.clear();

    emit changeLogChanged(m_last_changes_log.size());
    emit stashedChangeLogChanged(m_last_changes_log_stash.size());

    QGraphicsScene::clear();
}


// Getters
[[nodiscard]] QVector<QPointF> PaintTableScene::getWaterObjectCoords()
{
    if(m_wo_buffer.size() == 0)    return QVector<QPointF>{};

    int full_size{}; // for one time memory allocation
    for(auto&& vector : m_wo_buffer) {
        full_size += vector.size();
    }

    QVector<QPointF> area(full_size);
    int area_index{};
    for(auto&& vector : m_wo_buffer) {
        auto size{ vector.size() };
        for(int j{}; j < size; ++j) {
            area[area_index++] = vector[j];
        }
    }

    return area;
}

[[nodiscard]] QVector<QPointF> PaintTableScene::getIslandsCoords()
{
    if(m_islands_buffer.size() == 0)    return QVector<QPointF>{};

    int full_size{}; // for one time memoty reserve
    for(auto&& vector : m_islands_buffer) {
        full_size += vector.size();
    }

    QVector<QPointF> area(full_size);
    int area_index{};
    for(auto&& vector : m_islands_buffer) {
        auto size{ vector.size() };
        for(int j{}; j < size; ++j) {
            area[area_index++] = vector[j];
        }
    }
    return area;
}

[[nodiscard]] const QPixmap PaintTableScene::getEditedPixmap()
{
    QPixmap pixmap(sceneRect().size().toSize()); // WARNING: may throw; Create the image with the exact size of the shrunk scene

    QPainter painter(&pixmap);
    render(&painter);
    return pixmap;
}


// Protected overridden functions
void PaintTableScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    const auto pos{ event->scenePos() };

    if(!isInSceneRect(pos)) {
        event->ignore();
        return;
    }

    QVector<QPointF> new_writes(1);
    new_writes[0] = pos;

    if(auto button{ event->button() }; button == Qt::MouseButton::LeftButton) {
        m_wo_buffer.push_back(std::move(new_writes));
        addEllipse(pos.x(), pos.y(), line_width, line_width, Qt::NoPen, water_object_color);
        m_last_changes_log.push_back(LogValues::water_object);
    }
    else if(button == Qt::MouseButton::RightButton) {
        m_islands_buffer.push_back(std::move(new_writes));
        addEllipse(pos.x(), pos.y(), line_width, line_width, Qt::NoPen, islands_color);
        m_last_changes_log.push_back(LogValues::island);
    }

    emit changeLogChanged(m_last_changes_log.size());
    event->accept();
}

void PaintTableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    const auto pos{ event->scenePos() };

    if(!isInSceneRect(pos)) {
        event->ignore();
        return;
    }

    auto distance = [](const QPointF &first, const QPointF &second) { return std::sqrt(std::pow((second.x() - first.x()), 2) + std::pow(second.y() - first.y(), 2)); };

    constexpr double length_ratio{ 2. };

    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) { // left button always will have priority
        auto last_pos{ m_wo_buffer.back().back() };
        if(auto line_length{ distance(last_pos, pos) }; line_length <= line_width * length_ratio) {
            addLine(last_pos.x(), last_pos.y(), pos.x(), pos.y(), QPen(water_object_color, line_width, Qt::SolidLine, Qt::RoundCap));
            m_wo_buffer.back().append(pos);
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
                m_wo_buffer.back().append(QPointF(cur_x, cur_y));
                addLine(last_x, last_y, cur_x, cur_y, QPen(water_object_color, line_width, Qt::SolidLine, Qt::RoundCap));
                last_x = cur_x;
                last_y = cur_y;
            }
        }

    }
    else if(buttons.testFlag(Qt::MouseButton::RightButton)) {
        auto last_pos{ m_islands_buffer.back().back() };
        if(auto line_length{ distance(last_pos, pos) }; line_length <= line_width * length_ratio) {
            addLine(last_pos.x(), last_pos.y(), pos.x(), pos.y(), QPen(islands_color, line_width, Qt::SolidLine, Qt::RoundCap));
            m_islands_buffer.back().append(pos);
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
                m_islands_buffer.back().append(QPointF(cur_x, cur_y));
                addLine(last_x, last_y, cur_x, cur_y, QPen(islands_color, line_width, Qt::SolidLine, Qt::RoundCap));
                last_x = cur_x;
                last_y = cur_y;
            }
       }
    }
    event->accept();
}

void PaintTableScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) {
        auto pos{ event->scenePos() };

        if(!isInSceneRect(pos)) {
            event->ignore();
            return;
        }

        m_mark_pos_buffer.push_back(pos);
        m_last_changes_log.push_back(LogValues::mark);
        m_wo_buffer.pop_back();
        emit markPositionChanged(m_mark_pos_buffer);
        emit changeLogChanged(m_last_changes_log.size());
        event->accept();
    }

    event->ignore();
}


// public modifiers
void PaintTableScene::hideToStash()
{
    if(m_last_changes_log.size() == 0)  return;

    auto last_change{ m_last_changes_log.back() };
    switch (last_change) {
    case LogValues::water_object:
        m_wo_stash.push_back(std::move(m_wo_buffer.back()));
        m_wo_buffer.pop_back();
        break;

    case LogValues::island:
        m_islands_stash.push_back(std::move(std::move(m_islands_buffer.back())));
        m_islands_buffer.pop_back();
        break;

    case LogValues::mark:
        m_mark_pos_stash.push_back(m_mark_pos_buffer.back());
        m_mark_pos_buffer.pop_back();
        break;
    }

    m_last_changes_log.pop_back();
    m_last_changes_log_stash.push_back(std::move(last_change));

    emit stashedChangeLogChanged(m_last_changes_log_stash.size());
    emit changeLogChanged(m_last_changes_log.size());
}

void PaintTableScene::getFromStash()
{
    if(m_last_changes_log_stash.size() == 0)    return;

    auto change{ m_last_changes_log_stash.back() };
    switch (change) {
    case LogValues::water_object:
        m_wo_buffer.push_back(std::move(m_wo_stash.back()));
        m_wo_stash.pop_back();
        break;

    case LogValues::island:
        m_islands_buffer.push_back(std::move(m_islands_stash.back()));
        m_islands_stash.pop_back();
        break;

    case LogValues::mark:
        m_mark_pos_buffer.push_back(m_mark_pos_stash.back());
        m_mark_pos_stash.pop_back();
        break;
    }

    m_last_changes_log_stash.pop_back();
    m_last_changes_log.push_back(std::move(change));

    emit stashedChangeLogChanged(m_last_changes_log_stash.size());
    emit changeLogChanged(m_last_changes_log.size());
}

QPixmap PaintTableScene::paintContentOnMap(const QPixmap &where, PaintStyle style) const
{
    auto map{ where };
    QPainter painter(&map);

    if(auto wo_size{ m_wo_buffer.size() }; wo_size != 0) {
        switch(style) {
        case PaintStyle::lines:
            painter.setPen(QPen(water_object_color, line_width));
            for(auto&& vector : m_wo_buffer) {
                const auto vec_size{ vector.size() };
                if(vec_size == 0) continue;

                painter.drawEllipse(vector[0].x(), vector[0].y(), 0., 0.);
                for(int i{ 1 }; i < vec_size; ++i) {
                    painter.drawLine(QLineF{ vector[i - 1], vector[i] });
                }
            }

            painter.setPen(QPen(islands_color, line_width));
            for(auto&& vector : m_islands_buffer) {
                const auto vec_size{ vector.size() };
                if(vec_size == 0) continue;

                painter.drawEllipse(vector[0].x(), vector[0].y(), 0., 0.);
                for(int i{ 1 }; i < vec_size; ++i) {
                    painter.drawLine(QLineF{ vector[i - 1], vector[i] });
                }
            }
            break;

        case PaintStyle::ellipse:
            painter.setPen(Qt::NoPen);
            painter.setBrush(water_object_color);
            for(auto&& vector : m_wo_buffer) {
                const auto vec_size{ vector.size() };
                if(vec_size == 0) continue;

                for(int i{}; i < vec_size; ++i) {
                    painter.drawEllipse(vector[i].x(), vector[i].y(), line_width, line_width);
                }
            }

            painter.setBrush(islands_color);
            for(auto&& vector : m_islands_buffer) {
                const auto vec_size{ vector.size() };
                if(vec_size == 0) continue;

                for(int i{}; i < vec_size; ++i) {
                    painter.drawEllipse(vector[i].x(), vector[i].y(), line_width, line_width);
                }
            }
            break;
        }
    }
    // TODO:

    for(auto&& mark : m_mark_pos_buffer) {
        painter.drawImage(QPointF{ mark.x() - 10., mark.y() - 20. }, QImage(mark_icon_filepath).scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
    return map;
}

void PaintTableScene::resetStashes()
{
    m_wo_stash.clear();
    m_islands_stash.clear();
    m_mark_pos_stash.clear();
    m_last_changes_log_stash.clear();
    emit stashedChangeLogChanged(m_last_changes_log_stash.size());
}


// private helpers
bool PaintTableScene::isInSceneRect(const QPointF &pos) const
{
    const auto scene_rect{ sceneRect() };

    if(pos.x() < scene_rect.x() || pos.x() > scene_rect.x() + scene_rect.width() || // if out of bounding
       pos.y() < scene_rect.y() || pos.y() > scene_rect.y() + scene_rect.width()) {
        return false;
    }
    return true;
}
