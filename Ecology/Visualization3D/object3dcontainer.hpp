#ifndef OBJECT3DCONTAINER_HPP
#define OBJECT3DCONTAINER_HPP
// QT
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include <QTextStream>

// current project
#include "object3d.hpp"

// FIXME: must setup widgets allocations
class Object3DContainer : public QWidget
{
    Q_OBJECT

private: //data
    Object3D m_3dobject;
    QLabel m_gradient_label;

public:
    Object3DContainer(QWidget *parent = nullptr);
    //~Object3DContainer() noexcept;

public slots:
    void acceptPixGrid(const GridType &pixgrid); // connected with GridHandler::[1]
    void acceptDepth(DepthType &depth); // connected with MainWindow::[1] and ExcelWorker::[1]; TAKES OWNERSHIP on depth
    void show(); // redefined; have no connection yet

    void saveState(QTextStream &stream, const char delim); // connected with InternalConfigurationFilesHandler::[9]
    // connected with InternalConfigurationFilesHandler::[10]; emits:(1)
    void restoreState(QTextStream &stream, const char delim);

signals:
    void depthChanged(const DepthType &depth) const;// [1]

// helpers
private:
    void acceptDepth_(DepthType &depth, bool interpolate);
    // approximation manager
    void interpolation_and_approximation(DepthType &depth);
    // interpolation
    void interpolation(const GridType &realgrid, DepthType &depth);
    // approximation
    void create_approximation_row(const GridType &realgrid, DepthType &depth);
    QVector<double> approximation(const QVector<double> &x, const QVector<double> &y, const QVector<QPair<int, double>> &interpol_x) const;

    [[nodiscard]] inline double bilinear_interpolation(const double (&x)[2], const double (&y)[2], const double (&z)[4], double interpol_x, double interpol_y) const;
    [[nodiscard]] inline double linear_interpolation(const double (&x)[2], const double (&y)[2], double interpol_x) const;

    [[nodiscard]] int binary_search(const QVector<double> &vec, double value, double atol = 1e-4) const; // return index of the nearest to value vec value
};

// inline functions implementation
[[nodiscard]] inline double Object3DContainer::bilinear_interpolation(const double (&x)[2], const double (&y)[2], const double (&z)[4], double interpol_x, double interpol_y) const
{
    auto f1{ z[0] + (interpol_x - x[0]) * (z[2] - z[0]) / (x[1] - x[0]) };
    auto f2{ z[2] + (interpol_x - x[0]) * (z[3] - z[2]) / (x[1] - x[0]) };
    return f1 + (interpol_y - y[0]) * (f2 - f1) / (y[1] - y[0]);
}

[[nodiscard]] inline double Object3DContainer::linear_interpolation(const double (&x)[2], const double (&y)[2], double interpol_x) const
{
    return y[0] + (interpol_x - x[0]) * (y[1] - y[0]) / (x[1] - x[0]);
}

#endif // OBJECT3DCONTAINER_HPP
