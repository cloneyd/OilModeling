#ifndef COMPUTATIONS_HPP
#define COMPUTATIONS_HPP
#include <QObject>
#include <QPair>
#include <QVector>
#include <QTableWidget>

#include <variant>

#include "source_types.hpp"

enum class WaterObjectType : unsigned char // AHTUNG!!! IF WATER OBJECT COMBO BOX(class - MainWindow) WILL BE CHANGED - UB!!!!!
{
    MIN,
    River = MIN,
    Lake,
    MAX = Lake
};

enum class WindDirection : unsigned char // AHTUNG!!! IF SYSTEM COMBO BOX(class - MainWindow) WILL BE CHANGED - UB!!!
{
    MIN,
    North = MIN, // first el
    Northeast,
    East,
    Southeast,
    South,
    Southwest,
    West,
    Northwest, // last el
    MAX = Northwest // must be equal to last el
};

// TODO: mark changed slot
class Computator : public QObject
{
    Q_OBJECT

// class constants
public:
    static constexpr double m_owega{ 7.29e-5 };
    static constexpr double m_gamma{ 0.032 };
    static constexpr auto fill_value{ 100001. };; // standart fill value for all vector
    static constexpr double pi{ 3.141592653589793 };

private:
    const QVector<QVector<QPair<bool, QPointF>>> *m_grid_ptr; // nullptr by default;
    const QVector<QVector<QPair<bool, double>>> *m_heights_ptr; // nullptr by default
    QVector<QVector<double>> m_xspeeds_vectors; // filled with fill_value by default
    QVector<QVector<double>> m_yspeeds_vectors; // filled with fill_value by default

    double m_xstep; // -1. by default
    double m_ystep; // -1. by default

    double m_horizon; // must be 1. by default value
    WaterObjectType m_wo_type; // must be river by default
    double m_az_ratio; // Az ratio value
    double m_ksi_atol; // ksi accurancy tolerance (percent); 1 by default
    double m_max_computation_distance; // max computation distance (metres); 500. by default

    QPair<WindDirection, bool> m_wind_direction; // pair - direction is available now; north and false by default
    QPair<double, bool> m_wind_azimuth; // pair - degrees and is available now; 0. and true by default;
    double m_absolute_speed; // 10. by default

    std::list<QPair<int, int>> m_mark_index; // the polution mark position; empty by default
    QVector<QPair<std::variant<PointSource, DiffusionSource>, QVector<PolutionMatter>>> m_sources; /* first value - the source - will contain one of
                                                                    two types: PointSource of DiffusionSource. Must be checked with index() before using;
                                                                    second - vector of polution matters*/

    QVector<double> computateACoef(const QVector<PolutionMatter> &matters) const;
    QVector<double> computateCRevMaxI(const QVector<PolutionMatter> &matters) const;
    QVector<double> computateCStAdd(const QVector<PolutionMatter> &matters) const;
    QVector<double> computateVAT(const QVector<PolutionMatter> &matters, const QVector<PointSource> &sources);
    void computateRevTask(const QVector<PolutionMatter> &matters);
public:
    Computator();
    ~Computator();

public slots:
    void setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid);
    void setupHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with GridCreatorWidget(signal - gridChanged(same))

    inline void setARatio(double ratio) noexcept { m_az_ratio = ratio; } // connected with double spin box (from MainWindow); signal - valueChanged(double)
    void setWOType(int wo_index) noexcept; // connected with combo box (from MainWindow); signal - valueChanged(double)

    void acceptXSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveXSpeedsFromTable(QTableWidget &)
    void acceptYSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveYSpeedsFromTable(QTableWidget &)

    inline void acceptXStep(const double step) noexcept {  m_xstep = step; } // connected with QDoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptYStep(const double step) noexcept { m_ystep = step; } // connected with QDoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptHorizon(const double horizon) noexcept {  m_horizon = horizon; } // connected with QDoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptMarkPosition(QPair<int, int> mark_pos) { m_mark_index.push_back(mark_pos); } // connected with GridHandler; signal - markSearched(same)
    inline void acceptKsiAtol(double atol) noexcept { m_ksi_atol = atol; } // connected with DoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptAbsSpeed(double speed) noexcept { m_absolute_speed = speed; } // connected with DoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptAzimuth(const QPair<double, bool> &pair) { m_wind_azimuth = pair; } // connected with MainWindow; signal - sendAzimuthState(same)
    void acceptWindDirection(const QPair<int, bool> &pair);// connected with MainWindow; signal - sendSystemState(same)
    inline void acceptDistance(double distance) noexcept { m_max_computation_distance = distance; }

    inline void giveSourceInfo(int index, std::variant<PointSource, DiffusionSource> &source, QVector<PolutionMatter> &matters) const;
    void addNewSource(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters);
    void updateSource(int index, const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters);
    inline void deleteSource(int index) { m_sources.remove(index); }

    void decomposeAbsSpeed();
    void computateSpeeds() const; // connected with MainWindow; signal - computateSpeeds();

signals:
    void xWindProjectionChanged(const QVector<QVector<double>> &speeds);
    void yWindProjectionChanged(const QVector<QVector<double>> &speeds);

    void uxSpeedChanged(const QVector<QVector<double>> &xspeed) const;
    void uySpeedChanged(const QVector<QVector<double>> &yspeed) const;
    void u0xSpeedChanged(const QVector<QVector<double>> &xspeed) const;    
    void u0ySpeedChanged(const QVector<QVector<double>> &yspeed) const;
    void uChanged(const QVector<QVector<double>> &speed) const;
    void u0Changed(const QVector<QVector<double>> &speed) const;

    void speedsComputated() const;

    void getCurrentMapImage(QPixmap &map) const;
    void flowMapCreated(const QPixmap &map) const;

    void sourcesChanged(const PointSource &source, const QVector<PolutionMatter> &matters) const;
    void sourcesChanged(const DiffusionSource &source, const QVector<PolutionMatter> &matters) const;

    void sourceUpdated(int index, const PointSource &source, const QVector<PolutionMatter> &matters) const;
    void sourceUpdated(int index, const DiffusionSource &source, const QVector<PolutionMatter> &matters) const;

// helpers
private:
    QVector<QVector<double>> computateXTanPressure() const;
    QVector<QVector<double>> computateYTanPressure() const;

    QVector<QVector<double>> computateRotT(const QVector<QVector<double>> &xtan_pressures, const QVector<QVector<double>> &ytan_pressures) const;

    QVector<QVector<double>> computateF0(const QVector<QVector<double>> &rot) const;

    QVector<QVector<double>> computateKsi(const QVector<QVector<double>> &function, const QVector<QVector<double>> &f0) const;

    QVector<QVector<double>> computateU(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &xtan) const;
    QVector<QVector<double>> computateV(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &ytan) const;
    QVector<QVector<double>> computateU0(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &xtan) const;
    QVector<QVector<double>> computateV0(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &ytan) const;

    QVector<QVector<double>> createShoreBorder(const QVector<QVector<double>> &area) const; // creating shore values
    template <class Cmp>
    bool findInVector(const QVector<QPair<int, int>> &vec, const Cmp &cmp, const QPair<int, int> value) const;

    QPixmap createFlowMap(const QVector<QVector<double>> &ux, const QVector<QVector<double>> &uy,
                          const QVector<QVector<double>> &u0x, const QVector<QVector<double>> &u0y,
                          const QVector<QVector<double>> &u, const QVector<QVector<double>> &u0) const;
};

// inline function realization
inline void Computator::giveSourceInfo(int index, std::variant<PointSource, DiffusionSource> &source, QVector<PolutionMatter> &matters) const
{
    source = m_sources[index].first;
    matters = m_sources[index].second;
}
#endif // COMPUTATIONS_HPP
