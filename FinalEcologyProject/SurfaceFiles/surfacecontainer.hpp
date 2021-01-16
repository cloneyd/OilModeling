#ifndef SURFACECONTAINER_HPP
#define SURFACECONTAINER_HPP
#include <QWidget>
#include <QLabel>

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
    void setupGrid(const QVector<QPair<int, QVector<QPointF>>> &grid); // connected with GridCreatorWidget (signal - gridChanged(same))
    void setupTableWidget(TableWidget *table) const; // connected with MainWindow (signal - setupTableWidget(same)); FIXME: implicit connection with TableWidget
    void setupHeights(TableWidget *table); // connected with TableWidget (signal - closeSignal(same))
    void setupScale(double scale); // connected with QDoubleSpinBox (which is contained in MainWindow) (signal - valueChanged(same))
    void showWidget(); // connected with MainWindow (openSurfaceButtonPressed())

signals:
    void heightsChanged(const QVector<QPair<int, QVector<double>>> &heights); // emit function: setupHeights

// Helper functions
private:
    void interpolation(QVector<QPair<int, QVector<double>>> &heights);
};

#endif // SURFACECONTAINER_HPP
