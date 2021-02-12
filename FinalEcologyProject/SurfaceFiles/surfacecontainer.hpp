#ifndef SURFACECONTAINER_HPP
#define SURFACECONTAINER_HPP
#include <QWidget>
#include <QLabel>
#include <array>

#include "surface.hpp"
#include "HelperEntities/pch.hpp"
#include "HelperEntities/Table/tablecontainer.hpp"

class SurfaceContainer: public QWidget
{
    Q_OBJECT

private:
    QWidget *m_container;
    Surface *m_surface;
    QLabel *m_gr_label;
    TableContainer *m_deeps_table_container;

public:
    explicit SurfaceContainer(QWidget *parent = nullptr);
    ~SurfaceContainer() noexcept;

public slots:
    void setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridCreatorWidget (signal - gridChanged(same))
    void setupTableWidget(); // connected with MainWindow (signal - setupTableWidget(same)); FIXME: implicit connection with TableWidget
    void setupHeights(TableWidget *table); // connected with TableWidget (signal - closeSignal(same))
    void setupScale(double scale); // connected with QDoubleSpinBox (which is contained in MainWindow) (signal - valueChanged(same))
    void showWidget(); // connected with MainWindow (openSurfaceButtonPressed())

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
