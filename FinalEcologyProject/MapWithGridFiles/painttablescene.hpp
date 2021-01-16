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
    QVector<QPointF> m_area_points;

public:
    explicit PaintTableScene(QObject *parent = nullptr);

public slots:
    // redefines base clear() function
    void clear();

// Getters
public:
    [[nodiscard]] const QVector<QPointF>& getAreaPoints() const noexcept;

// Member access operators
public:
    // transfer the control over m_area_points; m_area_points becomes empty
    [[nodiscard]] QVector<QPointF>&& releaseAreaPoints() noexcept;

// Overridden functions
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PAINTTABLESCENE_HPP
