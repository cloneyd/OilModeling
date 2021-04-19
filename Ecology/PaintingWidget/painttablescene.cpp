// QT
#include <QPainter>

// STL
#include <cmath>

// current project
#include "painttablescene.hpp"

PaintTableScene::PaintTableScene(QObject *parent) :
    QGraphicsScene(parent),
    m_wo_buffer{},
    m_islands_buffer{},
    m_sources_marks_buffer{},
    m_stashed_wo{},
    m_stashed_islands{},
    m_stashed_sources_marks{},
    m_icon{}
{
    Q_ASSERT_X(m_icon.load(s_mark_icon_filepath),
               "Class - PaintTableScene", "Function - Constructor, problem - null mark pixmap");
}


// Public getters
[[nodiscard]] QVector<QPointF> PaintTableScene::getWaterObjectPoints() const
{
    // NOTE: cause there are no guarantee that WoBufType and IslandBufType will be same, this functions must have own realization
    int result_size{};
    for(auto&& vec : m_wo_buffer) {
        result_size += vec.size();
    }

    QVector<QPointF> wo_area;
    wo_area.reserve(result_size);

    for(auto &&deque : m_wo_buffer) {
        for(auto &&point : deque) {
            wo_area.push_back(point);
        }
    }

    return wo_area;
}

[[nodiscard]] QVector<QPointF> PaintTableScene::getIslandsPoints() const
{
    // NOTE: cause there are no guarantee that WoBufType and IslandBufType will be same, this functions must have own realization
    int result_size{};
    for(auto&& vec : m_islands_buffer) {
        result_size += vec.size();
    }

    QVector<QPointF> islands_area;
    islands_area.reserve(result_size);

    for(auto &&deque : m_islands_buffer) {
        for(auto &&point : deque) {
            islands_area.push_back(point);
        }
    }

    return islands_area;
}


// Protected overridden functions
void PaintTableScene::mousePressEvent(QGraphicsSceneMouseEvent *event) /*override*/
{
    std::deque<QPointF> new_pos{ event->scenePos() }; // pix coordinate

    if(!isInSceneRect(new_pos.front())) {
        event->ignore();
        return;
    }

    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) {
        addEllipse(new_pos.front().x(),
                   new_pos.front().y(),
                   PaintTableSceneConstants::s_line_width,
                   PaintTableSceneConstants::s_line_width,
                   Qt::NoPen,
                   s_wo_color);
        m_wo_buffer.push_back(std::move(new_pos));
        emit woChanged(ChangeType::Buffering);
    }
    else if( buttons.testFlag(Qt::MouseButton::RightButton)) {
        addEllipse(new_pos.front().x(),
                   new_pos.front().y(),
                   PaintTableSceneConstants::s_line_width,
                   PaintTableSceneConstants::s_line_width,
                   Qt::NoPen,
                   s_island_color);
        m_islands_buffer.push_back(std::move(new_pos));
        emit islandChanged(ChangeType::Buffering);
    }
    else { // no reaction is needed
        event->ignore();
        return;
    }

    event->accept();
}

void PaintTableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) /*override*/
{
    const auto pos{ event->scenePos() }; // pix coordinate
    if(!isInSceneRect(pos)) {
        event->ignore();
        return;
    }

    auto distance = [](const QPointF &begin, const QPointF &end) -> double {
        return std::sqrt(std::pow((end.x() - begin.x()), 2) + std::pow(end.y() - begin.y(), 2));
    };

    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) {
        const auto last_pos{ m_wo_buffer.back().back() };
        if(distance(last_pos, pos) <= PaintTableSceneConstants::s_line_width * PaintTableSceneConstants::s_length_ratio) {
            addLine(QLineF(last_pos, pos), QPen(s_wo_color, PaintTableSceneConstants::s_line_width, Qt::SolidLine, Qt::RoundCap));
            m_wo_buffer.back().push_back(std::move(pos));
        }
        else {
            connectPoints(last_pos, pos, s_wo_color, m_wo_buffer.back());
        }
    }
    else if(buttons.testFlag(Qt::MouseButton::RightButton)) {
        const auto last_pos{ m_islands_buffer.back().back() };
        if(distance(last_pos, pos) <= PaintTableSceneConstants::s_line_width) {
            addLine(QLineF(last_pos, pos), QPen(s_island_color, PaintTableSceneConstants::s_line_width, Qt::SolidLine, Qt::RoundCap));
            m_islands_buffer.back().push_back(std::move(pos));
        }
        else {
            connectPoints(last_pos, pos, s_island_color, m_islands_buffer.back());
        }
    }
    else {
        event->ignore();
        return;
    }

    event->accept();
}

void PaintTableScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) /*override*/
{
    if(m_sources_marks_buffer.isEmpty()) return; // do nothing if there is no sources

    auto pos{ event->scenePos() };
    if(!isInSceneRect(pos)) {
        event->ignore();
        return;
    }

    int index{};
    emit getCurrentSourceIndex(index); // WARNING: index changed there
    Q_ASSERT_X(index < m_sources_marks_buffer.size(),
               "Class - PaintTableScene", "function - mouseDoubleClicked, problem - source index out of range");

    if(auto buttons{ event->buttons() }; buttons.testFlag(Qt::MouseButton::LeftButton)) {
        if(m_wo_buffer.back().front() == pos && m_wo_buffer.back().size() == 1) { // if point was added cause bad double click
            m_wo_buffer.pop_back(); // deleting last change
            emit woChanged(ChangeType::Deleted);
        }
        m_sources_marks_buffer[index].append(std::move(pos));

        emit sourcesMarksChanged(ChangeType::Buffering, m_sources_marks_buffer[index].back());
        event->accept();
        return;
    }

    event->ignore();
}


//redefined functions
void PaintTableScene::clear()
{
    m_wo_buffer.clear();
    m_islands_buffer.clear();
    m_sources_marks_buffer.clear();

    clearStashes();

    QGraphicsScene::clear();
}


// Public modifiers
void PaintTableScene::clearStashes() /*noexcept*/ // NOT EMITTING
{
    m_stashed_wo.clear();
    m_stashed_islands.clear();
    m_stashed_sources_marks.clear();
}


// public helpers
[[nodiscard]] QPixmap PaintTableScene::paintContent(const QPixmap &pm, PaintStyle style) const
{
    auto pixmap{ pm }; // copy
    QPainter painter(&pixmap);

    if(auto wo_size{ m_wo_buffer.size() }; wo_size != 0) {
        switch(style) {
        case PaintStyle::Lines:
            painter.setPen(QPen(s_wo_color, PaintTableSceneConstants::s_line_width));
            for(auto&& container : m_wo_buffer) {
                const auto npoints{ container.size() };
                if(npoints == 0) continue;

                painter.drawEllipse(container[0].x(), container[0].y(), 0., 0.);
                for(std::size_t i{ 1 }; i < npoints; ++i) {
                    painter.drawLine(QLineF{ container[i - 1], container[i] });
                }
            }

            painter.setPen(QPen(s_island_color, PaintTableSceneConstants::s_line_width));
            for(auto&& container : m_islands_buffer) {
                const auto npoints{ container.size() };
                if(npoints == 0) continue;

                painter.drawEllipse(container[0].x(), container[0].y(), 0., 0.);
                for(std::size_t i{ 1 }; i < npoints; ++i) {
                    painter.drawLine(QLineF{ container[i - 1], container[i] });
                }
            }
            break;

        case PaintStyle::Ellipse:
            painter.setPen(Qt::NoPen);
            painter.setBrush(s_wo_color);
            for(auto&& container : m_wo_buffer) {
                const auto npoints{ container.size() };
                if(npoints == 0) continue;

                for(std::size_t i{}; i < npoints; ++i) {
                    painter.drawEllipse(container[i].x(), container[i].y(), PaintTableSceneConstants::s_line_width, PaintTableSceneConstants::s_line_width);
                }
            }

            painter.setBrush(s_island_color);
            for(auto&& container : m_islands_buffer) {
                const auto npoints{ container.size() };
                if(npoints == 0) continue;

                for(std::size_t i{}; i < npoints; ++i) {
                    painter.drawEllipse(container[i].x(), container[i].y(), PaintTableSceneConstants::s_line_width, PaintTableSceneConstants::s_line_width);
                }
            }
            break;
        }
    }

    auto icon{ m_icon.scaled(20, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation) };
    int source_index{};
    for(auto &&vectors : m_sources_marks_buffer) {
        if(vectors.isEmpty()) continue;

        SourceType type{};
        emit getSourceType(source_index, type);
        if(type == SourceType::PointSource) {
            painter.drawPixmap(QPointF{ vectors.back().x() - 10., vectors.back().y() - 20. }, icon);
        }
        else {
            for(auto &&mark : vectors) {
                painter.drawPixmap(QPointF{ mark.x() - 10., mark.y() - 20. }, icon);
            }
        }
        ++source_index;
    }
    return pixmap;
}

void PaintTableScene::saveState(QTextStream &stream, const char delim)
{
    auto writeToFile = [&stream](const auto &container, const char obj_delim) {
        stream << container.size() << obj_delim;
        for(const auto &cont : container) {
            stream << cont.size() << obj_delim;
            for(const auto &point : cont) {
                stream << point.x() << '\t' << point.y() << '\t';
            }
        }
        stream << obj_delim; // control delim
    };
    writeToFile(m_wo_buffer, delim);
    writeToFile(m_islands_buffer, delim);
    writeToFile(m_sources_marks_buffer, delim);
    writeToFile(m_stashed_wo, delim);
    writeToFile(m_stashed_islands, delim);

    stream << m_stashed_sources_marks.size() << delim;
    for(const auto &point : m_stashed_sources_marks) {
        stream << point.x() << '\t' << point.y() << '\t';
    }
    stream << delim; // control delim
}

void PaintTableScene::restoreState(QTextStream &stream, const char delim)
{
    auto readUntilDelim = [&stream](const char delim) -> QString {
        QString result{};
        char sym{};
        for(stream >> sym; sym != delim; stream >> sym) {
            result += sym;
        }
        return result;
    };

    auto readFromFile = [&readUntilDelim, &stream](auto &container, const char obj_delim) {
        bool is_converted{};
        const auto container_size{ readUntilDelim(obj_delim).toInt(&is_converted) };
        Q_ASSERT(is_converted);
        container.resize(container_size);

        for(auto &cont : container) {
            const auto cont_size{ readUntilDelim(obj_delim).toInt(&is_converted) };
            Q_ASSERT(is_converted);
            cont.resize(cont_size);
            for(auto &point : cont) {
                const auto x{ readUntilDelim('\t').toDouble(&is_converted) };
                Q_ASSERT(is_converted);
                point.setX(x);

                const auto y{ readUntilDelim('\t').toDouble(&is_converted) };
                Q_ASSERT(is_converted);
                point.setY(y);
            }
        }
        char ctrl_delim{};
        stream >> ctrl_delim;
        Q_ASSERT(ctrl_delim == obj_delim);
    };

    readFromFile(m_wo_buffer, delim);
    readFromFile(m_islands_buffer, delim);
    readFromFile(m_sources_marks_buffer, delim);
    readFromFile(m_stashed_wo, delim);
    readFromFile(m_stashed_islands, delim);

    bool is_converted{};
    const auto m_stashed_marks_size{ readUntilDelim(delim).toInt(&is_converted) };
    Q_ASSERT(is_converted);
    m_stashed_sources_marks.resize(m_stashed_marks_size);
    for(auto &point : m_stashed_sources_marks) {
        const auto x{ readUntilDelim('\t').toDouble(&is_converted) };
        Q_ASSERT(is_converted);
        point.setX(x);

        const auto y{ readUntilDelim('\t').toDouble(&is_converted) };
        Q_ASSERT(is_converted);
        point.setY(y);
    }

    char ctrl_delim{};
    stream >> ctrl_delim;
    Q_ASSERT(ctrl_delim == delim);
}


// private helpers
[[nodiscard]] bool PaintTableScene::isInSceneRect(const QPointF &pos) const
{
    const auto scene_rect{ sceneRect() };

    if(pos.x() < scene_rect.x() || pos.x() > scene_rect.x() + scene_rect.width() || // if out of bounding
       pos.y() < scene_rect.y() || pos.y() > scene_rect.y() + scene_rect.width()) {
        return false;
    }
    return true;
}

// angles
void PaintTableScene::connectPoints(const QPointF &first, const QPointF &second, const QColor &color, std::deque<QPointF> &where)
{
    auto distance = [](const QPointF &begin, const QPointF &end) -> double {
        return std::sqrt(std::pow((end.x() - begin.x()), 2) + std::pow(end.y() - begin.y(), 2));
    };

    const auto line_length(distance(first, second));
    const auto xline_coord{ second.x() - first.x() };
    const auto yline_coord{ second.y() - first.y() };
    const auto xcos{ xline_coord / line_length };
    const auto ycos{ yline_coord / line_length };

    auto cur_x{ first.x() };
    auto cur_y{ first.y() };
    auto last_x{ cur_x };
    auto last_y{ cur_y };

    auto step{ PaintTableSceneConstants::s_line_width * PaintTableSceneConstants::s_length_ratio };
    while(distance(QPointF(cur_x += step * xcos, cur_y += step * ycos), second) > step) {
        where.push_back({ cur_x, cur_y });
        addLine(last_x, last_y, cur_x, cur_y, QPen(color, PaintTableSceneConstants::s_line_width, Qt::SolidLine, Qt::RoundCap));
        last_x = cur_x;
        last_y = cur_y;
    }
}
