#include "computator.hpp"

#include <QTableWidgetItem>
#include <cmath>

Computator::Computator() :
    QObject{},
    m_heights{},
    m_x_speed_vector_table_container{ new TableContainer(QString("Таблица значений проекций скорости на OX")) },
    m_y_speed_vector_table_container{ new TableContainer(QString("Таблица значений проекций скорости на OY")) },
    m_wo_type{ WaterObjectType::river },
    m_az_ratio{ 0.001 }
{
    connect(m_x_speed_vector_table_container->getTableWidget(), SIGNAL(closeSignal(TableWidget*)),
            this, SLOT(setupXSpeedVectors(TableWidget*)));
    connect(m_y_speed_vector_table_container->getTableWidget(), SIGNAL(closeSignal(TableWidget*)),
            this, SLOT(setupYSpeedVectors(TableWidget*)));
}

Computator::~Computator()
{
    delete m_y_speed_vector_table_container;
    delete m_x_speed_vector_table_container;
}


void Computator::setXTanPressure(){
    auto rows{ m_xyspeeds_vectors.size() };
    auto cols{ rows > 0 ? m_xyspeeds_vectors[0].size() : 0 };

    if(m_xytan_pressure_vectors.size() == 0) {
        m_xytan_pressure_vectors.resize(rows);
        for(int i{}; i < rows; ++i) {
           m_xytan_pressure_vectors[i].resize(cols);
        }
    }

    for(int i{ 1 }; i < rows - 1; ++i) {
        for(int j{ 1 }; j < cols - 1; ++j) {
            m_xytan_pressure_vectors[i][j].first = m_gamma * m_xyspeeds_vectors[i][j].first * std::abs(m_xyspeeds_vectors[i][j].first);
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

void Computator::displayXYSpeedVectorTableWidgets()
{
    // clear old content
    auto x_table{ m_x_speed_vector_table_container->getTableWidget() };
    x_table->clear();

    auto y_table{ m_y_speed_vector_table_container->getTableWidget() };
    y_table->clear();

    auto rows{ m_heights.size() + 1};
    auto cols{ rows > 0 ? m_heights[0].size() + 1 : 0 };
    x_table->setRowCount(rows);
    x_table->setColumnCount(cols);
    y_table->setRowCount(rows);
    y_table->setColumnCount(cols);

    if(m_xyspeeds_vectors.size() > 0) {
        for(int i{}; i < rows; ++i) {
            for(int j{}; j < cols; ++j) {
                if(m_heights[i][j].first) {
                    auto x_item{ new QTableWidgetItem };
                    x_item->setText(QString("%1").arg(m_xyspeeds_vectors[i][j].first));
                    x_item->setBackground(QBrush(Qt::cyan));
                    x_item->setTextAlignment(Qt::AlignCenter);
                    x_table->setItem(i, j, x_item);

                    auto y_item{ new QTableWidgetItem };
                    y_item->setText(QString("%1").arg(m_xyspeeds_vectors[i][j].second));
                    y_item->setBackground(QBrush(Qt::cyan));
                    y_item->setTextAlignment(Qt::AlignCenter);
                    y_table->setItem(i, j, y_item);
                }
            }
        }
    }
    else {
        for(int i{}; i < rows; ++i) {
            for(int j{}; j < cols; ++j) {
                if(m_heights[i][j].first) {
                    auto x_item{ new QTableWidgetItem };
                    x_item->setText("-1");
                    x_item->setBackground(QBrush(Qt::cyan));
                    x_item->setTextAlignment(Qt::AlignCenter);
                    x_table->setItem(i, j, x_item);

                    auto y_item{ new QTableWidgetItem };
                    y_item->setText("-1");
                    y_item->setBackground(QBrush(Qt::cyan));
                    y_item->setTextAlignment(Qt::AlignCenter);
                    y_table->setItem(i, j, y_item);
                }
            }
        }
    }

    m_x_speed_vector_table_container->show();
    m_x_speed_vector_table_container->activateWindow();

    m_y_speed_vector_table_container->show();
    m_y_speed_vector_table_container->activateWindow();
}

void Computator::setupXSpeedVectors(TableWidget *table)
{
    auto rows{ m_heights.size() + 1 };
    auto cols{ rows > 0 ? m_heights[0].size() + 1 : 0 };

    if(m_xyspeeds_vectors.size() == 0) {
        m_xyspeeds_vectors.resize(rows);
        for(int i{}; i < rows; ++i) {
            m_xyspeeds_vectors[i].resize(cols);
        }
    }

    bool convertion_flag{};
    for(int i{ 1 }; i < rows - 1; ++i) {
        int heights_row { i - 1 }; // Convertion to heights grid indexation (rows)

        for(int j{ 1 }; j < cols - 1; ++j) {
            int heights_col { j - 1 }; // Convertion to heights grid indexation (collumns)

            if(m_heights[heights_row][heights_col].first) {
                if(auto value{ table->item(i, j)->text().toDouble(&convertion_flag) }; convertion_flag) {
                    m_xyspeeds_vectors[i][j].first = value;
                }
            }
        }
    }

    QPair<int, int> first_water_obj_ind{};
    QPair<int, int> last_water_obj_ind{};

    // parsing first row of the water objects grid
    int cur_row = 1;

    first_water_obj_ind.first = cur_row;
    last_water_obj_ind.first = cur_row;

    int heights_row { cur_row - 1 };

    for(int j{ 1 }; j < cols - 1; ++j) {
        int heights_col { j - 1 };

        if (m_heights[heights_row][heights_col].first) {
            first_water_obj_ind.second = j;
            break;
        }
    }

    for(int j{ cols - 1 }; j > first_water_obj_ind.second; --j) {
        int heights_col { j - 1 };

        if (m_heights[heights_row][heights_col].first) {
            last_water_obj_ind.second = j;
            break;
        }
    }

    m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1].first = m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second].first;
    m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1].first = m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second].first;
    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
        m_xyspeeds_vectors[first_water_obj_ind.first + 1][j].first = m_xyspeeds_vectors[first_water_obj_ind.first][j].first;
    }
    // parsing mid part of water objects grid
    for (int i { 2 }; i < rows - 2; ++i) {
        int heights_row { i - 1 };
        first_water_obj_ind.first = i;
        for (int j { 1 }; j < rows - 1; ++j) {
            int heights_col { j - 1 };

            if (m_heights[heights_row][heights_col].first) {
                first_water_obj_ind.second = j;
                break;
            }
        }

        for(int j{ cols - 1 }; j > first_water_obj_ind.second; --j) {
            int heights_col { j - 1 };

            if (m_heights[heights_row][heights_col].first) {
                last_water_obj_ind.second = j;
                break;
            }
        }

        m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1].first = m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second].first;
        m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1].first = m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second].first;

        for (int j { first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
            int heights_col { j - 1 };
            if(!m_heights[heights_row][heights_col].first) {
                m_xyspeeds_vectors[i][j].first = m_xyspeeds_vectors[i][j - 1].first;
                break;
            }
        }

        for (int j { last_water_obj_ind.second }; j > first_water_obj_ind.second; --j) {
            int heights_col { j - 1 };
            if(!m_heights[heights_row][heights_col].first) {
                m_xyspeeds_vectors[i][j].first = m_xyspeeds_vectors[i][j + 1].first;
                break;
            }
        }
    }
    // parsing last row of water objects grid
    cur_row = rows - 1;

    first_water_obj_ind.first = cur_row;
    last_water_obj_ind.first = cur_row;

    heights_row = cur_row - 1;

    for(int j{ 1 }; j < cols - 1; ++j) {
        if (m_heights[rows - 1][j].first) {
            first_water_obj_ind.second = j;
            break;
        }
    }

    for(int j{ cols - 1 }; j > first_water_obj_ind.second; --j) {
        if (m_heights[rows - 1][j].first) {
             last_water_obj_ind.second = j;
             break;
        }
    }

    m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1].first = m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second].first;
    m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1].first = m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second].first;

    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
         m_xyspeeds_vectors[first_water_obj_ind.first + 1][j].first = m_xyspeeds_vectors[first_water_obj_ind.first][j].second;
    }
}

void Computator::setupYSpeedVectors(TableWidget *table)
{
    auto rows{ m_heights.size() + 1 };
    auto cols{ rows > 0 ? m_heights[0].size() + 1 : 0 };

    if(m_xyspeeds_vectors.size() == 0) {
        m_xyspeeds_vectors.resize(rows);
        for(int i{}; i < rows; ++i) {
            m_xyspeeds_vectors[i].resize(cols);
        }
    }

    bool convertion_flag{};
    for(int i{ 1 }; i < rows - 1; ++i) {
        int heights_row { i - 1 }; // Convertion to heights grid indexation (rows)

        for(int j{ 1 }; j < cols - 1; ++j) {
            int heights_col { j - 1 }; // Convertion to heights grid indexation (collumns)

            if(m_heights[heights_row][heights_col].first) {
                if(auto value{ table->item(i, j)->text().toDouble(&convertion_flag) }; convertion_flag) {
                    m_xyspeeds_vectors[i][j].second = value;
                }
            }
        }
    }

    QPair<int, int> first_water_obj_ind{};
    QPair<int, int> last_water_obj_ind{};

    // parsing first row of the water objects grid
    int cur_row = 1;

    first_water_obj_ind.first = cur_row;
    last_water_obj_ind.first = cur_row;

    int heights_row { cur_row - 1 };

    for(int j{ 1 }; j < cols - 1; ++j) {
        int heights_col { j - 1 };

        if (m_heights[heights_row][heights_col].first) {
            first_water_obj_ind.second = j;
            break;
        }
    }

    for(int j{ cols - 1 }; j > first_water_obj_ind.second; --j) {
        int heights_col { j - 1 };

        if (m_heights[heights_row][heights_col].first) {
            last_water_obj_ind.second = j;
            break;
        }
    }

    m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1].second = m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second].second;
    m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1].second = m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second].second;
    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
        m_xyspeeds_vectors[first_water_obj_ind.first + 1][j].second = m_xyspeeds_vectors[first_water_obj_ind.first][j].second;
    }
    // parsing mid part of water objects grid
    for (int i { 2 }; i < rows - 2; ++i) {
        int heights_row { i - 1 };
        first_water_obj_ind.first = i;
        for (int j { 1 }; j < rows - 1; ++j) {
            int heights_col { j - 1 };

            if (m_heights[heights_row][heights_col].first) {
                first_water_obj_ind.second = j;
                break;
            }
        }

        for(int j{ cols - 1 }; j > first_water_obj_ind.second; --j) {
            int heights_col { j - 1 };

            if (m_heights[heights_row][heights_col].first) {
                last_water_obj_ind.second = j;
                break;
            }
        }

        m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1].second = m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second].second;
        m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1].second = m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second].second;

        for (int j { first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
            int heights_col { j - 1 };
            if(!m_heights[heights_row][heights_col].first) {
                m_xyspeeds_vectors[i][j].second = m_xyspeeds_vectors[i][j - 1].second;
                break;
            }
        }

        for (int j { last_water_obj_ind.second }; j > first_water_obj_ind.second; --j) {
            int heights_col { j - 1 };
            if(!m_heights[heights_row][heights_col].first) {
                m_xyspeeds_vectors[i][j].second = m_xyspeeds_vectors[i][j + 1].second;
                break;
            }
        }
    }
    // parsing last row of water objects grid
    cur_row = rows - 1;

    first_water_obj_ind.first = cur_row;
    last_water_obj_ind.first = cur_row;

    heights_row = cur_row - 1;

    for(int j{ 1 }; j < cols - 1; ++j) {
        if (m_heights[rows - 1][j].first) {
            first_water_obj_ind.second = j;
            break;
        }
    }

    for(int j{ cols - 1 }; j > first_water_obj_ind.second; --j) {
        if (m_heights[rows - 1][j].first) {
             last_water_obj_ind.second = j;
             break;
        }
    }

    m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1].second = m_xyspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second].second;
    m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1].second = m_xyspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second].second;

    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
         m_xyspeeds_vectors[first_water_obj_ind.first + 1][j].second = m_xyspeeds_vectors[first_water_obj_ind.first][j].second;
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
