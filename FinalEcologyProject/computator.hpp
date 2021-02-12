#ifndef COMPUTATIONS_HPP
#define COMPUTATIONS_HPP
#include <QObject>
#include <QPair>

#include "HelperEntities/pch.hpp"
#include "HelperEntities/Table/tablecontainer.hpp"

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

    TableContainer *m_x_speed_vector_table_container;
    TableContainer *m_y_speed_vector_table_container;

    WaterObjectType m_wo_type;

    double m_az_ratio; // this is the Az ratio value
public:
    Computator();
    ~Computator();

public slots:
    void setupHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with GridCreatorWidget(signal - gridChanged(same))
    void displayXYSpeedVectorTableWidgets(); // connected with MainWindow(signal - displaySpeedsTableWidget())

    void setupXSpeedVectors(TableWidget *table); // connected with TableWidget(signal - closeSignal(same))
    void setupYSpeedVectors(TableWidget *table); // connected with TableWidget(signal - closeSignal(same))

    void setARatio(double value) noexcept;
    void setWOType(int wo_index);
};

#endif // COMPUTATIONS_HPP
