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

private:
    QVector<QVector<QPointF>> m_wo_buffer; // buffer for temporary water object drawn sruff
    QVector<QVector<QPointF>> m_islands_buffer; // buffer for a temporary island drawn stuff

    QVector<QVector<QPointF>> m_wo_stash; // buffer for a currently unused things
    QVector<QVector<QPointF>> m_islands_stash; // buffer for a currently unused things

    QVector<LastChanger> m_last_changes; // contains the log of changes
    QVector<LastChanger> m_last_changes_stash; // contains the stash logs

public:
    explicit PaintTableScene(QObject *parent = nullptr);

public slots:
    // redefines base clear() function
    void clear();

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
};

#endif // PAINTTABLESCENE_HPP
