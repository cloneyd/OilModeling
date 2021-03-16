#ifndef PAINTTABLESCENE_HPP
#define PAINTTABLESCENE_HPP
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPointF>

#include <list>

#include "pollution_widget_utilities.hpp"

enum class PaintStyle : unsigned char
{
    MIN,
    ellipse = MIN,
    lines, // staring from ellipse
    MAX = lines
};

class PaintTableScene: public QGraphicsScene
{
    Q_OBJECT

    enum class LogValues: unsigned char // enum which contains who added last change to the table
    {
        MIN,
        water_object = MIN,
        island,
        mark,
        MAX = mark
    };

public:
    static constexpr auto line_width{ 3. };
    static inline auto water_object_color{ QColor(0x0338EF)};
    static inline auto islands_color{ QColor(0x9F6342) };
    static constexpr auto mark_icon_filepath{ ":/imgs/images/location.svg" }; // filepath to mark icon}

private:
    std::list<QVector<QPointF>> m_wo_buffer; // buffer for temporary water object drawn sruff
    std::list<QVector<QPointF>> m_islands_buffer; // buffer for a temporary island drawn stuff
    QVector<QVector<QPointF>> m_mark_pos_buffer; // the mark position; {-1., -1.} be default

    std::list<QVector<QPointF>> m_wo_stash; // buffer for a currently unused things
    std::list<QVector<QPointF>> m_islands_stash; // buffer for a currently unused things
    std::list<QVector<QPointF>> m_mark_pos_stash; // the last mark position; {-1., -1.} be default

    std::list<LogValues> m_last_changes_log; // contains the log of changes
    std::list<LogValues> m_last_changes_log_stash; // contains the stash logs

public:
    explicit PaintTableScene(QObject *parent = nullptr);

public slots:
    // redefines base clear() function
    void clear();

signals:
    void stashedChangeLogChanged(int number_of_writes);
    void changeLogChanged(int number_of_writes);
    void markPositionChanged(const QPointF &newpos);

    void getCurrentSourceIndex(int &will_be_index);
    void getCurrentSourceType(SourceType &type);

// Getters
public:
    [[nodiscard]] QVector<QPointF> getWaterObjectCoords();
    [[nodiscard]] QVector<QPointF> getIslandsCoords();

    [[nodiscard]] inline int getNumberOfChanges() const { return m_last_changes_log.size(); }
    [[nodiscard]] inline int getNumberOfStashedChanges() const { return m_last_changes_log_stash.size(); }
    [[nodiscard]] const QPixmap getEdittedPixmap();
    [[nodiscard]] inline const QVector<QVector<QPointF>>& getMarks() const noexcept { return m_mark_pos_buffer; }

// Overridden functions
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

// Modifiers
public:
    void hideToStash();
    void getFromStash();
    void resetStashes();
    inline void deleteLastMark(int source_index) { m_mark_pos_buffer[source_index].pop_back(); }

    inline void insertSource(int index) { m_mark_pos_buffer.insert(index, QVector<QPointF>{}); }
    inline void insertSource(int index, const QPointF &pos) { m_mark_pos_buffer.insert(index, QVector<QPointF>{ pos }); }
    inline void deleteSource(int source_index) { m_mark_pos_buffer.remove(source_index); }
    void updateSource(int index, SourceType type, const QPointF &pos);

// public methods
public:
    QPixmap paintContentOnMap(const QPixmap &where, PaintStyle style = PaintStyle::ellipse) const;

// helpers
private:
    bool isInSceneRect(const QPointF &pos) const;
};

#endif // PAINTTABLESCENE_HPP
