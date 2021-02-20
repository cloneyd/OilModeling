#ifndef COMPUTATIONS_HPP
#define COMPUTATIONS_HPP
#include <QObject>
#include <QPair>
#include <QVector>
#include <QTableWidget>

enum class WaterObjectType : unsigned
{
    river,
    lake
};

class Computator : public QObject
{
    Q_OBJECT

private:
    QVector<QVector<QPair<bool, double>>> m_heights;
    QVector<QVector<QPair<double, double>>> m_xyspeeds_vectors;

    WaterObjectType m_wo_type;

    double m_az_ratio; // this is the Az ratio value
public:
    Computator();
    ~Computator();

public slots:
    void setupHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with GridCreatorWidget(signal - gridChanged(same))

    void setARatio(double value) noexcept;
    void setWOType(int wo_index) noexcept;

    void setupXSpeedVector(QTableWidget &table);
    void setupYSpeedVector(QTableWidget &table);
};

#endif // COMPUTATIONS_HPP
