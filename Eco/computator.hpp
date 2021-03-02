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
public:
    static constexpr double m_owega{ 7.29e-5 };
    static constexpr double m_gamma{ 0.032 };
    static constexpr auto fill_value{ 100001. };; // standart fill value for all vector

private:
    QVector<QVector<QPair<bool, double>>> m_heights;
    QVector<QVector<double>> m_xspeeds_vectors; // filled with fill_value by default
    QVector<QVector<double>> m_yspeeds_vectors; // filled with fill_value by default
    bool m_is_xspeeds_entered_flag; // if m_xspeeds_vectors is entered - true
    bool m_is_yspeeds_entered_flag; // if m_yspeeds_vectors is entered - true

    double m_xstep; // -1. by default
    double m_ystep; // -1. by default

    QVector<QVector<double>> m_u_vectors;
    QVector<QVector<double>> m_v_vectors;
    QVector<QVector<double>> m_u0_vectors;
    QVector<QVector<double>> m_v0_vectors;

    double m_horizon; // must be 1. as default value

    WaterObjectType m_wo_type;

    double m_az_ratio; // this is the Az ratio value
public:
    Computator();
    ~Computator();

public slots:
    void setupHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with GridCreatorWidget(signal - gridChanged(same))

    inline void setARatio(double ratio) noexcept { m_az_ratio = ratio; } // connected with double spin box (from MainWindow); signal - valueChanged(double)
    void setWOType(int wo_index) noexcept; // connected with combo box (from MainWindow); signal - valueChanged(double)

    void acceptXSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveXSpeedsFromTable(QTableWidget &)
    void acceptYSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveYSpeedsFromTable(QTableWidget &)

    inline void acceptXStep(const double step) noexcept {  m_xstep = step; }
    inline void acceptYStep(const double step) noexcept { m_ystep = step; }
    inline void acceptHorizon(const double horizon) noexcept {  m_horizon = horizon; }

    void computateSpeeds() const;

signals:
    void xSpeedChanged(const QVector<QVector<double>> &xspeed); // FIXME: wrong value now
    void ySpeedChanged(const QVector<QVector<double>> &yspeed); // FIXME: wrong value now

// helpers
private:    
    QVector<QVector<double>> computateXTanPressure() const;
    QVector<QVector<double>> computateYTanPressure() const;

    QVector<QVector<double>> computateRotT(const QVector<QVector<double>> &xtan_pressures, const QVector<QVector<double>> &ytan_pressures) const;

    QVector<QVector<double>> computateF0(const QVector<QVector<double>> &rot) const;

    QVector<QVector<double>> computateKsi0() const;
    QVector<QVector<double>> approximation() const;
    QVector<QVector<double>> computateKsi() const;

    QVector<QVector<double>> computateU() const;
    QVector<QVector<double>> computateV() const;


    QVector<QVector<double>> createShoreBorder(const QVector<QVector<double>> &area) const; // creating shore values
    template <class Cmp>
    bool findInVector(const QVector<QPair<int, int>> &vec, const Cmp &cmp, const QPair<int, int> value) const;
};

#endif // COMPUTATIONS_HPP
