#include "computator.hpp"

// third party functions
void showErrorMessageBox(const QString &msg);


// ctors and dtor
Computator::Computator() :
    QObject{},
    m_heights{},
    m_xspeeds_vectors{},
    m_yspeeds_vectors{},
    m_xstep{ -1. },
    m_ystep{ -1. },
    m_xytan_pressure_vectors{},
    m_rot_t_vectors{},
    m_f0_vectors{},
    m_ksi0_vectors{},
    m_ksi_vectors{},
    m_u_vectors{},
    m_v_vectors{},
    m_wo_type{ WaterObjectType::river },
    m_az_ratio{ 0.001 }
{

}

Computator::~Computator()
{

}


// setters
void Computator::setXTanPressure(){
    auto rows{ m_xspeeds_vectors.size() }; // m_xspeeds_vectors and m_yspeeds_vectors have same size
    auto cols{ rows > 0 ? m_xspeeds_vectors[0].size() : 0 };

    if(m_xytan_pressure_vectors.size() == 0) {
        m_xytan_pressure_vectors.resize(rows);
        for(int i{}; i < rows; ++i) {
           m_xytan_pressure_vectors[i].resize(cols);
        }
    }

    for(int i{ 1 }; i < rows - 1; ++i) {
        for(int j{ 1 }; j < cols - 1; ++j) {
            m_xytan_pressure_vectors[i][j].first = m_gamma * m_xspeeds_vectors[i][j] * std::abs(m_xspeeds_vectors[i][j]);
        }
    }
}


// public slots
void Computator::setupHeights(const QVector<QVector<QPair<bool, double>>> &heights)
{
    auto rows{ heights.size() };
    if(rows < 1) {
        return;
    }

    auto cols{ heights[0].size() };
    if(cols < 1) {
        return;
    }

    m_heights.resize(rows);
    for(int i{}; i < rows; ++i) {
        m_heights[i].resize(cols);

        for(int j{}; j < cols; ++j) {
            m_heights[i][j] = heights[i][j];
        }
    }
}

void Computator::setARatio(double ratio) noexcept
{
    m_az_ratio = ratio;
}

void Computator::setWOType(int index_type) noexcept
{
    switch(index_type) {
    case 0:
        m_wo_type = WaterObjectType::river;
        break;

    case 1:
        m_wo_type = WaterObjectType::lake;
        break;

    default:
        showErrorMessageBox("Тип водного объекта не опознан");
    }

}

void Computator::getXSpeedsFromTable(QTableWidget &table)
{
    auto nrows{ m_heights.size() };
    auto ncols{ nrows > 0 ? m_heights[0].size() : 0 };

    m_xspeeds_vectors.clear();
    const auto fill_value{ 100001. };
    m_xspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_heights[i][j].first) {
                m_xspeeds_vectors[i][j] = table.item(i, j)->text().toDouble();
            }
        }
    }
    emit xSpeedChanged(m_xspeeds_vectors);
    createShoreBorder(m_xspeeds_vectors);
}

void Computator::getYSpeedsFromTable(QTableWidget &table)
{
    auto nrows{ m_heights.size() };
    auto ncols{ nrows > 0 ? m_heights[0].size() : 0 };

    m_yspeeds_vectors.clear();
    const auto fill_value{ 100001. };
    m_yspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_heights[i][j].first) {
                m_yspeeds_vectors[i][j] = table.item(i, j)->text().toDouble();
            }
        }
    }

    emit ySpeedChanged(m_yspeeds_vectors);
    createShoreBorder(m_yspeeds_vectors);
}

void Computator::createShoreBorder(QVector<QVector<double>> &area)
{
    if(area.size() == 0) return;

    auto nrows{ area.size() + 2 };
    auto ncols{ area[0].size() + 2 };

    // copy the source table
    QVector<QVector<double>> bordered_area(nrows, QVector<double>(ncols, 100001.));
    for(int i{ 1 }; i < nrows - 1; ++i) {
        for(int j{ 1 }; j < ncols - 1; ++j) {
            bordered_area[i][j] = area[i - 1][j - 1];
        }
    }

    // copy first and last rows
    QVector<QPair<int, int>> wo_shore_indexes;
    for(int i{ 1 }; i < ncols - 1; ++i) {
        bordered_area[0][i] = area[0][i - 1];
        bordered_area[nrows - 1][i] = area[nrows - 3][i - 1];
        wo_shore_indexes.append(qMakePair(0, i));
        wo_shore_indexes.append(qMakePair(nrows - 1, i));
    }

    QVector<QPair<int, int>> islands_shore_indexes;
    auto cmp = [](const QPair<int, int> &first, const QPair<int, int> &second)->bool { return first.first == second.first && first.second == second.second; };
    // copy first and last nonzero cells
    constexpr auto fill_value{ 100001. };
    constexpr auto error{ -1. };

    for(int i{ 1 }; i < nrows - 1; ++i) {
        int first_nonshore{};
        for(int j{}; j < ncols - 2; ++j) {
            if(area[i - 1][j] - fill_value < error) {
                first_nonshore = j;
                bordered_area[i][j] = area[i - 1][j];
                wo_shore_indexes.append(qMakePair(i, j));
                break;
            }
        }

        int last_nonshore{};
        for(int j{ ncols - 3 }; j > 0; --j) {
            if(area[i - 1][j] - fill_value < error) {
                last_nonshore = j;
                bordered_area[i][j + 2] = area[i - 1][j];
                wo_shore_indexes.append(qMakePair(i, j + 2));
                break;
            }
        }

        ++last_nonshore;
        for(int j{ first_nonshore }; j < last_nonshore; ++j) {
            if(bordered_area[i][j] - fill_value > error) {
                if(bordered_area[i][j - 1] - fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i, j - 1))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i][j - 1]; // CHECKME
                }
                else if(bordered_area[i][j + 1] - fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i, j + 1))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i][j + 1]; // CHECKME
                }
                else if(i > 0 && bordered_area[i - 1][j] - fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i - 1, j))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i - 1][j]; // CHECKME
                }
                else if(i + 1 < nrows && bordered_area[i + 1][j] - fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i + 1, j))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i + 1][j]; // CHECKME
                }
            }
        }
    }
    islands_shore_indexes.clear();

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(bordered_area[i][j] - fill_value > error) {
                if(i + 1 < nrows && bordered_area[i + 1][j] - fill_value < error && !findInVector(wo_shore_indexes, cmp, qMakePair(i + 1, j))) {
                    bordered_area[i][j] = bordered_area[i + 1][j];
                    wo_shore_indexes.append(qMakePair(i, j));
                }
                else if(i - 1 >= 0 && bordered_area[i - 1][j] - fill_value < error && !findInVector(wo_shore_indexes, cmp, qMakePair(i - 1, j))) {
                    bordered_area[i][j] = bordered_area[i - 1][j];
                    wo_shore_indexes.append(qMakePair(i, j));
                }
            }
        }
    }

    area = std::move(bordered_area);
}

template <class Cmp>
bool Computator::findInVector(const QVector<QPair<int, int>> &vec, const Cmp &cmp, const QPair<int, int> value)
{
    auto vec_size{ vec.size() };
    for(int i{}; i < vec_size; ++i) {
        if(cmp(value, vec[i])) {
            return true;
        }
    }
    return false;
}

void Computator::getXStep(const double step)
{
    m_xstep = step;
}
void Computator::getYStep(const double step)
{
    m_ystep = step;
}
