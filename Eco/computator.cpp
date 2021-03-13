#include "computator.hpp"

#include <QMessageBox>
#include <cmath>
#include <QPainter>

// third party functions
void showErrorMessageBox(const QString &msg, const QString &title = "");


// ctors and dtor
Computator::Computator() :
    QObject{},
    m_grid_ptr{},
    m_heights_ptr{},
    m_xspeeds_vectors{},
    m_yspeeds_vectors{},
    m_horizon{ 1. },
    m_wo_type{ WaterObjectType::River },
    m_az_ratio{ 0.001 },
    m_ksi_atol{ 1. },
    m_max_computation_distance{ 500. },
    m_wind_direction{ WindDirection::North, false },
    m_wind_azimuth{ 0., true },
    m_absolute_speed{ 10. },
    m_mark_index{ }
{
    // PASS
}

Computator::~Computator()
{

}


// public slots
void Computator::setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    m_mark_index.clear();
    m_grid_ptr = nullptr;

    auto nrows{ grid.size() };
    if(nrows == 0)  return;
    auto ncols{ grid[0].size() };
    if(ncols == 0)  return;
    m_grid_ptr = &grid;

    m_sources.clear();
    m_heights_ptr = nullptr;

    decomposeAbsSpeed();
}

void Computator::setupHeights(const QVector<QVector<QPair<bool, double>>> &heights)
{
    m_heights_ptr = nullptr;
    auto nrows{ heights.size() };
    if(nrows == 0)  return;
    auto ncols{ heights[0].size() };
    if(ncols == 0)  return;

    m_heights_ptr = &heights;
}

void Computator::setWOType(int index) noexcept
{
    Q_ASSERT_X(index >= static_cast<int>(WaterObjectType::MIN) && index <= static_cast<int>(WaterObjectType::MAX),
               "Class - Computator", "Function - setWOType, wrong water object index");
    m_wo_type = static_cast<WaterObjectType>(index);
}

void Computator::acceptXSpeedsFromTable(QTableWidget &table)
{
    m_xspeeds_vectors.clear();

    if(!m_heights_ptr) return;
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    m_xspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_heights_ptr)[i][j].first) {
                m_xspeeds_vectors[i][j] = table.item(i, j)->text().toDouble();               
            }
        }
    }
}

void Computator::acceptYSpeedsFromTable(QTableWidget &table)
{
    m_yspeeds_vectors.clear();

    if(!m_heights_ptr) return;
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    m_yspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_heights_ptr)[i][j].first) {
                m_yspeeds_vectors[i][j] = table.item(i, j)->text().toDouble();                
            }
        }
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

    if(source.index() == 0) {
        emit sourcesChanged(std::get<PointSource>(source), matters);
    }
    else {
        emit sourcesChanged(std::get<DiffusionSource>(source), matters);
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

void Computator::decomposeAbsSpeed()
{
    static constexpr double pi{ 3.141592653589793 };

    m_xspeeds_vectors.clear();
    m_yspeeds_vectors.clear();

    if(!m_heights_ptr) return;
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    m_xspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);
    m_yspeeds_vectors.fill(QVector<double>(ncols, fill_value), nrows);

    auto fill = [&nrows, &ncols, this](double degrees) mutable {
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                if((*m_heights_ptr)[i][j].first) {
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

    emit xWindProjectionChanged(m_xspeeds_vectors);
    emit yWindProjectionChanged(m_yspeeds_vectors);
}

void Computator::computateSpeeds() const
{
    // HERE MUST BE SPEED CHECKING

    if(m_wo_type != WaterObjectType::Lake) {
        showErrorMessageBox("Внимание! Некорректный водный объект!\nРасчеты проводятся только для озер", "Ошибка водный объект");
        return;
    }

    // FIXME: error message?
    if(!m_heights_ptr) {
        showErrorMessageBox("Высоты не заданы.\nЗаполните поля высот.");
        return;
    }
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    auto xtan_pressure_vectors{ computateXTanPressure() };
    auto ytan_pressure_vectors{ computateYTanPressure() };

    auto rot_t_vectors{ computateRotT(xtan_pressure_vectors, ytan_pressure_vectors) };
    auto f0_vectors{ computateF0(rot_t_vectors) };

    // ksi computating
    auto average_error = [](const QVector<QVector<double>> &first, const QVector<QVector<double>> &second) {
        auto nrows{ first.size() };
        auto ncols{ first[0].size() };
        double average{};
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                average += std::fabs(std::fabs(second[i][j] - first[i][j]) / first[i][j]);
            }
        }
        return average / (nrows * ncols);
    };

    auto ksi0{ f0_vectors };
    auto ksi{ computateKsi(ksi0, f0_vectors) };
    while(average_error(ksi, ksi0) * 100. > m_ksi_atol) { // * 100 - from relative to percents
        ksi0 = std::move(ksi);
        ksi = computateKsi(ksi0, f0_vectors);
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_heights_ptr)[i][j].first) {
                ksi[i][j] *= (*m_heights_ptr)[i][j].second;
            }
        }
    }

    auto ux_speed{ computateU(ksi, xtan_pressure_vectors) };
    emit uxSpeedChanged(ux_speed);

    auto uy_speed{ computateV(ksi, ytan_pressure_vectors) };
    emit uySpeedChanged(uy_speed);

    auto u0x_speed{ computateU0(ksi, xtan_pressure_vectors) };
    emit u0xSpeedChanged(u0x_speed);

    auto u0y_speed{ computateV0(ksi, ytan_pressure_vectors) };
    emit u0ySpeedChanged(u0y_speed);

    auto computate_vectors = [this](const QVector<QVector<double>> &xprojection,
            const QVector<QVector<double>> &yprojection) -> QVector<QVector<double>> {
        auto nrows{ xprojection.size() };
        auto ncols{ xprojection[0].size() };

        QVector<QVector<double>> result(nrows, QVector<double>(ncols, fill_value));
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                if((*m_heights_ptr)[i][j].first) {
                    result[i][j] = std::sqrt(std::pow(xprojection[i][j], 2) + std::pow(yprojection[i][j], 2));
                }
            }
        }

        return result;
    };

    auto u{ computate_vectors(ux_speed, uy_speed) };
    auto u0{ computate_vectors(u0x_speed, u0y_speed) };

    emit uChanged(u);
    emit u0Changed(u0);

    auto pm{ createFlowMap(ux_speed, uy_speed, u0x_speed, u0y_speed) };
    emit flowMapCreated(pm);

    QMessageBox::about(nullptr, "Действие завершено", "Значения рассчитаны");
    emit speedsComputated();
}


// private functions
QVector<QVector<double>> Computator::computateXTanPressure() const
{
    // range check must be in caller function
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    QVector<QVector<double>> xtan_pressure_vectors(nrows, QVector<double>(ncols, fill_value));

    auto xspeeds_vectors{ createShoreBorder(m_xspeeds_vectors) };

    for(int i{}; i < nrows; ++i){
        for(int j{}; j < ncols; ++j){
            if ((*m_heights_ptr)[i][j].first)
                xtan_pressure_vectors[i][j] = m_gamma * xspeeds_vectors[i + 1][j + 1] * std::abs(xspeeds_vectors[i + 1][j + 1]);
        }
    }

    return xtan_pressure_vectors;
}

QVector<QVector<double>> Computator::computateYTanPressure() const
{
    // range check must be in caller function
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    QVector<QVector<double>> ytan_pressure_vectors(nrows, QVector<double>(ncols, fill_value));

    auto yspeeds_vectors{ createShoreBorder(m_yspeeds_vectors) };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if ((*m_heights_ptr)[i][j].first)
                ytan_pressure_vectors[i][j] = m_gamma * yspeeds_vectors[i + 1][j + 1] * std::abs(yspeeds_vectors[i + 1][j + 1]);
        }
    }

    return ytan_pressure_vectors;
}

QVector<QVector<double>> Computator::computateRotT(const QVector<QVector<double>> &xtan_pressures, const QVector<QVector<double>> &ytan_pressures) const
{
    // range check must be in caller function
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    QVector<QVector<double>> rot_vectors(nrows, QVector<double>(ncols, fill_value));
    auto local_xtan_pressures{ createShoreBorder(xtan_pressures) };
    auto local_ytan_pressures{ createShoreBorder(ytan_pressures) };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if ((*m_heights_ptr)[i][j].first) {
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
    // range check must be in caller function
    auto nrows{ (*m_heights_ptr).size() };
    auto ncols{ (*m_heights_ptr)[0].size() };

    auto local_rot_vectors{ createShoreBorder(rot_vectors) };

    QVector<QVector<double>> f0_vectors(nrows, QVector<double>(ncols, fill_value));

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_heights_ptr)[i][j].first) {
                f0_vectors[i][j] = local_rot_vectors[i + 1][j + 1] * 200.0 * m_xstep / m_gamma;
            }
        }
    }

    return f0_vectors;
}

QVector<QVector<double>> Computator::computateKsi(const QVector<QVector<double>> &last_ksi, const QVector<QVector<double>> &f0) const
{
    // range check must be in caller function
    const auto nrows{ last_ksi.size() };
    const auto ncols{ last_ksi[0].size() };

    QVector<QVector<double>> ksi(nrows, QVector<double>(ncols, fill_value));
    for(int i{ 1 }; i < nrows - 1; ++i) {
        for(int j{ 1 }; j < ncols - 1; ++j) {
            if((*m_heights_ptr)[i][j].first) {
                double left{};
                double right{};
                double up{};
                double down{};

                if((*m_heights_ptr)[i - 1][j].first)   up      = last_ksi[i - 1][j];
                if((*m_heights_ptr)[i][j - 1].first)   left    = last_ksi[i][j - 1];
                if((*m_heights_ptr)[i][j + 1].first)   right   = last_ksi[i][j + 1];
                if((*m_heights_ptr)[i + 1][j].first)   down    = last_ksi[i + 1][j];

                ksi[i][j] = (up + left + right + down) / 4. - f0[i][j];
            }
        }
    }

    if((*m_heights_ptr)[0][0].first) {
        double up{};
        double right{};
        if((*m_heights_ptr)[1][0].first)   up      = last_ksi[1][0];
        if((*m_heights_ptr)[0][1].first)   right   = last_ksi[0][1];
        ksi[0][0] = (up + right) / 4. - f0[0][0];
    }

    if((*m_heights_ptr)[0][ncols - 1].first) {
        double down{};
        double left{};
        if((*m_heights_ptr)[1][ncols - 1].first)   down = last_ksi[1][ncols - 1];
        if((*m_heights_ptr)[0][ncols - 2].first)   left = last_ksi[0][ncols - 2];

        ksi[0][ncols - 1] = (down + left) / 4. - f0[0][ncols - 1];
    }

    if((*m_heights_ptr)[nrows - 1][0].first) {
        double right{};
        double up{};
        if((*m_heights_ptr)[nrows - 1][1].first)   right = last_ksi[nrows - 1][1];
        if((*m_heights_ptr)[nrows - 2][0].first)   up    = last_ksi[nrows - 2][0];
        ksi[nrows - 1][0] = (right + up) / 4. - f0[nrows - 1][0];
    }

    if((*m_heights_ptr)[nrows - 1][ncols - 1].first) {
        double left{};
        double up{};
        if((*m_heights_ptr)[nrows - 1][ncols - 2].first)   left = last_ksi[nrows - 1][ncols - 2];
        if((*m_heights_ptr)[nrows - 2][ncols - 1].first)   up   = last_ksi[nrows - 2][ncols - 1];
        ksi[nrows - 1][ncols - 1] = (left + up) / 4. - f0[nrows - 1][ncols - 1];
    }

    for(int j{ 1 }; j < ncols - 1; ++j) {
        if((*m_heights_ptr)[0][j].first) {
            double left{};
            double right{};
            double down{};
            if((*m_heights_ptr)[0][j - 1].first)   left  = last_ksi[0][j - 1];
            if((*m_heights_ptr)[0][j + 1].first)   right = last_ksi[0][j + 1];
            if((*m_heights_ptr)[1][j].first)       down  = last_ksi[1][j];
            ksi[0][j] = (left + right + down) / 4. - f0[0][j];
        }
    }

    for(int j{ 1 }; j < ncols - 1; ++j) {
        if((*m_heights_ptr)[nrows - 1][j].first) {
            double left{};
            double right{};
            double up{};
            if((*m_heights_ptr)[nrows - 1][j - 1].first)   left  = last_ksi[nrows - 1][j - 1];
            if((*m_heights_ptr)[nrows - 1][j + 1].first)   right = last_ksi[nrows - 1][j + 1];
            if((*m_heights_ptr)[nrows - 2][j].first)       up    = last_ksi[nrows - 2][j];
            ksi[nrows - 1][j] = (left + right + up) / 4. - f0[nrows - 1][j];
        }
    }

    for(int i{ 1 }; i < nrows - 1; ++i) {
        if((*m_heights_ptr)[i][0].first) {
            double up{};
            double down{};
            double right{};
            if((*m_heights_ptr)[i - 1][0].first)   up    = last_ksi[i - 1][0];
            if((*m_heights_ptr)[i + 1][0].first)   down  = last_ksi[i + 1][0];
            if((*m_heights_ptr)[i][1].first)       right = last_ksi[i][1];
            ksi[i][0] = (up + down + right) / 4. - f0[i][0];
        }
    }

    for(int i{ 1 }; i < nrows - 1; ++i) {
        if((*m_heights_ptr)[i][ncols - 1].first) {
            double up{};
            double down{};
            double left{};
            if((*m_heights_ptr)[i - 1][ncols - 1].first)   up   = last_ksi[i - 1][ncols - 1];
            if((*m_heights_ptr)[i + 1][ncols - 1].first)   down = last_ksi[i + 1][ncols - 1];
            if((*m_heights_ptr)[i][ncols - 2].first)       left = last_ksi[i][ncols - 2];
            ksi[i][ncols - 1] = (up + down + left) / 4. - f0[i][ncols - 1];
        }
    }
    return ksi;
}

QVector<QVector<double>> Computator::computateU(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &xtan) const
{
    // range check must be in caller function
    const auto nrows{ ksi.size() };
    const auto ncols{ ksi[0].size() };

    auto local_ksi{ createShoreBorder(ksi) };
    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, fill_value));

    for(int i{ 1 }; i <= nrows; ++i) {
        for(int j{ 1 }; j <= ncols; ++j) {
            if((*m_heights_ptr)[i - 1][j - 1].first) {
                // all values for computating must be created by createShoreBorder
                double height{ (*m_heights_ptr)[i - 1][j - 1].second };
                speeds[i - 1][j - 1] =(3. * (height * height - m_horizon * m_horizon) * (local_ksi[i][j + 1] - local_ksi[i][j - 1])) /
                        (4. * height * height * height) + xtan[i - 1][j - 1] / (4. * m_az_ratio) * (height * height - 4 * height * m_horizon
                                                                                                                 + 3 * m_horizon * m_horizon);
            }
        }
    }

    return speeds;
}

QVector<QVector<double>> Computator::computateV(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &ytan) const
{
    // range check must be in caller function
    const auto nrows{ ksi.size() };
    const auto ncols{ ksi[0].size() };

    auto local_ksi{ createShoreBorder(ksi) };
    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, fill_value));

    for(int i{ 1 }; i <= nrows; ++i) {
        for(int j{ 1 }; j <= ncols; ++j) {
            if((*m_heights_ptr)[i - 1][j - 1].first) {
                // all values for computating must be created by createShoreBorder
                double height{ (*m_heights_ptr)[i - 1][j - 1].second };
                speeds[i - 1][j - 1] =(3. * (height * height - m_horizon * m_horizon) * (local_ksi[i - 1][j] - local_ksi[i + 1][j])) /
                        (4. * height * height * height) + ytan[i - 1][j - 1] / (4. * m_az_ratio) * (height * height - 4 * height * m_horizon
                                                                                                                 + 3 * m_horizon * m_horizon);
            }
        }
    }

    return speeds;
}

// FIXME
QVector<QVector<double>> Computator::computateU0(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &/*xtan*/) const
{
    // range check must be in caller function
    const auto nrows{ ksi.size() };
    const auto ncols{ ksi[0].size() };

    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, fill_value));

    // TODO

    return speeds;
}

// FIXME
QVector<QVector<double>> Computator::computateV0(const QVector<QVector<double>> &ksi, const QVector<QVector<double>> &/*ytan*/) const
{
    // range check must be in caller function
    const auto nrows{ ksi.size() };
    const auto ncols{ ksi[0].size() };

    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, fill_value));

    // TODO

    return speeds;
}

QVector<QVector<double>> Computator::createShoreBorder(const QVector<QVector<double>> &area) const
{
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

// TODO: arrows and legend
QPixmap Computator::createFlowMap(const QVector<QVector<double>> &ux, const QVector<QVector<double>> &uy,
                                  const QVector<QVector<double>> &u0x, const QVector<QVector<double>> &u0y) const
{
    QPixmap pm;
    emit getCurrentMapImage(pm);

    auto nrows{ ux.size() };
    auto ncols{ ux[0].size() };

    auto length = [](double first, double second) -> double {
          return std::sqrt(std::pow(first, 2) + std::pow(second, 2));
    };

    auto pix_x_step{ (*m_grid_ptr)[0][1].second.x() -  (*m_grid_ptr)[0][0].second.x() };
    auto pix_y_step{ (*m_grid_ptr)[1][0].second.y() - (*m_grid_ptr)[0][0].second.y() };
    auto pix_vec{ std::sqrt(std::pow(pix_x_step / 2., 2) + std::pow(pix_y_step / 2., 2)) };

    QPainter painter;
    painter.begin(&pm);
    painter.setPen(QPen(Qt::black, 1.));

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_heights_ptr)[i][j].first) {
                if((*m_heights_ptr)[i][j].second > m_horizon) {
                    auto result{ length(ux[i][j], uy[i][j]) };
                    auto sin{ uy[i][j] / result };
                    auto cos{ ux[i][j] / result };

                    if(result <= pix_vec) {
                        painter.drawLine(QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2.,
                                                 (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2.),
                                         QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2 + result * cos,
                                                 (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2. - result * sin));
                    }
                    else {
                        painter.drawLine(QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2., (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2.),
                                         QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2. + pix_vec * cos,
                                                 (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2. - pix_vec * sin));
                    }
                }
                else {
                    auto result{ length(u0x[i][j], u0y[i][j]) };
                    auto sin{ u0y[i][j] / result };
                    auto cos{ u0x[i][j] / result };

                    if(result <= pix_vec) {
                        painter.drawLine(QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2.,
                                                 (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2.),
                                         QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2. + result * cos,
                                                 (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2. - result * sin));
                    }
                    else {
                        painter.drawLine(QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2.,
                                                 (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2.),
                                         QPointF((*m_grid_ptr)[i][j].second.x() + pix_x_step / 2. + pix_vec * cos,
                                                 (*m_grid_ptr)[i][j].second.y() + pix_y_step / 2. - pix_vec * sin));
                    }
                }
            }
        }
    }
    painter.end();

    return pm;
}
