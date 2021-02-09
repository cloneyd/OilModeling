#ifndef SURFACECONTAINER_HPP
#define SURFACECONTAINER_HPP
#include <QWidget>
#include <QLabel>
#include <array>

#include "surface.hpp"
#include "HelperEntities/pch.hpp"
#include "HelperEntities/tablewidget.hpp"

class SurfaceContainer: public QWidget
{
    Q_OBJECT

private:
    QWidget *m_container;
    Surface *m_surface;
    QLabel *m_gr_label;

public:
    explicit SurfaceContainer(QWidget *parent = nullptr);
    ~SurfaceContainer() noexcept;

public slots:
    void setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid); // connected with GridCreatorWidget (signal - gridChanged(same))
    void setupTableWidget(TableWidget *table) const; // connected with MainWindow (signal - setupTableWidget(same)); FIXME: implicit connection with TableWidget
    void setupHeights(TableWidget *table); // connected with TableWidget (signal - closeSignal(same))
    void setupScale(double scale); // connected with QDoubleSpinBox (which is contained in MainWindow) (signal - valueChanged(same))
    void showWidget(); // connected with MainWindow (openSurfaceButtonPressed())

signals:
    void heightsChanged(const QVector<QVector<QPair<bool, double>>> &heights); // emit function: setupHeights

// Helper functions
private:
    void interpolation(QVector<QVector<QPair<bool, double>>> &heights);
    void gauss(const double(&A)[3][3], const double(&B)[3], double(&C)[3]);
    QVector<double> approximation(const QVector<double> &x, const QVector<double> &y, const QVector<QPair<int, double>> &interpol_x);
};

#endif // SURFACECONTAINER_HPP
