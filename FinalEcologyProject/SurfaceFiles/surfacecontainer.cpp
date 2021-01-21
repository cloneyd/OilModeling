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
    auto cols{ rows > 0 ? grid[0].size() : 0 };

    table->setRowCount(rows);
    table->setColumnCount(cols);

    auto heights{ m_surface->getHeights() };
    if(heights.empty()) {
        for(int i{}; i < rows; ++i) {
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
    auto cols{ rows > 0 ? grid[0].size() : 0 };
    QVector<QVector<QPair<bool, double>>> heights(rows);

    for(int i{}; i < rows; ++i) {
        QVector<QPair<bool, double>> tmp(cols, {false, -1.});
        for(int j{}; j < cols; ++j) {
            if(auto item = table->item(i, j); item) {
                tmp[j] = qMakePair(true, item->text().toDouble());
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
    activateWindow();
}


// private helper methods
void SurfaceContainer::interpolation(QVector<QVector<QPair<bool, double>>> &heights)
{
    const auto &grid{ m_surface->getGrid() };
    auto rows{ heights.size() };
    auto cols{ rows > 0 ? heights[0].size() : 0 };

    if(rows == 0 || cols == 0) {
        return;
    }

    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(i > 0 && i < rows - 1 && j > 0 && j < cols - 1) {
                if(heights[i][j].first && heights[i][j].second < 0.) { // using shortcut computation
                    if(heights[i - 1][j - 1].second > 0. && // if 4 or 8 points around (i;j) is determined
                       heights[i - 1][j + 1].second > 0. &&
                       heights[i + 1][j - 1].second > 0. &&
                       heights[i + 1][j + 1].second > 0.) { // if 4 points determined
                        double x[]{ grid[i - 1][j - 1].second.x(), grid[i - 1][j + 1].second.x() };
                        double y[]{ grid[i - 1][j - 1].second.y(), grid[i + 1][j - 1].second.y() };

                        auto cur_x{ grid[i][j].second.x() };
                        auto cur_y{ grid[i][j].second.y() };
                        auto f1{ heights[i - 1][j - 1].second + (cur_x - x[0]) * (heights[i + 1][j - 1].second - heights[i - 1][j - 1].second) / (x[1] - x[0]) };
                        auto f2{ heights[i + 1][j - 1].second + (cur_x - x[0]) * (heights[i + 1][j + 1].second - heights[i + 1][j - 1].second) / (x[1] - x[0]) };
                        heights[i][j].second = f1 + (cur_y - y[0]) * (f2 - f1) / (y[1] - y[0]);

                        if(heights[i - 1][j].second > 0. &&
                           heights[i + 1][j].second > 0. &&
                           heights[i][j - 1].second > 0. &&
                           heights[i][j + 1].second > 0.) { // FIXME: if 8 points is detemined

                        }
                    }
                }
                // else - do nothing
            }
        }
    }
}
