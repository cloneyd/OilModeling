// QT
#include <QPainter>

// current project
#include "computator.hpp"

Computator::Computator(QObject *parent) :
    QObject(parent),
    m_pixgrid_ptr{},
    m_depth_ptr{},
    m_xspeeds_vectors{},
    m_yspeeds_vectors{},
    m_xstep{ -1. },
    m_ystep{ -1. },
    m_horizon{ 1. },
    m_wo_type{ WaterObjectType::River },
    m_az_ratio{ 0.001 },
    m_psi_atol {10.},
    m_max_computation_distance{ 500. },
    m_wind_system{ false, WindDirection::North },
    m_azimuth{ true, 0. },
    m_absolute_speed{ 10. },
    m_marks_indexes{},
    m_marks_coordinates{},
    m_sources{}
{ /*PASS*/ }


// public slots
void Computator::acceptGrid(const GridType &pixgrid) noexcept
{
    m_pixgrid_ptr = nullptr;
    m_depth_ptr = nullptr;
    m_marks_indexes.clear();
    m_marks_coordinates.clear();
    m_xspeeds_vectors.clear();
    m_yspeeds_vectors.clear();

    if(pixgrid.size() == 0) return;
    if(pixgrid[0].size() == 0)  return;

    m_pixgrid_ptr = std::addressof(pixgrid);
    decomposeAbsSpeed();
}

void Computator::acceptDepth(const DepthType &depth) noexcept
{
    m_depth_ptr = nullptr;

    if(depth.size() == 0)    return;
    if(depth[0].size() == 0) return;

    m_depth_ptr = std::addressof(depth);
}

void Computator::acceptXSpeedProjections(QVector<QVector<double>> &speeds)
{
    m_xspeeds_vectors.clear();
    auto nrows{ speeds.size() };
    if(nrows == 0) {
        return;
    }

    auto ncols{ speeds[0].size() };
    if(ncols == 0) {
        return;
    }
    Q_ASSERT_X(m_pixgrid_ptr &&
               m_pixgrid_ptr->size() == nrows &&
               (*m_pixgrid_ptr)[0].size() == ncols,
               "Class - Computator", "Function - acceptXSpeedProjections, problem - speed and grid dimensions are not equal");

    m_xspeeds_vectors = std::move(speeds);
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(!(*m_pixgrid_ptr)[i][j].first) {
                m_xspeeds_vectors[i][j] = s_fill_value;
            }
        }
    }
}

void Computator::acceptYSpeedProjections(QVector<QVector<double>> &speeds)
{
    m_yspeeds_vectors.clear();
    auto nrows{ speeds.size() };
    if(nrows == 0) {
        return;
    }

    auto ncols{ speeds[0].size() };
    if(ncols == 0) {
        return;
    }
    Q_ASSERT_X(m_pixgrid_ptr &&
               m_pixgrid_ptr->size() == nrows &&
               (*m_pixgrid_ptr)[0].size() == ncols,
               "Class - Computator", "Function - acceptXSpeedProjections, problem - speed and grid dimensions are not equal");

    m_yspeeds_vectors = std::move(speeds);
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(!(*m_pixgrid_ptr)[i][j].first) {
                m_yspeeds_vectors[i][j] = s_fill_value;
            }
        }
    }
}

void Computator::computateSpeeds(bool *operation_status)
{
    if(m_wo_type != WaterObjectType::Lake) {
        QMessageBox::warning(nullptr, "Некорректный водный объект", "Внимание! Некорректный водный объект!\nРасчеты проводятся только для озер");
        if(operation_status)    *operation_status = false;
        return;
    }

    if(!m_depth_ptr) {
        QMessageBox::warning(nullptr, "Данные не найдены", "Высоты не заданы.\nЗаполните поля высот.");
        if(operation_status)    *operation_status = false;
        return;
    }
    auto nrows{ (*m_depth_ptr).size() };
    auto ncols{ (*m_depth_ptr)[0].size() };

    auto xtan_pressure_vectors{ computateXTanPressure() };
    auto ytan_pressure_vectors{ computateYTanPressure() };
    auto rot_t_vectors{ computateRotT(xtan_pressure_vectors, ytan_pressure_vectors) };
    auto f0_vectors{ computateF0(rot_t_vectors) };

    // psi computating
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

    auto psi0{ f0_vectors };
    auto psi{ computatePsi(psi0, f0_vectors) };
    while(average_error(psi, psi0) * 100. > m_psi_atol) { // * 100 - from relative to percents
        psi0 = std::move(psi);
        psi = computatePsi(psi0, f0_vectors);
    }

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_depth_ptr)[i][j].first) {
                psi[i][j] *= (*m_depth_ptr)[i][j].second;
            }
        }
    }

    auto ux_speed{ computateU(psi, xtan_pressure_vectors) };
    emit uxProjectionsComputated(ux_speed);

    auto uy_speed{ computateV(psi, ytan_pressure_vectors) };
    emit uyProjectionsComputated(uy_speed);

    auto u0x_speed{ computateU0(psi, xtan_pressure_vectors) };
    emit u0xProjectionsComputated(u0x_speed);

    auto u0y_speed{ computateV0(psi, ytan_pressure_vectors) };
    emit u0yProjectionsComputated(u0y_speed);

    auto computate_vectors = [this](const QVector<QVector<double>> &xprojection,
        const QVector<QVector<double>> &yprojection) -> QVector<QVector<double>> {
        auto nrows{ xprojection.size() };
        auto ncols{ xprojection[0].size() };

        QVector<QVector<double>> result(nrows, QVector<double>(ncols, s_fill_value));
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                if((*m_depth_ptr)[i][j].first) {
                    result[i][j] = std::sqrt(std::pow(xprojection[i][j], 2) + std::pow(yprojection[i][j], 2));
                }
            }
        }

        return result;
    };

    auto u{ computate_vectors(ux_speed, uy_speed) };
    auto u0{ computate_vectors(u0x_speed, u0y_speed) };

    emit uComputated(u);
    emit u0Computated(u0);

    auto pm{ createFlowMap(ux_speed, uy_speed, u0x_speed, u0y_speed, u, u0) };
    emit flowMapCreated(pm);

    if(operation_status)    *operation_status = true;
}

void Computator::decomposeAbsSpeed(bool *operation_status)
{
    m_xspeeds_vectors.clear();
    m_yspeeds_vectors.clear();

    if(!m_pixgrid_ptr) {
        if(operation_status)    *operation_status = false;
        return;
    }
    auto nrows{ (*m_pixgrid_ptr).size() };
    auto ncols{ (*m_pixgrid_ptr)[0].size() };

    m_xspeeds_vectors.fill(QVector<double>(ncols, s_fill_value), nrows);
    m_yspeeds_vectors.fill(QVector<double>(ncols, s_fill_value), nrows);

    auto fill = [&nrows, &ncols, this](double degrees) mutable {
        for(int i{}; i < nrows; ++i) {
            for(int j{}; j < ncols; ++j) {
                if((*m_pixgrid_ptr)[i][j].first) {
                    m_xspeeds_vectors[i][j] = m_absolute_speed * std::cos(degrees * s_pi / 180.); // from radians to degrees
                    m_yspeeds_vectors[i][j] = m_absolute_speed * std::sin(degrees * s_pi / 180.);
                }
            }
        }
    };

    fill(90. - getCurrentAngle());
    emit xProjectionsDecomposed(m_xspeeds_vectors);
    emit yProjectionsDecomposed(m_yspeeds_vectors);
    if(operation_status)    *operation_status = true;
}

// FIXME: #implementme
void Computator::computatePollution(bool */*operation_status*/)
{
    // TODO:
}

void Computator::acceptNewSourcesCoordinates(const QVector<QVector<QPointF>> &coordinates, const QVector<QVector<QPoint>> &indexes)
{
    auto nsources{ m_sources.size() };
    Q_ASSERT_X(coordinates.size() == nsources, "Class - Computator", "Function - acceptNewSourcesCoordinates, problem - wrong marks coordinates size");
    Q_ASSERT_X(indexes.size() == nsources, "Class - Computator", "Function - acceptNewSourcesCoordinates, problem - wrong marks indexes size");
    m_marks_indexes = indexes;
    m_marks_coordinates = coordinates;
    for(int i{}; i < nsources; ++i) { // updating coordinates in sources
        if(m_sources[i].first.index() == 0) {
            auto &ref{ std::get<PointSource>(m_sources[i].first) };
            ref.m_x = coordinates[i].front().x();
            ref.m_y = coordinates[i].front().y();
        }
        else {
            auto &ref{ std::get<DiffusionSource>(m_sources[i].first) };
            ref.m_x = coordinates[i].front().x();
            ref.m_y = coordinates[i].front().y();
        }
    }
}

void Computator::appendNewSource(const PointSource &source, const QVector<PollutionMatter> &matters)
{
    m_sources.append(qMakePair(source, matters)); // marks_indexes and marks_coordinates become invalid;
    // FIXME: sync();
}

void Computator::updateSource(int source_index, const PointSource &source, const QVector<PollutionMatter> &matters)
{
    m_sources[source_index] = qMakePair(source, matters); // marks_indexes and marks_coordinates become invalid;
    // FIXME: sync();
}

void Computator::appendNewSource(const DiffusionSource &source, const QVector<PollutionMatter> &matters)
{
    m_sources.append(qMakePair(source, matters)); // marks_indexes and marks_coordinates become invalid;
    // FIXME: sync();
}

void Computator::updateSource(int source_index, const DiffusionSource &source, const QVector<PollutionMatter> &matters)
{
    m_sources[source_index] = qMakePair(source, matters); // marks_indexes and marks_coordinates become invalid;
    // FIXME: sync();
}

void Computator::giveSourceInfo(int source_index, std::variant<PointSource, DiffusionSource> &will_be_source, QVector<PollutionMatter> &will_be_matters)
{
    will_be_source = m_sources[source_index].first;
    will_be_matters = m_sources[source_index].second;
}


// private functions
QVector<QVector<double>> Computator::computateXTanPressure() const
{
    // range check must be in caller function
    auto nrows{ (*m_depth_ptr).size() };
    auto ncols{ (*m_depth_ptr)[0].size() };

    QVector<QVector<double>> xtan_pressure_vectors(nrows, QVector<double>(ncols, s_fill_value));

    auto xspeeds_vectors{ createShoreBorder(m_xspeeds_vectors) };

    for(int i{}; i < nrows; ++i){
        for(int j{}; j < ncols; ++j){
            if ((*m_depth_ptr)[i][j].first)
                xtan_pressure_vectors[i][j] = s_gamma * xspeeds_vectors[i + 1][j + 1] * std::abs(xspeeds_vectors[i + 1][j + 1]);
        }
    }

    return xtan_pressure_vectors;
}

QVector<QVector<double>> Computator::computateYTanPressure() const
{
    // range check must be in caller function
    auto nrows{ (*m_depth_ptr).size() };
    auto ncols{ (*m_depth_ptr)[0].size() };

    QVector<QVector<double>> ytan_pressure_vectors(nrows, QVector<double>(ncols, s_fill_value));

    auto yspeeds_vectors{ createShoreBorder(m_yspeeds_vectors) };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if ((*m_depth_ptr)[i][j].first)
                ytan_pressure_vectors[i][j] = s_gamma * yspeeds_vectors[i + 1][j + 1] * std::abs(yspeeds_vectors[i + 1][j + 1]);
        }
    }

    return ytan_pressure_vectors;
}

QVector<QVector<double>> Computator::computateRotT(const QVector<QVector<double>> &xtan_pressures, const QVector<QVector<double>> &ytan_pressures) const
{
    // range check must be in caller function
    auto nrows{ (*m_depth_ptr).size() };
    auto ncols{ (*m_depth_ptr)[0].size() };

    QVector<QVector<double>> rot_vectors(nrows, QVector<double>(ncols, s_fill_value));
    auto local_xtan_pressures{ createShoreBorder(xtan_pressures) };
    auto local_ytan_pressures{ createShoreBorder(ytan_pressures) };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if ((*m_depth_ptr)[i][j].first) {
                rot_vectors[i][j] = (1.0 / (2.0 * m_xstep)) * (local_ytan_pressures[i + 1][j + 2] -
                        local_ytan_pressures[i + 1][j] -
                        local_xtan_pressures[i][j + 1] +
                        local_xtan_pressures[i + 2][j + 1]);
            }
        }
    }

    return rot_vectors;
}

QVector<QVector<double>> Computator::computateF0(const QVector<QVector<double>> &rot) const
{
    // range check must be in caller function
    auto nrows{ (*m_depth_ptr).size() };
    auto ncols{ (*m_depth_ptr)[0].size() };

    auto local_rot_vectors{ createShoreBorder(rot) };

    QVector<QVector<double>> f0_vectors(nrows, QVector<double>(ncols, s_fill_value));

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_depth_ptr)[i][j].first) {
                f0_vectors[i][j] = local_rot_vectors[i + 1][j + 1] * 200.0 * m_xstep / s_gamma;
            }
        }
    }

    return f0_vectors;
}

QVector<QVector<double>> Computator::computatePsi(const QVector<QVector<double>> &last_psi, const QVector<QVector<double>> &f0) const
{
    // range check must be in caller function
    const auto nrows{ last_psi.size() };
    const auto ncols{ last_psi[0].size() };

    QVector<QVector<double>> psi(nrows, QVector<double>(ncols, s_fill_value));
    for(int i{ 1 }; i < nrows - 1; ++i) {
        for(int j{ 1 }; j < ncols - 1; ++j) {
            if((*m_depth_ptr)[i][j].first) {
                double left{};
                double right{};
                double up{};
                double down{};

                if((*m_depth_ptr)[i - 1][j].first)   up      = last_psi[i - 1][j];
                if((*m_depth_ptr)[i][j - 1].first)   left    = last_psi[i][j - 1];
                if((*m_depth_ptr)[i][j + 1].first)   right   = last_psi[i][j + 1];
                if((*m_depth_ptr)[i + 1][j].first)   down    = last_psi[i + 1][j];

                psi[i][j] = (up + left + right + down) / 4. - f0[i][j];
            }
        }
    }

    if((*m_depth_ptr)[0][0].first) {
        double up{};
        double right{};
        if((*m_depth_ptr)[1][0].first)   up      = last_psi[1][0];
        if((*m_depth_ptr)[0][1].first)   right   = last_psi[0][1];
        psi[0][0] = (up + right) / 4. - f0[0][0];
    }

    if((*m_depth_ptr)[0][ncols - 1].first) {
        double down{};
        double left{};
        if((*m_depth_ptr)[1][ncols - 1].first)   down = last_psi[1][ncols - 1];
        if((*m_depth_ptr)[0][ncols - 2].first)   left = last_psi[0][ncols - 2];

        psi[0][ncols - 1] = (down + left) / 4. - f0[0][ncols - 1];
    }

    if((*m_depth_ptr)[nrows - 1][0].first) {
        double right{};
        double up{};
        if((*m_depth_ptr)[nrows - 1][1].first)   right = last_psi[nrows - 1][1];
        if((*m_depth_ptr)[nrows - 2][0].first)   up    = last_psi[nrows - 2][0];
        psi[nrows - 1][0] = (right + up) / 4. - f0[nrows - 1][0];
    }

    if((*m_depth_ptr)[nrows - 1][ncols - 1].first) {
        double left{};
        double up{};
        if((*m_depth_ptr)[nrows - 1][ncols - 2].first)   left = last_psi[nrows - 1][ncols - 2];
        if((*m_depth_ptr)[nrows - 2][ncols - 1].first)   up   = last_psi[nrows - 2][ncols - 1];
        psi[nrows - 1][ncols - 1] = (left + up) / 4. - f0[nrows - 1][ncols - 1];
    }

    for(int j{ 1 }; j < ncols - 1; ++j) {
        if((*m_depth_ptr)[0][j].first) {
            double left{};
            double right{};
            double down{};
            if((*m_depth_ptr)[0][j - 1].first)   left  = last_psi[0][j - 1];
            if((*m_depth_ptr)[0][j + 1].first)   right = last_psi[0][j + 1];
            if((*m_depth_ptr)[1][j].first)       down  = last_psi[1][j];
            psi[0][j] = (left + right + down) / 4. - f0[0][j];
        }
    }

    for(int j{ 1 }; j < ncols - 1; ++j) {
        if((*m_depth_ptr)[nrows - 1][j].first) {
            double left{};
            double right{};
            double up{};
            if((*m_depth_ptr)[nrows - 1][j - 1].first)   left  = last_psi[nrows - 1][j - 1];
            if((*m_depth_ptr)[nrows - 1][j + 1].first)   right = last_psi[nrows - 1][j + 1];
            if((*m_depth_ptr)[nrows - 2][j].first)       up    = last_psi[nrows - 2][j];
            psi[nrows - 1][j] = (left + right + up) / 4. - f0[nrows - 1][j];
        }
    }

    for(int i{ 1 }; i < nrows - 1; ++i) {
        if((*m_depth_ptr)[i][0].first) {
            double up{};
            double down{};
            double right{};
            if((*m_depth_ptr)[i - 1][0].first)   up    = last_psi[i - 1][0];
            if((*m_depth_ptr)[i + 1][0].first)   down  = last_psi[i + 1][0];
            if((*m_depth_ptr)[i][1].first)       right = last_psi[i][1];
            psi[i][0] = (up + down + right) / 4. - f0[i][0];
        }
    }

    for(int i{ 1 }; i < nrows - 1; ++i) {
        if((*m_depth_ptr)[i][ncols - 1].first) {
            double up{};
            double down{};
            double left{};
            if((*m_depth_ptr)[i - 1][ncols - 1].first)   up   = last_psi[i - 1][ncols - 1];
            if((*m_depth_ptr)[i + 1][ncols - 1].first)   down = last_psi[i + 1][ncols - 1];
            if((*m_depth_ptr)[i][ncols - 2].first)       left = last_psi[i][ncols - 2];
            psi[i][ncols - 1] = (up + down + left) / 4. - f0[i][ncols - 1];
        }
    }
    return psi;
}

QVector<QVector<double>> Computator::computateU(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &xtan) const
{
    // range check must be in caller function
    const auto nrows{ psi.size() };
    const auto ncols{ psi[0].size() };

    auto local_psi{ createShoreBorder(psi) };
    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, s_fill_value));

    for(int i{ 1 }; i <= nrows; ++i) {
        for(int j{ 1 }; j <= ncols; ++j) {
            if((*m_depth_ptr)[i - 1][j - 1].first) {
                // all values for computating must be created by createShoreBorder
                double depth{ (*m_depth_ptr)[i - 1][j - 1].second };
                speeds[i - 1][j - 1] =(3. * (depth * depth - m_horizon * m_horizon) * (local_psi[i][j + 1] - local_psi[i][j - 1])) /
                        (4. * depth * depth * depth) + xtan[i - 1][j - 1] / (4. * m_az_ratio) * (depth * depth - 4 * depth * m_horizon
                                                                                                                 + 3 * m_horizon * m_horizon);
            }
        }
    }

    return speeds;
}

QVector<QVector<double>> Computator::computateV(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &ytan) const
{
    // range check must be in caller function
    const auto nrows{ psi.size() };
    const auto ncols{ psi[0].size() };

    auto local_psi{ createShoreBorder(psi) };
    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, s_fill_value));

    for(int i{ 1 }; i <= nrows; ++i) {
        for(int j{ 1 }; j <= ncols; ++j) {
            if((*m_depth_ptr)[i - 1][j - 1].first) {
                // all values for computating must be created by createShoreBorder
                double depth{ (*m_depth_ptr)[i - 1][j - 1].second };
                speeds[i - 1][j - 1] =(3. * (depth * depth - m_horizon * m_horizon) * (local_psi[i - 1][j] - local_psi[i + 1][j])) /
                        (4. * depth * depth * depth) + ytan[i - 1][j - 1] / (4. * m_az_ratio) * (depth * depth - 4 * depth * m_horizon
                                                                                                                 + 3 * m_horizon * m_horizon);
            }
        }
    }

    return speeds;
}

QVector<QVector<double>> Computator::computateU0(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &xtan) const
{
    // range check must be in caller function
    const auto nrows{ psi.size() };
    const auto ncols{ psi[0].size() };

    auto local_ksi{ createShoreBorder(psi) };
    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, s_fill_value));

    for(int i{ 1 }; i <= nrows; ++i) {
        for(int j{ 1 }; j <= ncols; ++j) {
            if((*m_depth_ptr)[i - 1][j - 1].first) {
                // all values for computating must be created by createShoreBorder
                double depth{ (*m_depth_ptr)[i - 1][j - 1].second };
                speeds[i - 1][j - 1] = ((3 * (local_ksi[i - 1][j] - local_ksi[i + 1][j])) / (4 * m_xstep * depth)) +
                                       ((xtan[i - 1][j - 1] * depth) / (4 * m_az_ratio));
            }
        }
    }

    return speeds;
}

QVector<QVector<double>> Computator::computateV0(const QVector<QVector<double>> &psi, const QVector<QVector<double>> &ytan) const
{
    // range check must be in caller function
    const auto nrows{ psi.size() };
    const auto ncols{ psi[0].size() };

    auto local_ksi{ createShoreBorder(psi) };
    QVector<QVector<double>> speeds(nrows, QVector<double>(ncols, s_fill_value));

    for(int i{ 1 }; i <= nrows; ++i) {
        for(int j{ 1 }; j <= ncols; ++j) {
            if((*m_depth_ptr)[i - 1][j - 1].first) {
                // all values for computating must be created by createShoreBorder
                double depth{ (*m_depth_ptr)[i - 1][j - 1].second };
                speeds[i - 1][j - 1] = ((3 * (local_ksi[i - 1][j] - local_ksi[i + 1][j])) / (4 * m_ystep * depth)) +
                                       ((ytan[i - 1][j - 1] * depth) / (4 * m_az_ratio));
            }
        }
    }

    return speeds;
}

QVector<QVector<double>> Computator::createShoreBorder(const QVector<QVector<double>> &area) const
{
    auto nrows{ area.size() + 2 };
    auto ncols{ area[0].size() + 2 };

    // copy the source table
    QVector<QVector<double>> bordered_area(nrows, QVector<double>(ncols, s_fill_value));
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
            if(area[i - 1][j] - s_fill_value < error) {
                first_nonshore = j;
                bordered_area[i][j] = area[i - 1][j];
                wo_shore_indexes.append(qMakePair(i, j));
                break;
            }
        }

        int last_nonshore{};
        for(int j{ ncols - 3 }; j > 0; --j) {
            if(area[i - 1][j] - s_fill_value < error) {
                last_nonshore = j;
                bordered_area[i][j + 2] = area[i - 1][j];
                wo_shore_indexes.append(qMakePair(i, j + 2));
                break;
            }
        }

        ++last_nonshore;
        for(int j{ first_nonshore }; j < last_nonshore; ++j) {
            if(bordered_area[i][j] - s_fill_value > error) {
                if(bordered_area[i][j - 1] - s_fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i, j - 1))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i][j - 1];
                }
                else if(bordered_area[i][j + 1] - s_fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i, j + 1))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i][j + 1];
                }
                else if(i > 0 && bordered_area[i - 1][j] - s_fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i - 1, j))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i - 1][j];
                }
                else if(i + 1 < nrows && bordered_area[i + 1][j] - s_fill_value < error && !findInVector(islands_shore_indexes, cmp, qMakePair(i + 1, j))) {
                    islands_shore_indexes.append(qMakePair(i, j));
                    bordered_area[i][j] = bordered_area[i + 1][j];
                }
            }
        }
    }
    islands_shore_indexes.clear();

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(bordered_area[i][j] - s_fill_value > error) {
                if(i + 1 < nrows && bordered_area[i + 1][j] - s_fill_value < error && !findInVector(wo_shore_indexes, cmp, qMakePair(i + 1, j))) {
                    bordered_area[i][j] = bordered_area[i + 1][j];
                    wo_shore_indexes.append(qMakePair(i, j));
                }
                else if(i - 1 >= 0 && bordered_area[i - 1][j] - s_fill_value < error && !findInVector(wo_shore_indexes, cmp, qMakePair(i - 1, j))) {
                    bordered_area[i][j] = bordered_area[i - 1][j];
                    wo_shore_indexes.append(qMakePair(i, j));
                }
            }
        }
    }

   return bordered_area;
}

template <class Cmp>
[[nodiscard]] bool Computator::findInVector(const QVector<QPair<int, int>> &vec, const Cmp &cmp, const QPair<int, int> value) const
{
    auto vec_size{ vec.size() };
    for(int i{}; i < vec_size; ++i) {
        if(cmp(value, vec[i])) {
            return true;
        }
    }
    return false;
}

[[nodiscard]] double Computator::getCurrentAngle() const noexcept
{
    if(m_azimuth.first) {
        return m_azimuth.second;
    }
    else {
        switch (m_wind_system.second) {
        case WindDirection::North:
            return 0.;

        case WindDirection::Northeast:
            return 45.;

        case WindDirection::East:
            return 90.;

        case WindDirection::Southeast:
            return 135.;

        case WindDirection::South:
            return 180.;

        case WindDirection::Southwest:
            return 225.;

        case WindDirection::West:
            return 270.;

        case WindDirection::Northwest:
            return 315.;
        }
    }
}

[[nodiscard]] QPixmap Computator::createFlowMap(const QVector<QVector<double>> &ux, const QVector<QVector<double>> &uy,
                                                const QVector<QVector<double>> &u0x, const QVector<QVector<double>> &u0y,
                                                const QVector<QVector<double>> &u, const QVector<QVector<double>> &u0) const
{
    QPixmap pm;
    emit getCurrentMapImage(pm);

    auto nrows{ ux.size() };
    auto ncols{ ux[0].size() };

    double max_speed{ -1. };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_depth_ptr)[i][j].first) {
                if(max_speed < u[i][j]) {
                    max_speed = u[i][j];
                }

                if(max_speed < u0[i][j]) {
                    max_speed = u0[i][j];
                }
            }
        }
    }

    static constexpr double narrow_ratio{ 0.6 };
    static constexpr double arrow_angle{ 75. };
    auto pix_xstep{ (*m_pixgrid_ptr)[0][1].second.x() -  (*m_pixgrid_ptr)[0][0].second.x() };
    auto pix_ystep{ (*m_pixgrid_ptr)[1][0].second.y() - (*m_pixgrid_ptr)[0][0].second.y() };
    auto pix_vec{ std::sqrt(std::pow(pix_xstep / 2., 2) + std::pow(pix_ystep / 2., 2)) * narrow_ratio };
    double arrow_length{ pix_vec / narrow_ratio / 3. };

    QPainter painter;
    painter.begin(&pm);
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if((*m_depth_ptr)[i][j].first) {
                double sin{};
                double cos{};
                if((*m_depth_ptr)[i][j].second > m_horizon) {
                    if(u[i][j] <= max_speed / 3.) {
                        painter.setPen(QPen(Qt::darkGreen, 1.));
                    }
                    else if(u[i][j] <= max_speed / 3. * 2.) {
                        painter.setPen(QPen(Qt::yellow, 1.));
                    }
                    else {
                        painter.setPen(QPen(Qt::red, 1.));
                    }

                    sin = uy[i][j] / u[i][j];
                    cos = ux[i][j] / u[i][j];
                }
                else {
                    if(u0[i][j] <= max_speed / 3.) {
                        painter.setPen(QPen(Qt::darkGreen, 1.));
                    }
                    else if(u0[i][j] <= max_speed / 3. * 2.) {
                        painter.setPen(QPen(Qt::yellow, 1.));
                    }
                    else {
                        painter.setPen(QPen(Qt::red, 1.));
                    }

                    sin = u0y[i][j] / u0[i][j];
                    cos = u0x[i][j] / u0[i][j];
                }

                painter.drawLine(QPointF((*m_pixgrid_ptr)[i][j].second.x() + pix_xstep / 2., (*m_pixgrid_ptr)[i][j].second.y() + pix_ystep / 2.),
                                 QPointF((*m_pixgrid_ptr)[i][j].second.x() + pix_xstep / 2. + pix_vec * cos,
                                         (*m_pixgrid_ptr)[i][j].second.y() + pix_ystep / 2. - pix_vec * sin));

                painter.drawLine(QPointF((*m_pixgrid_ptr)[i][j].second.x() + pix_xstep / 2., (*m_pixgrid_ptr)[i][j].second.y() + pix_ystep / 2.),
                                 QPointF((*m_pixgrid_ptr)[i][j].second.x() + pix_xstep / 2. - pix_vec * cos,
                                         (*m_pixgrid_ptr)[i][j].second.y() + pix_ystep / 2. + pix_vec * sin));

                const auto angle{ 90. - getCurrentAngle() };
                const QPointF begin{ (*m_pixgrid_ptr)[i][j].second.x() + pix_xstep / 2. + pix_vec * cos,
                                     (*m_pixgrid_ptr)[i][j].second.y() + pix_ystep / 2. - pix_vec * sin };
                const QPointF end{ begin.x() + arrow_length, begin.y() }; // set line length
                QLineF arrow(begin, end);
                arrow.setAngle(angle - arrow_angle - 90.);
                painter.drawLine(arrow);
                arrow.setAngle(angle + arrow_angle + 90.);
                painter.drawLine(arrow);
            }
        }
    }
    painter.end();

    return pm;
}
