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
    template <int size>
    void gauss(const double(&A)[size][size], const double(&B)[size], double(&C)[size]) const;
    QVector<double> approximation(const QVector<double> &x, const QVector<double> &y, const QVector<QPair<int, double>> &interpol_x);
};

#endif // SURFACECONTAINER_HPP