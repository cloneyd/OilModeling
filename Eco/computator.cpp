#include "computator.hpp"

// third party functions
void showErrorMessageBox(const QString &msg);


// ctors and dtor
Computator::Computator() :
    QObject{},
    m_heights{},
    m_xspeeds_vectors{},
    m_yspeeds_vectors{},
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
    m_xspeeds_vectors.resize(nrows);

    for(int i{}; i < nrows; ++i) {
    m_xspeeds_vectors[i].resize(ncols);
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
    m_yspeeds_vectors.resize(nrows);

    for(int i{}; i < nrows; ++i) {
        m_yspeeds_vectors[i].resize(ncols);
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

    QVector<QVector<double>> bordered_area(nrows, QVector<double>(ncols));
    for(int i{ 1 }; i < nrows - 1; ++i) {
        for(int j{ 1 }; j < ncols - 1; ++j) {
            bordered_area[i][j] = area[i - 1][j - 1];
        }
    }

    for(int i{ 1 }; i < ncols - 1; ++i) {
        bordered_area[0][i] = area[0][i - 1];
        bordered_area[nrows - 1][i] = area[nrows - 3][i - 1];
    }


    for(int i{ 1 }; i < nrows - 1; ++i) {
        for(int j{}; j < ncols - 2; ++j) {
            if(area[i - 1][j] > 1e-5) {
                 bordered_area[i][j] = area[i - 1][j];
                break;
            }
        }

        for(int j{ ncols - 3 }; j > 0; --j) {
            if(area[i - 1][j] > 1e-5) {
                 bordered_area[i][j + 2] = area[i - 1][j];
                 break;
            }
        }
    }

    // TODO: islands handler
//    auto table{ new QTableWidget };
//    table->setRowCount(nrows);
//    table->setColumnCount(ncols);
//    for(int i{}; i < nrows; ++i) {
//        for(int j{}; j < ncols; ++j) {
//            auto item(new QTableWidgetItem);
//            item->setBackground(Qt::cyan);
//            item->setText(QString(("%1")).arg(bordered_area[i][j]));
//            table->setItem(i, j, item);
//        }
//    }
//    table->show();
}
