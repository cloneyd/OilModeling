#include "computator.hpp"

#include <QMessageBox>

// third party functions
void showErrorMessageBox(const QString &msg, const QString &title = "");


// ctors and dtor
Computator::Computator() :
    QObject{},
    m_heights{},
    m_xspeeds_vectors{},
    m_yspeeds_vectors{},
    m_is_xspeeds_entered_flag{},
    m_is_yspeeds_entered_flag{},
    m_u_vectors{},
    m_v_vectors{},
    m_u0_vectors{},
    m_v0_vectors{},
    m_horizon{ 1. },
<<<<<<< Updated upstream
    m_wo_type{ WaterObjectType::river },
    m_az_ratio{ 0.001 }
=======
    m_wo_type{ WaterObjectType::River },
    m_az_ratio{ 0.001 },
    m_ksi_atol{ 1. },
    m_max_computation_distance{ 500. },
    m_wind_direction{ WindDirection::North, false },
    m_wind_azimuth{ 0., true },
    m_absolute_speed{ 10. },
    m_marks_indexes{ },
    m_sources{}
>>>>>>> Stashed changes
{

}

Computator::~Computator()
{

}


// public slots
<<<<<<< Updated upstream
void Computator::setupHeights(const QVector<QVector<QPair<bool, double>>> &heights)
{
    auto rows{ heights.size() };
    if(rows < 1) {
        return;
    }
=======
void Computator::resetSettings()
{
    m_grid_ptr = nullptr;
    m_heights_ptr = nullptr;
    m_xspeeds_vectors.clear();
    m_yspeeds_vectors.clear();
    m_marks_indexes.clear();

    auto nsources{ m_sources.size() };
    for(int i{ nsources - 1 }; i >= 0; --i) {
        deleteSource(i);
    }
}

void Computator::setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    m_grid_ptr = nullptr;
>>>>>>> Stashed changes

    auto cols{ heights[0].size() };
    if(cols < 1) {
        return;
    }

<<<<<<< Updated upstream
    m_heights.resize(rows);
    for(int i{}; i < rows; ++i) {
        m_heights[i].resize(cols);
=======
    m_heights_ptr = nullptr;
>>>>>>> Stashed changes

        for(int j{}; j < cols; ++j) {
            m_heights[i][j] = heights[i][j];
        }
    }

    m_is_xspeeds_entered_flag = false;
    m_is_yspeeds_entered_flag = false;
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
        showErrorMessageBox("Тип водного объекта не опознан", "Ошибка");
    }

}

void Computator::acceptXSpeedsFromTable(QTableWidget &table)
{
    auto nrows{ m_heights.size() };
    auto ncols{ nrows > 0 ? m_heights[0].size() : 0 };

    m_xspeeds_vectors.clear();
    m_xspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_heights[i][j].first) {
                m_xspeeds_vectors[i][j] = table.item(i, j)->text().toDouble();               
            }
        }
    }

    m_is_xspeeds_entered_flag = true;
    emit xSpeedChanged(m_xspeeds_vectors);
}

void Computator::acceptYSpeedsFromTable(QTableWidget &table)
{
    auto nrows{ m_heights.size() };
    auto ncols{ nrows > 0 ? m_heights[0].size() : 0 };

    m_yspeeds_vectors.clear();
    m_yspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_heights[i][j].first) {
                m_yspeeds_vectors[i][j] = table.item(i, j)->text().toDouble();                
            }
        }
    }
<<<<<<< Updated upstream
=======
}

void Computator::updateCoordinates(const QVector<QVector<QPointF>> &coordinates, const QVector<QVector<QPoint>> &sector)
{
    // FIXME: diffusion source?
    m_marks_indexes = sector;
    const auto nsources{ m_sources.size() };
    PointSource *current_source{};
    for(int i{}; i < nsources; ++i) {
        if(m_sources[i].first.index() == 0) {
            current_source = std::addressof(std::get<PointSource>(m_sources[i].first));
        }
        else {
            current_source = std::addressof(std::get<DiffusionSource>(m_sources[i].first));
        }

        current_source->m_x = coordinates[i][0].x();
        current_source->m_y = coordinates[i][0].y();
    }
}


void Computator::acceptWindDirection(const QPair<int, bool> &pair)
{
    auto first{ pair.first };
    auto second{ pair.second };

    Q_ASSERT_X(first >= static_cast<int>(WindDirection::MIN) && first <= static_cast<int>(WindDirection::MAX),
               "Class - Computator", "Function - acceptWindDirection, problem - wrong direction");

    m_wind_direction.first = static_cast<WindDirection>(first);
    m_wind_direction.second = second;
}

void Computator::addNewSource(const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters)
{
    m_sources.append(qMakePair(source, matters));

    auto new_size{ m_sources.size() };
    if(source.index() == 0) {
        auto current_source{ std::get<PointSource>(source) };
        emit sourcesChanged(current_source, matters);
        emit sourcesChanged(new_size, new_size - 1, SourceType::Point, current_source.m_name, { current_source.m_x, current_source.m_y });
    }
    else {
        auto current_source{ std::get<DiffusionSource>(source) };
        emit sourcesChanged(current_source, matters);
        emit sourcesChanged(new_size, new_size - 1, SourceType::Diffusion, current_source.m_name, { current_source.m_x, current_source.m_y });
    }
}

void Computator::updateSource(int index, const std::variant<PointSource, DiffusionSource> &source, const QVector<PolutionMatter> &matters)
{
    m_sources[index] = qMakePair(source, matters);

    if(source.index() == 0) {
        emit sourceUpdated(index, std::get<PointSource>(source), matters);
    }
    else {
        emit sourceUpdated(index, std::get<DiffusionSource>(source), matters);
    }
}

void Computator::deleteLastMarkInSource(int source_index)
{
    PointSource *source{};
    SourceType type{};
    if(m_sources[source_index].first.index() == 0) {
        source = std::addressof(std::get<PointSource>(m_sources[source_index].first));
        type = SourceType::Point;
    }
    else {
        source = std::addressof(std::get<DiffusionSource>(m_sources[source_index].first));
        type = SourceType::Diffusion;
    }

    source->m_x = -1.;
    source->m_y = -1.;
    emit sourcesChanged(m_sources.size(), source_index, type, source->m_name, { source->m_x, source->m_y });
}

void Computator::decomposeAbsSpeed()
{
    m_xspeeds_vectors.clear();
    m_yspeeds_vectors.clear();

    if(!m_grid_ptr) return;
    auto nrows{ (*m_grid_ptr).size() };
    auto ncols{ (*m_grid_ptr)[0].size() };

    m_xspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);
    m_yspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    auto fill = [&nrows, &ncols, this](double degrees) mutable {
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                if((*m_grid_ptr)[i][j].first) {
                    m_xspeeds_vectors[i][j] = m_absolute_speed * std::cos(degrees * pi / 180.); // from radians to degrees
                    m_yspeeds_vectors[i][j] = m_absolute_speed * std::sin(degrees * pi / 180.);
                }
            }
        }
    };

    if(m_wind_azimuth.second) {
        fill(90. -  m_wind_azimuth.first);
    }
    else if(m_wind_direction.second) {
        switch(m_wind_direction.first) {
        case WindDirection::North: // 0. OR 360.
            fill(90.);
            break;

        case WindDirection::Northeast: // 45.
            fill(45.);
            break;

        case WindDirection::East: // 90
            fill(0.);
            break;

        case WindDirection::Southeast: // 135
            fill(-45.);
            break;

        case WindDirection::South: // 180
            fill(-90.);
            break;

        case WindDirection::Southwest: // 225
            fill(-135.);
            break;

        case WindDirection::West: // 270
            fill(-180.);
            break;

        case WindDirection::Northwest: // 325
            fill(-225.);
            break;
        }
    }
>>>>>>> Stashed changes

    m_is_yspeeds_entered_flag = true;
    emit ySpeedChanged(m_yspeeds_vectors);
}

void Computator::computateSpeeds() const
{
    if(m_wo_type != WaterObjectType::lake) {
        showErrorMessageBox("Внимание! Некорректный водный объект!\nРасчеты проводятся только для озер", "Ошибка водный объект");
        return;
    }

    if(!(m_is_xspeeds_entered_flag && m_is_yspeeds_entered_flag)) {
        showErrorMessageBox("Внимание! Значение проекций\nскоростей должны быть проинициализированы!", "Ошибка значений");
        return;
    }

    auto xtan_pressure_vectors{ computateXTanPressure() };
    auto ytan_pressure_vectors{ computateYTanPressure() };

    auto rot_t_vectors{ computateRotT(xtan_pressure_vectors, ytan_pressure_vectors) };
    auto f0_vectors{ computateF0(rot_t_vectors) };

    QMessageBox::about(nullptr, "Действие", "Значения рассчитаны");
}


// private functions
QVector<QVector<double>> Computator::computateXTanPressure() const
{
    auto nrows{ m_heights.size() };
    if(nrows == 0) return QVector<QVector<double>>{};
    auto ncols{ m_heights[0].size() };
    if(ncols == 0) return QVector<QVector<double>>{};

    QVector<QVector<double>> xtan_pressure_vectors(nrows, QVector<double>(ncols, fill_value));

    auto xspeeds_vectors{ createShoreBorder(m_xspeeds_vectors) };

    for(int i{}; i < nrows; ++i){
        for(int j{}; j < ncols; ++j){
            if (m_heights[i][j].first)
                xtan_pressure_vectors[i][j] = m_gamma * xspeeds_vectors[i + 1][j + 1] * std::abs(xspeeds_vectors[i + 1][j + 1]);
        }
    }

    return xtan_pressure_vectors;
}

QVector<QVector<double>> Computator::computateYTanPressure() const
{
    auto nrows{ m_heights.size() };
    if(nrows == 0) return QVector<QVector<double>>{};
    auto ncols{ m_heights[0].size() };
    if(ncols == 0) return QVector<QVector<double>>{};

    QVector<QVector<double>> ytan_pressure_vectors(nrows, QVector<double>(ncols, fill_value));

    auto yspeeds_vectors{ createShoreBorder(m_yspeeds_vectors) };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if (m_heights[i][j].first)
                ytan_pressure_vectors[i][j] = m_gamma * yspeeds_vectors[i + 1][j + 1] * std::abs(yspeeds_vectors[i + 1][j + 1]);
        }
    }

    return ytan_pressure_vectors;
}

QVector<QVector<double>> Computator::computateRotT(const QVector<QVector<double>> &xtan_pressures, const QVector<QVector<double>> &ytan_pressures) const
{
    auto nrows{ m_heights.size() };
    if(nrows == 0)  return QVector<QVector<double>>{};
    auto ncols{ m_heights[0].size() };
    if(ncols == 0)  return QVector<QVector<double>>{};

    QVector<QVector<double>> rot_vectors(nrows, QVector<double>(ncols, fill_value));
    auto local_xtan_pressures{ createShoreBorder(xtan_pressures) };
    auto local_ytan_pressures{ createShoreBorder(ytan_pressures) };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if (m_heights[i][j].first) {
                rot_vectors[i][j] = (1.0 / (2.0 * m_xstep)) * (local_ytan_pressures[i + 1][j + 2] -
                        local_ytan_pressures[i + 1][j] -
                        local_xtan_pressures[i][j + 1] +
                        local_xtan_pressures[i + 2][j + 1]);
            }
        }
    }

    return rot_vectors;
}

QVector<QVector<double>> Computator::computateF0(const QVector<QVector<double>> &rot_vectors) const
{
    auto nrows{ m_heights.size() };
    if(nrows == 0)      return QVector<QVector<double>>{};
    auto ncols{m_heights[0].size() };
    if(ncols == 0)      return QVector<QVector<double>>{};

    auto local_rot_vectors{ createShoreBorder(rot_vectors) };

    QVector<QVector<double>> f0_vectors(nrows, QVector<double>(ncols, fill_value));

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(m_heights[i][j].first) {
                f0_vectors[i][j] = local_rot_vectors[i + 1][j + 1] * 200.0 * m_xstep / m_gamma;
            }
        }
    }

    return f0_vectors;
}

QVector<QVector<double>> Computator::createShoreBorder(const QVector<QVector<double>> &area) const
{
    if(area.size() == 0) return QVector<QVector<double>>{};

    auto nrows{ area.size() + 2 };
    auto ncols{ area[0].size() + 2 };

    // copy the source table
    QVector<QVector<double>> bordered_area(nrows, QVector<double>(ncols, fill_value));
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

   return bordered_area;
}

template <class Cmp>
bool Computator::findInVector(const QVector<QPair<int, int>> &vec, const Cmp &cmp, const QPair<int, int> value) const
{
    auto vec_size{ vec.size() };
    for(int i{}; i < vec_size; ++i) {
        if(cmp(value, vec[i])) {
            return true;
        }
    }
    return false;
}
