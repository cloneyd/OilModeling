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
            if(auto item = table->item(i, j); item && grid[i][j].first) {
                if(auto text{ item->text() }; !text.isEmpty()) {
                    tmp[j] = qMakePair(true, item->text().toDouble());
                }
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
            if(heights[i][j].first && heights[i][j].second < 0.) { // using shortcut computation
                if(i > 0 && i < rows - 1 && j > 0 && j < cols - 1) {
                    if(heights[i - 1][j - 1].second > 0. && // if 4 or 8 points around (i;j) is determined
                       heights[i - 1][j + 1].second > 0. &&
                       heights[i + 1][j - 1].second > 0. &&
                       heights[i + 1][j + 1].second > 0.) {
                        if(heights[i - 1][j].second > 0. && // if 8 points is determined
                           heights[i + 1][j].second > 0. &&
                           heights[i][j - 1].second > 0. &&
                           heights[i][j + 1].second > 0.) { // lagrange interpolation; FIXME: problem - valeus of lagrange methods cannot be similar; solution - exclude a repeated values
                            double x[]{ grid[i - 1][j - 1].second.x(),
                                        grid[i - 1][j].second.x(),
                                        grid[i - 1][j + 1].second.x() };
                            double y[]{ grid[i - 1][j - 1].second.y(),
                                        grid[i][j - 1].second.y(),
                                        grid[i + 1][j - 1].second.y() };
                            double z[]{ heights[i - 1][j - 1].second,
                                        heights[i - 1][j].second,
                                        heights[i - 1][j + 1].second,
                                        heights[i][j - 1].second,
                                        heights[i][j + 1].second,
                                        heights[i + 1][j - 1].second,
                                        heights[i + 1][j].second,
                                        heights[i + 1][j + 1].second,
                                        0. }; // NOTE: This value does not affect the final interpolated value and used as a 'stub'

                            double interpol_x{ grid[i][j].second.x() };
                            double interpol_y{ grid[i][j].second.y() };

                            double L[3]{};
                            for (int k{}; k < 3; ++k) {
                                for (int i{}; i < 3; ++i) {
                                    double l{ z[k * 3 + i] };
                                    for (int j{}; j < 3; ++j) {
                                        if (j != i) {
                                            l *= (interpol_x - x[j]) / (x[i] - x[j]) * (interpol_y - y[j]) / (y[i] - y[j]);
                                        }
                                    }
                                    L[k] += l;
                                }
                            }
                            heights[i][j].second = (L[0] + L[1] + L[2]) / 3.;
                        }
                        else { // bilinear interpolation
                            double x[]{ grid[i - 1][j - 1].second.x(), grid[i - 1][j + 1].second.x() };
                            double y[]{ grid[i - 1][j - 1].second.y(), grid[i + 1][j - 1].second.y() };

                            auto cur_x{ grid[i][j].second.x() };
                            auto cur_y{ grid[i][j].second.y() };
                            auto f1{ heights[i - 1][j - 1].second + (cur_x - x[0]) * (heights[i + 1][j - 1].second - heights[i - 1][j - 1].second) / (x[1] - x[0]) };
                            auto f2{ heights[i + 1][j - 1].second + (cur_x - x[0]) * (heights[i + 1][j + 1].second - heights[i + 1][j - 1].second) / (x[1] - x[0]) };
                            heights[i][j].second = f1 + (cur_y - y[0]) * (f2 - f1) / (y[1] - y[0]);
                        }
                    }
                    else if(heights[i][j - 1].second > 0. && heights[i][j + 1].second > 0.) { // linear interpolation
                        heights[i][j].second = heights[i][j - 1].second + (grid[i][j + 1].second.x() - grid[i][j - 1].second.x()) * (heights[i][j + 1].second - heights[i][j - 1].second) /
                                    (grid[i][j + 1].second.x() - grid[i][j - 1].second.x());
                    }
                    else if(heights[i - 1][j].second > 0. && heights[i + 1][j].second > 0.) { // linear interpolation
                        heights[i][j].second = heights[i - 1][j].second + (grid[i + 1][j].second.y() - grid[i - 1][j].second.y()) * (heights[i + 1][j].second - heights[i - 1][j].second) /
                                    (grid[i + 1][j].second.y() - grid[i - 1][j].second.y());
                    }
                }
                else if(j > 0 && j < cols - 1) {
                    if(heights[i][j - 1].second > 0. && heights[i][j + 1].second > 0.) { // linear interpolation
                        heights[i][j].second = heights[i][j - 1].second + (grid[i][j + 1].second.x() - grid[i][j - 1].second.x()) * (heights[i][j + 1].second - heights[i][j - 1].second) /
                                    (grid[i][j + 1].second.x() - grid[i][j - 1].second.x());
                    }
                }
                else if(i > 0 && i < rows - 1) { // linear interpolation
                    if(heights[i - 1][j].second > 0. && heights[i + 1][j].second > 0.) {
                        heights[i][j].second = heights[i - 1][j].second + (grid[i + 1][j].second.y() - grid[i - 1][j].second.y()) * (heights[i + 1][j].second - heights[i - 1][j].second) /
                                    (grid[i + 1][j].second.y() - grid[i - 1][j].second.y());
                    }
                }
                // else - do nothing now
            }
        }
    }

    // check that there is no uniterlopated values in heights
    auto is_interpolated_flag{ true };
    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(heights[i][j].first && heights[i][j].second < 0.) {
                is_interpolated_flag = false;
                break;
            }
        }
        if(!is_interpolated_flag) {
            break;
        }
    }

    if(!is_interpolated_flag) {
        QVector<double> values;
        QVector<QPair<int, double>> interpol_values;
        QVector<double> z;
        values.reserve(cols);
        interpol_values.reserve(cols);
        z.reserve(cols);
        for(int i{}; i < rows; ++i) {
            for(int j{}; j < cols; ++j) {
                if(heights[i][j].first && heights[i][j].second > 0.) {
                    values.append(grid[i][j].second.x());
                    z.append(heights[i][j].second);
                }
                else {
                    interpol_values.append(qMakePair(j, grid[i][j].second.x()));
                }
            }
            if(values.size() >= 3) {
                auto aprx_value{ approximation(values, z, interpol_values) };
                auto apr_size{ aprx_value.size() };
                for(int j{}; j < apr_size; ++j) {
                    heights[i][interpol_values[j].first].second = aprx_value[j];
                }
            }

            values.clear();
            interpol_values.clear();
            z.clear();
        }

        for(int i{}; i < cols; ++i) {
            for(int j{}; j < rows; ++j) {
                if(heights[j][i].second > 0.) {
                    values.append(grid[j][i].second.x());
                    z.append(heights[j][i].second);
                }
                else {
                    interpol_values.append(qMakePair(j, grid[j][i].second.x()));
                }
            }

            if(values.size() >= 3) {
                auto aprx_value{ approximation(values, z, interpol_values) };
                auto apr_size{ aprx_value.size() };
                for(int j{}; j < apr_size; ++j) {
                    heights[interpol_values[j].first][i].second = (heights[interpol_values[j].first][i].second + aprx_value[j]) / 2.;

                }
            }

            values.clear();
            interpol_values.clear();
            z.clear();
        }
    }
}

void SurfaceContainer::gauss(const double(&A)[3][3], const double(&B)[3], double(&C)[3])
{
    constexpr auto rows{ 3 };
    const auto cols{ 4 };
    double expanded[rows][cols]{};
       for (int i{}; i < rows; ++i) {
           for (int j{}; j < rows; ++j) {
               expanded[i][j] = A[i][j];
           }
       }
       for (int i{}; i < rows; ++i) {
           expanded[i][cols - 1] = B[i];
       }


       for (int i{}; i < rows; ++i) {
           if (expanded[i][i] == 0.) {
               for (int j{ i + 1 }; j < rows; ++j) {
                   if (expanded[j][i] != 0.) {
                       for (int k{ i }; k < cols; ++k) {
                           std::swap(expanded[i][k], expanded[j][k]);
                       }
                   }

                   break;
               }
           }

           if (expanded[i][i] != .0) {
               for (int j{ i }; j < rows - 1; ++j) {
                   double tmp = -expanded[j + 1][i] / expanded[i][i];

                   for (int k{ i }; k < cols; ++k) {
                       expanded[j + 1][k] += expanded[i][k] * tmp;
                   }
               }

               // Упрощение матрицы
               auto tmp = expanded[i][i];
               for (int j{ i }; j < cols; ++j) {
                   expanded[i][j] /= tmp;
               }
           }
       }

       // обратный ход
       for (int i = rows - 1; i >= 0; --i) {
           C[i] = expanded[i][cols - 1] / expanded[i][i];
           for (int j = i + 1; j < rows; ++j) {
               C[i] -= expanded[i][j] * C[j] / expanded[i][i];
           }
       }
}

QVector<double> SurfaceContainer::approximation(const QVector<double> &x, const QVector<double> &y, const QVector<QPair<int, double>> &interpol_x)
{
    auto size_{ x.size() };
    QVector<double> fx[3];
    fx[0].resize(size_);
    fx[1].resize(size_);
    fx[2].resize(size_);
    for (int i{}; i < size_; ++i)    fx[0][i] = std::sin(x[i]) * std::cos(x[i]);
    for (int i{}; i < size_; ++i)    fx[1][i] = x[i] * x[i] * x[i];
    for (int i{}; i < size_; ++i)    fx[2][i] = x[i] * x[i];

    double A[3][3]{};
    for (int i{}; i < 3; ++i) {
        for (int j{}; j < 3; ++j) {
            for (int k{}; k < size_; ++k) {
                A[i][j] += fx[i][k] * fx[j][k];
            }
        }
    }

    double B[3]{};
    for (int i{}; i < 3; ++i) {
        for (int j{}; j < size_; ++j) {
            B[i] += y[j] * fx[i][j];
        }
    }

    double C[3]{};
    gauss(A, B, C);

    auto inter_size{ interpol_x.size() };
    QVector<double> values(inter_size);
    for(int i{}; i < inter_size; ++i) {
        values[i] = C[0] + C[1] * interpol_x[i].second + C[2] * interpol_x[i].second * interpol_x[i].second;
    }
    return values;
}
