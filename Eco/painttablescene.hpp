#ifndef PAINTTABLESCENE_HPP
#define PAINTTABLESCENE_HPP
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPointF>


class PaintTableScene: public QGraphicsScene
{
    Q_OBJECT

    enum class LastChanger // enum which contains who added last change to the table
    {
        water_object,
        island
    };

public:
    static constexpr auto line_width{ 3. };
    static inline auto water_object_color{ QColor(0x0338EF)};
    static inline auto islands_color{ QColor(0x9F6342) };
<<<<<<< Updated upstream

private:
    QVector<QVector<QPointF>> m_wo_buffer; // buffer for temporary water object drawn sruff
    QVector<QVector<QPointF>> m_islands_buffer; // buffer for a temporary island drawn stuff

    QVector<QVector<QPointF>> m_wo_stash; // buffer for a currently unused things
    QVector<QVector<QPointF>> m_islands_stash; // buffer for a currently unused things
=======
    static constexpr auto mark_icon_filepath{ ":/imgs/images/location.svg" }; // filepath to mark icon

private:
    std::list<QVector<QPointF>> m_wo_buffer; // buffer for temporary water object drawn sruff
    std::list<QVector<QPointF>> m_islands_buffer; // buffer for a temporary island drawn stuff
    QVector<QVector<QPointF>> m_mark_pos_buffer; // the mark position; {-1., -1.} be default
    QVector<int> m_indexes_buffer;

    std::list<QVector<QPointF>> m_wo_stash; // buffer for a currently unused things
    std::list<QVector<QPointF>> m_islands_stash; // buffer for a currently unused things
    QVector<QPointF> m_mark_pos_stash; // the last mark position; {-1., -1.} be default
    QVector<int> m_indexes_stash;
>>>>>>> Stashed changes

    QVector<LastChanger> m_last_changes; // contains the log of changes
    QVector<LastChanger> m_last_changes_stash; // contains the stash logs

    bool m_stashed;

public:
    explicit PaintTableScene(QObject *parent = nullptr);

public slots:
    // redefines base clear() function
    void clear();

<<<<<<< Updated upstream
=======
signals:
    void stashedChangeLogChanged(int number_of_writes) const;
    void changeLogChanged(int number_of_writes) const;
    void markPositionChanged(int, const QPointF *newpos, bool must_be_deleted_if_not_found = false) const;

    void getCurrentSourceIndex(int &will_be_index);
    void getSourceType(SourceType &type, int index);

>>>>>>> Stashed changes
// Getters
public:
    [[nodiscard]] QVector<QPointF> getWaterObjectCoords();
    [[nodiscard]] QVector<QPointF> getIslandsCoords();

    [[nodiscard]] inline int getNumberOfChanges() const { return m_last_changes.size(); }
    [[nodiscard]] inline int getNumberOfStashedChanges() const { return m_last_changes_stash.size(); }

// Overridden functions
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

// Modifiers
public:
    void hideToStash();
    void getFromStash();
<<<<<<< Updated upstream
=======
    void resetStashes();
    inline void deleteLastMark(int source_index) { m_mark_pos_buffer[source_index].pop_back(); }

    inline void insertSource(int index) { m_mark_pos_buffer.insert(index, QVector<QPointF>{});}
    inline void insertSource(int index, const QPointF &pos);
    inline void deleteSource(int source_index);
    void updateSource(int index, SourceType type, const QPointF &pos);

// public methods
public:
    QPixmap paintContentOnMap(const QPixmap &where, PaintStyle style = PaintStyle::ellipse) const;

// helpers
private:
    bool isInSceneRect(const QPointF &pos) const;
>>>>>>> Stashed changes
};

inline void PaintTableScene::insertSource(int index, const QPointF &pos)
{
    m_mark_pos_buffer.insert(index, QVector<QPointF>{ pos });
    emit markPositionChanged(index, &pos, true);
}

inline void PaintTableScene::deleteSource(int source_index)
{
    m_mark_pos_buffer.remove(source_index);
    emit markPositionChanged(source_index, nullptr);
}

#endif // PAINTTABLESCENE_HPP
