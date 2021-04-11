#ifndef COMPUTATIONS_HPP
#define COMPUTATIONS_HPP
// QT
#include <QObject>

// STL
#include <variant>

// current project
#include "computator_utilities.hpp"
#include "GridHandlerFiles/grid_handler_utilities.hpp"
#include "Visualization3D/object3d_utilities.hpp"
#include "PollutionWidget/pollutionwidget_utilities.hpp"

// TODO: create wind directions
// TODO: refactoring
class Computator : public QObject
{
    Q_OBJECT

// some constansts
private:
    static constexpr double s_owega{ 7.29e-5 };
    static constexpr double s_gamma{ 0.032 };
    static constexpr double s_pi{ 3.141592653589793 };

    static constexpr auto s_fill_value{ 100001. };; // standart fill value for all vector

private: // data
    const GridType *m_pixgrid_ptr;
    const DepthType *m_depth_ptr;

    QVector<QVector<double>> m_xspeeds_vectors;
    QVector<QVector<double>> m_yspeeds_vectors;

    double m_xstep; // -1. by default
    double m_ystep; // -1. by default

    double m_horizon; // must be 10. by default value
    WaterObjectType m_wo_type; // must be river by default
    double m_az_ratio; // Az ratio value
    double m_psi_atol; // psi accurancy tolerance (percent); 1 by default
    double m_max_computation_distance; // max computation distance (metres); 500. by default

    QPair<bool, WindDirection> m_wind_system; // pair - is available now and direction; north and false by default
    QPair<bool, double> m_azimuth; // pair - is available now and degrees; 0. and true by default;
    double m_absolute_speed; // 10. by default

    QVector<QVector<QPoint>> m_marks_indexes; // the polution mark position; empty by default
    QVector<QVector<QPointF>> m_marks_coordinates; // ALL coordinates of source marks; (diffusion sources may content few marks)
    QVector<QPair<std::variant<PointSource, DiffusionSource>, QVector<PollutionMatter>>> m_sources;

public:
    Computator(QObject *parent = nullptr);

public slots:
    void acceptGrid(const GridType &pixgrid) noexcept; // connected with GridHandler::[1]
    void acceptDepth(const DepthType &depth) noexcept; // connected with Object3DContainer::[1]
    void acceptXSpeedProjections(QVector<QVector<double>> &speeds); // connected MainWindow::[2]; TAKES OWNERSHIP
    void acceptYSpeedProjections(QVector<QVector<double>> &speeds);  // connected with MainWindow::[3]; TAKES OWNERSHIP

    void computateSpeeds(bool *operation_status = nullptr); // connected with MainWindow::[21]; emits: {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, implicitely {9}
    void decomposeAbsSpeed(bool *operation_status = nullptr); // connected with MainWindow::[19]; emits: [10], [11]
    void computatePollution(bool *operation_status = nullptr); // connected with MainWindow::[27]; TODO: #implementme

    // connected with PaintingWidget::[7];
    void acceptNewSourcesCoordinates(const QVector<QVector<QPointF>> &coordinates, const QVector<QVector<QPoint>> &indexes);
    void appendNewSource(const PointSource &source, const QVector<PollutionMatter> &matters); // connected with PollutionWidgetGenerator::[1]
    void updateSource(int source_index, const PointSource &source, const QVector<PollutionMatter> &matters); // connected with PollutionWidgetGenerator::[2]
    void appendNewSource(const DiffusionSource &source, const QVector<PollutionMatter> &matters); // connected with PollutionWidgetGenerator::[3]
    void updateSource(int source_index, const DiffusionSource &source, const QVector<PollutionMatter> &matters); // connected with PollutionWidgetGenerator::[4]
    void giveSourceInfo(int source_index, std::variant<PointSource, DiffusionSource> &will_be_source, QVector<PollutionMatter> &will_be_matters); // connected with PollutionWidgetGenerator::[5]

    inline void acceptAzimuthState(const QPair<bool, double> &state) { m_azimuth = state; } // connected with MainWindow::[8]
    inline void acceptSystemState(const QPair<bool, WindDirection> &state) { m_wind_system = state; } // connected with MainWindow::[9]
    inline void acceptARatio(double ratio) noexcept { m_az_ratio = ratio; } // connected MainWindow::[10]
    inline void acceptWaterObjectType(WaterObjectType type) noexcept { m_wo_type = type; } // connected with MainWindow::[11]
    inline void acceptHorizon(double horizon) noexcept { m_horizon = horizon; } // connected with MainWindow::[12]
    inline void acceptAtol(double atol) noexcept { m_psi_atol = atol; }
    inline void acceptAbsSpeed(double speed) noexcept { Q_ASSERT(speed > 0.); m_absolute_speed = speed; } // connected with MainWindow::[14]
    inline void acceptMaxComputationDistance(double distance) { Q_ASSERT(distance > 0.); m_max_computation_distance = distance; } // connected with MainWIndow::[15]
    inline void acceptXStep(double step) noexcept { Q_ASSERT(step > 0.); m_xstep = step; } // connected with MainWindow::[17]
    inline void acceptYStep(double step) noexcept { Q_ASSERT(step > 0.); m_ystep = step; } // connected with MainWindow::[18]
    inline void azimuthValueChanged(double value) noexcept { m_azimuth.second = value; } // connected with MainWindow::[28]
    inline void systemDirectionChanged(WindDirection direction) noexcept { m_wind_system.second = direction; } // connected with MainWindow::[29]

    inline void deleteSource(int source_index) noexcept; // connected with MainWindow::[30]
    inline void resetSources() { m_sources.clear(); } // connected with PaintingWidget::[8]

signals:
    void uxProjectionsComputated(const QVector<QVector<double>> &speeds) const; // [1]
    void uyProjectionsComputated(const QVector<QVector<double>> &speeds) const; // [2]
    void u0xProjectionsComputated(const QVector<QVector<double>> &speeds) const; // [3]
    void u0yProjectionsComputated(const QVector<QVector<double>> &speeds) const; // [4]
    void uComputated(const QVector<QVector<double>> &speeds) const; // [5]
    void u0Computated(const QVector<QVector<double>> &speeds) const; // [6]
    // [7] is free now
    void flowMapCreated(const QPixmap &pm) const; // [8]
    void getCurrentMapImage(QPixmap &will_be_pm) const; // [9]
    void xProjectionsDecomposed(const QVector<QVector<double>> &speed) const; // [10]
    void yProjectionsDecomposed(const QVector<QVector<double>> &speed)const; // [10]

// helpers
private:
    QVector<QVector<double>> computateXTanPressure() const;
    QVector<QVector<double>> computateYTanPressure() const;
    QVector<QVector<double>> computateRotT(const QVector<QVector<double>> &xtan_pressures, const QVector<QVector<double>> &ytan_pressures) const;
    QVector<QVector<double>> computateF0(const QVector<QVector<double>> &rot) const;
    QVector<QVector<double>> computatePsi(const QVector<QVector<double>> &last_psi, const QVector<QVector<double>> &f0) const;
    QVector<QVector<double>> computateU(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &xtan) const;
    QVector<QVector<double>> computateV(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &ytan) const;
    QVector<QVector<double>> computateU0(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &xtan) const;
    QVector<QVector<double>> computateV0(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &ytan) const;

    QVector<QVector<double>> createShoreBorder(const QVector<QVector<double>> &area) const; // creating shore values
    template <class Cmp>
    [[nodiscard]] bool findInVector(const QVector<QPair<int, int>> &where, const Cmp &cmp, const QPair<int, int> what) const;
    [[nodiscard]] double getCurrentAngle() const noexcept;

    // emits: [9]
    [[nodiscard]] QPixmap createFlowMap(const QVector<QVector<double>> &ux, const QVector<QVector<double>> &uy,
                         const QVector<QVector<double>> &u0x, const QVector<QVector<double>> &u0y,
                         const QVector<QVector<double>> &u, const QVector<QVector<double>> &u0) const;
};

// inline function implementation
inline void Computator::deleteSource(int source_index) noexcept
{
    Q_ASSERT_X(source_index < m_sources.size(),
               "Class - Computator", "Function - deleteSource, problem - invalid index");
    m_sources.remove(source_index);
}

#endif // COMPUTATIONS_HPP
