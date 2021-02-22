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

//    QPair<int, int> first_water_obj_ind{};
//    QPair<int, int> last_water_obj_ind{};

//    // parsing first row of the water objects grid
//    int cur_row = 1;

//    first_water_obj_ind.first = cur_row;
//    last_water_obj_ind.first = cur_row;

//    int heights_row { cur_row - 1 };

//    for(int j{ 1 }; j < ncols - 1; ++j) {
//        int heights_col { j - 1 };

//        if (m_heights[heights_row][heights_col].first) {
//            first_water_obj_ind.second = j;
//            break;
//        }
//    }

//    for(int j{ ncols - 1 }; j > first_water_obj_ind.second; --j) {
//        int heights_col { j - 1 };

//        if (m_heights[heights_row][heights_col].first) {
//            last_water_obj_ind.second = j;
//            break;
//        }
//    }

//    m_xspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1] = m_xspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second];
//    m_xspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1] = m_xspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second];
//    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
//        m_xspeeds_vectors[first_water_obj_ind.first + 1][j] = m_xspeeds_vectors[first_water_obj_ind.first][j];
//    }
//    // parsing mid part of water objects grid
//    for (int i { 2 }; i < nrows - 2; ++i) {
//        int heights_row { i - 1 };
//        first_water_obj_ind.first = i;
//        for (int j { 1 }; j < nrows - 1; ++j) {
//            int heights_col { j - 1 };

//            if (m_heights[heights_row][heights_col].first) {
//                first_water_obj_ind.second = j;
//                break;
//            }
//        }

//        for(int j{ ncols - 1 }; j > first_water_obj_ind.second; --j) {
//            int heights_col { j - 1 };

//            if (m_heights[heights_row][heights_col].first) {
//                last_water_obj_ind.second = j;
//                break;
//            }
//        }

//        m_xspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1] = m_xspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second];
//        m_xspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1] = m_xspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second];

//        for (int j { first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
//            int heights_col { j - 1 };
//            if(!m_heights[heights_row][heights_col].first) {
//                m_xspeeds_vectors[i][j] = m_xspeeds_vectors[i][j - 1];
//                break;
//            }
//        }

//        for (int j { last_water_obj_ind.second }; j > first_water_obj_ind.second; --j) {
//            int heights_col { j - 1 };
//            if(!m_heights[heights_row][heights_col].first) {
//                m_xspeeds_vectors[i][j] = m_xspeeds_vectors[i][j + 1];
//                break;
//            }
//        }
//    }
//    // parsing last row of water objects grid
//    cur_row = nrows - 1;

//    first_water_obj_ind.first = cur_row;
//    last_water_obj_ind.first = cur_row;

//    heights_row = cur_row - 1;

//    for(int j{ 1 }; j < ncols - 1; ++j) {
//        if (m_heights[nrows - 1][j].first) {
//            first_water_obj_ind.second = j;
//            break;
//        }
//    }

//    for(int j{ ncols - 1 }; j > first_water_obj_ind.second; --j) {
//        if (m_heights[nrows - 1][j].first) {
//             last_water_obj_ind.second = j;
//             break;
//        }
//    }

//    m_xspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1] = m_xspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second];
//    m_xspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1] = m_xspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second];

//    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
//         m_xspeeds_vectors[first_water_obj_ind.first + 1][j] = m_xspeeds_vectors[first_water_obj_ind.first][j];
//    }
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

//    QPair<int, int> first_water_obj_ind{};
//    QPair<int, int> last_water_obj_ind{};

//    // parsing first row of the water objects grid
//    int cur_row = 1;

//    first_water_obj_ind.first = cur_row;
//    last_water_obj_ind.first = cur_row;

//    int heights_row { cur_row - 1 };

//    for(int j{ 1 }; j < ncols - 1; ++j) {
//        int heights_col { j - 1 };

//        if (m_heights[heights_row][heights_col].first) {
//            first_water_obj_ind.second = j;
//            break;
//        }
//    }

//    for(int j{ ncols - 1 }; j > first_water_obj_ind.second; --j) {
//        int heights_col { j - 1 };

//        if (m_heights[heights_row][heights_col].first) {
//            last_water_obj_ind.second = j;
//            break;
//        }
//    }

//    m_yspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1]= m_yspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second];
//    m_yspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1] = m_yspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second];
//    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
//        m_yspeeds_vectors[first_water_obj_ind.first + 1][j] = m_yspeeds_vectors[first_water_obj_ind.first][j];
//    }
//    // parsing mid part of water objects grid
//    for (int i { 2 }; i < nrows - 2; ++i) {
//        int heights_row { i - 1 };
//        first_water_obj_ind.first = i;
//        for (int j { 1 }; j < nrows - 1; ++j) {
//            int heights_col { j - 1 };

//            if (m_heights[heights_row][heights_col].first) {
//                first_water_obj_ind.second = j;
//                break;
//            }
//        }

//        for(int j{ ncols - 1 }; j > first_water_obj_ind.second; --j) {
//            int heights_col { j - 1 };

//            if (m_heights[heights_row][heights_col].first) {
//                last_water_obj_ind.second = j;
//                break;
//            }
//        }

//        m_yspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1] = m_yspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second];
//        m_yspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1] = m_yspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second];

//        for (int j { first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
//            int heights_col { j - 1 };
//            if(!m_heights[heights_row][heights_col].first) {
//                m_yspeeds_vectors[i][j] = m_yspeeds_vectors[i][j - 1];
//                break;
//            }
//        }

//        for (int j { last_water_obj_ind.second }; j > first_water_obj_ind.second; --j) {
//            int heights_col { j - 1 };
//            if(!m_heights[heights_row][heights_col].first) {
//                m_yspeeds_vectors[i][j] = m_yspeeds_vectors[i][j + 1];
//                break;
//            }
//        }
//    }
//    // parsing last row of water objects grid
//    cur_row = nrows - 1;

//    first_water_obj_ind.first = cur_row;
//    last_water_obj_ind.first = cur_row;

//    heights_row = cur_row - 1;

//    for(int j{ 1 }; j < ncols - 1; ++j) {
//        if (m_heights[nrows - 1][j].first) {
//            first_water_obj_ind.second = j;
//            break;
//        }
//    }

//    for(int j{ ncols - 1 }; j > first_water_obj_ind.second; --j) {
//        if (m_heights[nrows - 1][j].first) {
//             last_water_obj_ind.second = j;
//             break;
//        }
//    }

//    m_yspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second - 1] = m_yspeeds_vectors[first_water_obj_ind.first][first_water_obj_ind.second];
//    m_yspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second + 1] = m_yspeeds_vectors[last_water_obj_ind.first][last_water_obj_ind.second];

//    for (int j{ first_water_obj_ind.second }; j < last_water_obj_ind.second; ++j) {
//         m_yspeeds_vectors[first_water_obj_ind.first + 1][j] = m_yspeeds_vectors[first_water_obj_ind.first][j];
//    }
}
