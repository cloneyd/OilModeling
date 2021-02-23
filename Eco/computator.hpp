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

// class constants
private:
    static constexpr double m_owega = 7.29e-5; // one constant to all objects
    static constexpr double m_gamma = 0.032; // one constants to all objects

private:
    QVector<QVector<QPair<bool, double>>> m_heights;
    QVector<QVector<double>> m_xspeeds_vectors; // filled with 100001. by default
    QVector<QVector<double>> m_yspeeds_vectors; // filled with 100001. by default

    QVector<QVector<QPair<double, double>>> m_xytan_pressure_vectors;
    QVector<QVector<double>> m_rot_t_vectors;
    QVector<QVector<double>> m_f0_vectors;
    QVector<QVector<double>> m_ksi0_vectors;
    QVector<QVector<double>> m_ksi_vectors;
    QVector<QVector<double>> m_u_vectors;
    QVector<QVector<double>> m_v_vectors;

    WaterObjectType m_wo_type;

    double m_az_ratio; // this is the Az ratio value
public:
    Computator();
    ~Computator();

// setters
public:
    void setXTanPressure();
    void setYTanPressure();

    void setRotT();

    void setF0();

    void setKsi0();
    void approximation();
    void setKsi();

    void setU();
    void setV();

public slots:
    void setupHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with GridCreatorWidget(signal - gridChanged(same))

    void setARatio(double value) noexcept; // connected with double spin box (from MainWindow); signal - valueChanged(double)
    void setWOType(int wo_index) noexcept; // connected with combo box (from MainWindow); signal - valueChanged(double)

    void getXSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveXSpeedsFromTable(QTableWidget &)
    void getYSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveYSpeedsFromTable(QTableWidget &)

signals:
    void xSpeedChanged(const QVector<QVector<double>> &xspeed);
    void ySpeedChanged(const QVector<QVector<double>> &yspeed);

// helpers
private:
    void createShoreBorder(QVector<QVector<double>> &area); // creating shore values
    template <class Cmp>
    bool findInVector(const QVector<QPair<int, int>> &vec, const Cmp &cmp, const QPair<int, int> value);
};

#endif // COMPUTATIONS_HPP
