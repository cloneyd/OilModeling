#include "computator.hpp"


Computator::Computator() :
    QObject{},
    m_heights{},
    m_wo_type{ WaterObjectType::river },
    m_az_ratio{ 0.001 }
{

}

Computator::~Computator()
{

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
    if(index_type == 0)
    {
        m_wo_type = WaterObjectType::river;
    }
    else {
        m_wo_type = WaterObjectType::lake;
    }
}

void Computator::setupXSpeedVector(QTableWidget &table)
{
    auto rows{ m_heights.size() };
    auto cols{ rows > 0 ? m_heights[0].size() : 0 };

    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(m_heights[i][j].first) {
                m_xyspeeds_vectors[i][j].first = table.item(i, j)->text().toDouble();
            }
        }
    }
}

void Computator::setupYSpeedVector(QTableWidget &table)
{
    auto rows{ m_heights.size() };
    auto cols{ rows > 0 ? m_heights[0].size() : 0 };

    for(int i{}; i < rows; ++i) {
        for(int j{}; j < cols; ++j) {
            if(m_heights[i][j].first) {
                m_xyspeeds_vectors[i][j].second = table.item(i, j)->text().toDouble();
            }
        }
    }
}
