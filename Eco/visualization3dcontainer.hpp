#ifndef SURFACECONTAINER_HPP
#define SURFACECONTAINER_HPP
#include <QWidget>
#include <QLabel>
#include <QTableWidget>

#include "visualization3dobject.hpp"

class Visualization3DContainter: public QWidget
{
    Q_OBJECT

private:
    QWidget *m_container;
    Visualization3DObject *m_3dobject;
    QLabel *m_gr_label;

public:
    explicit Visualization3DContainter(QWidget *parent = nullptr);
    ~Visualization3DContainter() noexcept;

public slots:
    void setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridCreatorWidget (signal - gridChanged(same))
    void setupHeights(QTableWidget &table);
    void setupScale(double scale); // connected with QDoubleSpinBox (which is contained in MainWindow) (signal - valueChanged(same))

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
