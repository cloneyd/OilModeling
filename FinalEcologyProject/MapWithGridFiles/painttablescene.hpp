#ifndef PAINTTABLESCENE_HPP
#define PAINTTABLESCENE_HPP
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPointF>

class PaintTableScene: public QGraphicsScene
{
    Q_OBJECT

private:
    // buffer for user drawn stuff
    QVector<QPointF> m_water_area;
    QVector<QPointF> m_island_area;

public:
    explicit PaintTableScene(QObject *parent = nullptr);

public slots:
    // redefines base clear() function
    void clear();

// Getters
public:
    [[nodiscard]] inline const QVector<QPointF>& getWaterObjectCoords() const noexcept { return m_water_area; }
    [[nodiscard]] inline const QVector<QPointF>& getIslandsCoords() const noexcept { return m_island_area; }

// Member access operators
public:
    // transfer the control over m_area_points; m_area_points becomes empty
    [[nodiscard]] inline QVector<QPointF>&& releaseWaterObjectCoords() noexcept { return std::move(m_water_area); }

// Overridden functions
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PAINTTABLESCENE_HPP
