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
<<<<<<< Updated upstream
=======
    void resetSettings();
    void setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid);
>>>>>>> Stashed changes
    void setupHeights(const QVector<QVector<QPair<bool, double>>> &heights); // connected with GridCreatorWidget(signal - gridChanged(same))

    inline void setARatio(double ratio) noexcept { m_az_ratio = ratio; } // connected with double spin box (from MainWindow); signal - valueChanged(double)
    void setWOType(int wo_index) noexcept; // connected with combo box (from MainWindow); signal - valueChanged(double)

    void acceptXSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveXSpeedsFromTable(QTableWidget &)
    void acceptYSpeedsFromTable(QTableWidget &table); // connected with MainWindow; signal - saveYSpeedsFromTable(QTableWidget &)

<<<<<<< Updated upstream
    inline void acceptXStep(const double step) noexcept {  m_xstep = step; }
    inline void acceptYStep(const double step) noexcept { m_ystep = step; }
    inline void acceptHorizon(const double horizon) noexcept {  m_horizon = horizon; }
=======
    inline void acceptXStep(const double step) noexcept {  m_xstep = step; } // connected with QDoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptYStep(const double step) noexcept { m_ystep = step; } // connected with QDoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptHorizon(const double horizon) noexcept {  m_horizon = horizon; } // connected with QDoubleSpinBox (MainWindow); signal - valueChanged(double)
    void updateCoordinates(const QVector<QVector<QPointF>> &coordinates, const QVector<QVector<QPoint>> &sector);
    inline void acceptKsiAtol(double atol) noexcept { m_ksi_atol = atol; } // connected with DoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptAbsSpeed(double speed) noexcept { m_absolute_speed = speed; } // connected with DoubleSpinBox (MainWindow); signal - valueChanged(double)
    inline void acceptAzimuth(const QPair<double, bool> &pair) { m_wind_azimuth = pair; } // connected with MainWindow; signal - sendAzimuthState(same)
    void acceptWindDirection(const QPair<int, bool> &pair);// connected with MainWindow; signal - sendSystemState(same)
    inline void acceptDistance(double distance) noexcept { m_max_computation_distance = distance; }

    inline void giveSourceInfo(int index, std::variant<PointSource, DiffusionSource> &source, QVector<PolutionMatter> &matters) const;
    void addNewSource(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters);
    void updateSource(int index, const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters);
    inline void deleteSource(int index);
    void deleteLastMarkInSource(int source_index);

    void decomposeAbsSpeed();
    void computateSpeeds() const; // connected with MainWindow; signal - computateSpeeds();
    void computatePollution();

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
>>>>>>> Stashed changes

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
