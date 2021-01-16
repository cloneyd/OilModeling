#include "surfacecontainer.hpp"

#include <QMessageBox>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <algorithm>
#include <QTableWidgetItem>

// ctor and dtor
SurfaceContainer::SurfaceContainer(QWidget *parent) :
    QWidget(parent),
    m_container{}, // will be deleted automatically with widget
    m_surface{},
    m_gr_label{ new QLabel } // WARNING: may throw; should be replaced
{
    auto graph = new QtDataVisualization::Q3DSurface; // WARNING: may throw; // FIXME!!!: deletion problem (leak now)
    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return;
    }
    m_container = QWidget::createWindowContainer(graph, this); // adopt the graph to container

    QSize screenSize = screen()->size();
    m_container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6)); // magic numbers
    m_container->setMaximumSize(screenSize);
    m_container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_container->setFocusPolicy(Qt::StrongFocus);

    QHBoxLayout *hLayout = new QHBoxLayout(this); // WARNING: may throw; should be replaced
    QVBoxLayout *vLayout = new QVBoxLayout(); // WARNING: may throw; should be replaced
    hLayout->addWidget(m_container, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);

    setWindowTitle(QString("3D визуализация"));

    QGroupBox *heightMapGroupBox = new QGroupBox(QString("Цветовая палитра")); // WARNING: may throw; should be replaced
    QVBoxLayout *colorMapVBox = new QVBoxLayout;// WARNING: may throw; new layout for label; should be replaced
    colorMapVBox->addWidget(m_gr_label);
    heightMapGroupBox->setLayout(colorMapVBox);

    vLayout->addWidget(heightMapGroupBox);

    m_surface = new Surface(graph); // WARNING: may throw; should be replaced
}

SurfaceContainer::~SurfaceContainer() noexcept
{
    delete m_gr_label;
    delete m_surface;
}


// public slots
void SurfaceContainer::setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    m_surface->setGrid(grid);
    m_gr_label->setPixmap(m_surface->getGradientPixmap());
    m_surface->updateMap();
}

void SurfaceContainer::setupTableWidget(TableWidget *table) const
{
    connect(table, SIGNAL(closeSignal(TableWidget*)), // implicit connection; may cause problems with understanding
            this, SLOT(setupHeights(TableWidget*)));

    auto grid{ m_surface->getGrid() };
    auto rows{ grid.size() };
    auto max_cols{ 0 };
    for(int i{}; i < rows; ++i) {
        max_cols = std::max(max_cols, grid[i].size());
    }

    table->setRowCount(rows);
    table->setColumnCount(max_cols);

    auto heights{ m_surface->getHeights() };
    if(heights.empty()) {
        for(int i{}; i < rows; ++i) {
            auto cols{ grid[i].size() };
            for(int j{}; j < cols; ++j) {
                if(grid[i][j].first) {
                    auto item{ new QTableWidgetItem }; // WARNING: may throw; should be replaced
                    item->setBackground(QBrush(Qt::cyan));
                    item->setText("-1");
                    item->setTextAlignment(Qt::AlignCenter);
                    table->setItem(i, j, item);
                }
            }
        }
    }
    else {
        for(int i{}; i < rows; ++i) {
            auto cols{ heights[i].size() };
            for(int j{}; j < cols; ++j) {
                if(heights[i][j].first) {
                    auto item{ new QTableWidgetItem }; // WARNING: may throw; should be replaced
                    item->setBackground(QBrush(Qt::cyan));
                    item->setText(QString("%1").arg(heights[i][j].second));
                    item->setTextAlignment(Qt::AlignCenter);
                    table->setItem(i, j, item);
                }
            }
        }
    }
}

void SurfaceContainer::setupHeights(TableWidget *table)
{
    auto grid{ m_surface->getGrid() };
    auto rows{ grid.size() };
    QVector<QVector<QPair<bool, double>>> heights(rows);

    for(int i{}; i < rows; ++i) {
        auto cols{ grid[i].size() };
        QVector<QPair<bool, double>> tmp(cols);
        for(int j{}; j < cols; ++j) {
            if(grid[i][j].first) {
                tmp[j] = qMakePair(grid[i][j].first, table->item(i, j)->text().toDouble());
            }
        }
        heights[i] = std::move(tmp); // WARNING: extra copy
    }

    interpolation(heights);
    m_surface->setHeights(std::move(heights));
    m_gr_label->clear();
    m_gr_label->setPixmap(m_surface->getGradientPixmap());

    disconnect(table, SIGNAL(closeSignal(TableWidget*)),
               this, SLOT(setupTableWidget(TableWidget*)));

    emit heightsChanged(m_surface->getHeights());
}

void SurfaceContainer::setupScale(double scale)
{
    m_surface->setScale(screen()->physicalDotsPerInch() / 2.54 / scale);
}

void SurfaceContainer::showWidget()
{
    show();
}


// private helper methods
void SurfaceContainer::interpolation(QVector<QVector<QPair<bool, double>>> &heights)
{

}
