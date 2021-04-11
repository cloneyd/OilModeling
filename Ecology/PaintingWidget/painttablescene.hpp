#ifndef PAINTTABLESCENE_HPP
#define PAINTTABLESCENE_HPP
// QT
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

// STL
#include <list>
#include <deque>

// current project
#include "paint_table_scene_utilities.hpp" // includes pch
#include "PollutionWidget/pollutionwidget_utilities.hpp"

class PaintTableScene : public QGraphicsScene
{
    Q_OBJECT

private: // type aliases
    using WOBufType = std::list<std::deque<QPointF>>;
    using IslandBufType = std::list<std::deque<QPointF>>;
    using SourceMarksBufType = QVector<QVector<QPointF>>;

public: // static constants
    static constexpr auto s_wo_color{ QColor(0x03, 0x38, 0xEF) };
    static constexpr auto s_island_color{ QColor(0x9F, 0x63, 0x42) };
     static constexpr auto s_mark_icon_filepath{ "://imgs/Images//location.svg" }; // filepath to mark icon}

private: // data
    WOBufType m_wo_buffer; // water object points buffer; empty by default
    IslandBufType m_islands_buffer; // islands points buffer; empty by default
    SourceMarksBufType m_sources_marks_buffer; // source marks buffer; empty by default

    WOBufType m_stashed_wo;
    IslandBufType m_stashed_islands;
    std::list<QPointF> m_stashed_sources_marks;

    QPixmap m_icon;

public:
    PaintTableScene(QObject *parent = nullptr);

signals:
    void woChanged(ChangeType change) const; // [1]
    void islandChanged(ChangeType /*change*/) const; // [2]
    void sourcesMarksChanged(ChangeType /*change*/, const QPointF &pos) const; // [3]
    void getCurrentSourceIndex(int &will_be_index) const; // [4]
    void getSourceType(int source_index, SourceType &will_be_type) const; // [5]

// Getters
public:
    [[nodiscard]] QVector<QPointF> getWaterObjectPoints() const; // create one vector from std::list<QVector>;
    [[nodiscard]] QVector<QPointF> getIslandsPoints() const; // create one vector from std::list<QVector>
    [[nodiscard]] inline const SourceMarksBufType& getSourcesMarks() const noexcept { return m_sources_marks_buffer; }

// Overridden functions
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; // emits: woChanged [1] or islandChanged [2]
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    /* emits: sourcesMarksChanged; do nothing if widget sources combo box is empty
     * also can emit woChanged[1]::deleting if point belongs to scene */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override; // emits [3], [4], [5]

// redefined functions
public:
    void clear();

// Modifiers
public:
    // NOT EMITTING
    void clearStashes() /*noexcept*/; // clear all stashes
    inline void deleteSource(int source_index) { m_sources_marks_buffer.remove(source_index); }
    inline void deleteLastMark(int source_index) { m_sources_marks_buffer[source_index].pop_back(); }
    inline void hideLastWO(); // hides last water object change to stash; emits: woChanged
    inline void hideLastIsland(); // hides last island change to stash; emits: islandChanged
    inline void hideLastMark(int source_index); // hides last mark change of source with given index to stash; emits: sourcesMarksChanged

    // return value to buffer from stash; do nothing if stash is empty; NOT EMITTING
    inline void returnFromWOStash(); // emits: woChanged
    inline void returnFromIslandsStash(); // emits: islandChanged
    inline void returnFromMarksStash(int source_index); // return to buffer with given index; emits: sourcesMarksChanged

    /* append marks to m_source_mark_buffer (inserts at the end, can be empty if invalid)
     * NOT EMITTING
    * TAKES OWNERSHIP */
    inline void appendSourceMarks(QVector<QPointF> &&marks) { m_sources_marks_buffer.append(std::move(marks)); };
    // applies marks to source with given index; TAKES OWNERSHIP on marks; NOT EMITTING
    inline void applySourceMarks(int source_index, QVector<QPointF> &&marks) { m_sources_marks_buffer[source_index] = std::move(marks); }
// helpers
public:
    // draw current content on Pixmap and returns it
    [[nodiscard]] QPixmap paintContent(const QPixmap &pm, PaintStyle style = PaintStyle::Lines) const;

private:
    [[nodiscard]] bool isInSceneRect(const QPointF &pos) const;
    void connectPoints(const QPointF &first, const QPointF &second, const QColor &color, std::deque<QPointF> &where);
};

// inline functions implementation
inline void PaintTableScene::hideLastWO() // NOT EMITTING
{
   m_stashed_wo.push_back(std::move(m_wo_buffer.back()));
   m_wo_buffer.pop_back();
}

inline void PaintTableScene::hideLastIsland() // NOT EMITTING
{
    m_stashed_islands.push_back(std::move(m_islands_buffer.back()));
    m_islands_buffer.pop_back();
}

inline void PaintTableScene::hideLastMark(int source_index) // NOT EMITTING
{
    m_stashed_sources_marks.push_back(std::move(m_sources_marks_buffer[source_index].back()));
    m_sources_marks_buffer[source_index].pop_back();
}

inline void PaintTableScene::returnFromWOStash() // NOT EMITTING
{
    m_wo_buffer.push_back(std::move(m_stashed_wo.back()));
    m_stashed_wo.pop_back();
}

inline void PaintTableScene::returnFromIslandsStash() // NOT EMITTING
{
    m_islands_buffer.push_back(std::move(m_stashed_islands.back()));
    m_stashed_islands.pop_back();
}

inline void PaintTableScene::returnFromMarksStash(int source_index) // NOT EMITTING
{
    m_sources_marks_buffer[source_index].append(std::move(m_stashed_sources_marks.back()));
    m_stashed_sources_marks.pop_back();
}

#endif // PAINTTABLESCENE_HPP
