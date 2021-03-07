#ifndef SURFACECONTAINER_HPP
#define SURFACECONTAINER_HPP
#include <QWidget>
#include <QLabel>
#include <QTableWidget>

#include "visualization3dobject.hpp"

class Visualization3DContainer: public QWidget
{
    Q_OBJECT

private:
    QWidget *m_container;
    Visualization3DObject *m_3dobject;
    QLabel *m_gr_label;

public:
    explicit Visualization3DContainer(QWidget *parent = nullptr);
    ~Visualization3DContainer() noexcept;

public slots:
    void setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridHandler; signal - gridChanged(same)
    void setupHeights(QTableWidget &table); // connected with MainWindow; signal - saveHeightsFromTable(same)
    void setupHeights(QVector<QVector<QPair<bool, double>>> &heights); // connected with ExcelWorker; signal - heightsLoaded(same)
    void setupScale(double scale); // connected with QDoubleSpinBox (from MainWindow); signal - valueChanged(same)

signals:
    void heightsChanged(const QVector<QVector<QPair<bool, double>>> &heights); // emit function: setupHeights

// Helper functions
private:
    void interpolation_and_approximation(QVector<QVector<QPair<bool, double>>> &heights);
    void interpolation(const QVector<QVector<QPair<bool, QPointF>>> &grid, QVector<QVector<QPair<bool, double>>> &heights);
    void create_approximation_row(const QVector<QVector<QPair<bool, QPointF>>> &grid, QVector<QVector<QPair<bool, double>>> &heights);
    QVector<double> approximation(const QVector<double> &x, const QVector<double> &y, const QVector<QPair<int, double>> &interpol_x) const;

    [[nodiscard]] double bilinear_interpolation(const double (&x)[2], const double (&y)[2], const double (&z)[4], double interpol_x, double interpol_y) const;
    [[nodiscard]] double linear_interpolation(const double (&x)[2], const double (&y)[2], double interpol_x) const;

    [[nodiscard]] int binary_search(const QVector<double> &vec, double value, double atol = 1e-4) const; // return index of the nearest to value vec value
};

#endif // SURFACECONTAINER_HPP
