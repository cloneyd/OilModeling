// QT
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

// current project
#include "object3dcontainer.hpp"

Object3DContainer::Object3DContainer(QWidget *parent) :
    QWidget(parent),
    m_3dobject{}, // this class will be owner of m_3dobject
    m_gradient_label{}
{
    auto graph{ new QtDataVisualization::Q3DSurface }; // WARNING: throws
    if (!graph->hasContext()) {
        QMessageBox::warning(nullptr, "OpenGL error", QString("Couldn't initialize the OpenGL context."));
        return;
    }

    auto graph_container{ QWidget::createWindowContainer(graph, this) }; // adopt the graph to container

    graph_container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    graph_container->setFocusPolicy(Qt::StrongFocus);

    auto hlayout{ new QHBoxLayout(this) };
    auto gradient_group_box(new QGroupBox(QString("Цветовая палитра"), this));
    hlayout->addWidget(graph_container, 1); // change owner

    auto vlayout{ new QVBoxLayout{} };
    hlayout->addLayout(vlayout);
    vlayout->setAlignment(Qt::AlignTop);

    setWindowTitle(QString("3D визуализация"));

    auto gradient_vlayout{ new QVBoxLayout{} };
    gradient_vlayout->addWidget(&m_gradient_label);
    gradient_group_box->setLayout(gradient_vlayout);

    vlayout->addWidget(gradient_group_box);

    m_3dobject.resetGraph(graph);
}


// public slots
void Object3DContainer::acceptPixGrid(const GridType &pixgrid)
{
    m_3dobject.setGridPtr(std::addressof(pixgrid));
    m_3dobject.setDepth({}); // depth must become empty
    m_3dobject.repaint();

    m_gradient_label.clear();
    m_gradient_label.setPixmap(m_3dobject.getGradientPixmap());
    emit depthChanged({}); // depth is empty now
}

void Object3DContainer::acceptDepth(DepthType &depth)
{
    acceptDepth_(depth, true);
    emit depthChanged(m_3dobject.getDepth());
}

void Object3DContainer::show()
{
    m_3dobject.show();
    QWidget::show();
}

void Object3DContainer::saveState(QTextStream &stream, const char delim)
{
    const auto &depth{ m_3dobject.getDepth() };
    const auto nrows{ depth.size() };
    const auto ncols{ nrows > 0 ? depth[0].size() : 0 };
    stream << nrows << '\t' << ncols << delim;
    for(int row_index{}; row_index < nrows; ++row_index) {
        for(int col_index{}; col_index < ncols; ++col_index) {
            stream << depth[row_index][col_index].first << '\t';
            stream << depth[row_index][col_index].second << '\t';
        }
    }
    stream << delim; // control delim
}

void Object3DContainer::restoreState(QTextStream &stream, const char delim)
{
    auto readUntilDelim = [&stream](const char delim) -> QString {
        QString result{};
        char sym{};
        for(stream >> sym; sym != delim; stream >> sym) {
            result += sym;
        }
        return result;
    };
    bool is_converted{};
    const auto nrows{ readUntilDelim('\t').toInt(&is_converted) };
    Q_ASSERT(is_converted);

    const auto ncols{ readUntilDelim(delim).toInt(&is_converted) };
    Q_ASSERT(is_converted);

    DepthType depth(nrows, QVector<QPair<bool, double>>(ncols, qMakePair(false, -1.)));
    for(int row_index{}; row_index < nrows; ++row_index) {
        for(int col_index{}; col_index < ncols; ++col_index) {
            const bool belongness = readUntilDelim('\t').toInt(&is_converted); // narrow
            Q_ASSERT(is_converted);

            const double value{ readUntilDelim('\t').toDouble(&is_converted) };
            Q_ASSERT(is_converted);
            depth[row_index][col_index] = qMakePair(belongness, value);
        }
    }
    char ctrl_delim{};
    stream >> ctrl_delim;
    Q_ASSERT(ctrl_delim == delim);

    acceptDepth_(depth, false);
    emit depthChanged(m_3dobject.getDepth());
}


// private functions
void Object3DContainer::acceptDepth_(DepthType &depth, bool interpolate)
{
    if(interpolate) interpolation_and_approximation(depth);
    m_3dobject.setDepth(std::move(depth));
    m_3dobject.repaint();

    m_gradient_label.clear();
    m_gradient_label.setPixmap(m_3dobject.getGradientPixmap());
}

void Object3DContainer::interpolation_and_approximation(DepthType &depth)
{
    const auto &grid{ m_3dobject.getRealMetersGrid() };
    const auto nrows{ depth.size() };
    if(nrows == 0)  return;
    const auto ncols{ depth[0].size() };
    if(ncols == 0)  return;

    interpolation(grid, depth); // first interpolation

    // check that there is no uninterlopated values in depth
    auto is_interpolated_flag{ true };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(depth[i][j].first && depth[i][j].second < 0.) {
                is_interpolated_flag = false;
                break;
            }
        }
        if(!is_interpolated_flag) {
            break;
        }
    }

    if(!is_interpolated_flag) {
        // TODO: normalizing with approximated values; these values must be returned by this funtion
        create_approximation_row(grid, depth); // approximation + second interpolation
        interpolation(grid, depth); // third interpolation
    }
}

void Object3DContainer::interpolation(const GridType &realgrid, DepthType &depth)
{
    const auto nrows{ depth.size() };
    const auto ncols{ depth[0].size() };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(depth[i][j].first && depth[i][j].second < 0.) { // if interpolation is needed
                if(i > 0 && i < nrows - 1 && j > 0 && j < ncols - 1) { // if point not belong to borders
                    if(depth[i - 1][j - 1].first && depth[i - 1][j + 1].first && depth[i - 1][j - 1].second > 0. && depth[i - 1][j + 1].second > 0.) { // if 11 and 13
                        double x[]{ realgrid[i][j - 1].second.x(), realgrid[i][j + 1].second.x() };
                        if(depth[i + 1][j - 1].first && depth[i + 1][j + 1].first && depth[i + 1][j - 1].second > 0. && depth[i + 1][j + 1].second > 0.) { // if 31 and 33
                            double y[]{ realgrid[i - 1][j].second.y(), realgrid[i + 1][j].second.y() };
                            double z[]{ depth[i - 1][j - 1].second, // 11
                                        depth[i - 1][j + 1].second, // 13
                                        depth[i + 1][j - 1].second, // 31
                                        depth[i + 1][j + 1].second }; // 33
                            depth[i][j].second = bilinear_interpolation(x, y, z, realgrid[i][j].second.x(), realgrid[i][j].second.y());
                        }
                        else {
                            double z[]{ depth[i - 1][j - 1].second, // 11
                                        depth[i - 1][j + 1].second }; // 13
                            depth[i][j].second = linear_interpolation(x, z, realgrid[i][j].second.x());
                        }
                    }

                    if(depth[i - 1][j].first && depth[i + 1][j].first && depth[i - 1][j].second > 0. && depth[i + 1][j].second > 0.) { // if 12 and 32
                        double y[]{ realgrid[i - 1][j].second.y(), realgrid[i + 1][j].second.y() };
                        if(depth[i][j - 1].first && depth[i][j + 1].first && depth[i][j - 1].second > 0. && depth[i][j + 1].second > 0.) { // if 21 and 23
                            double x[]{ realgrid[i][j - 1].second.x(), realgrid[i][j + 1].second.x() };
                            double z[]{ depth[i - 1][j].second, // 12
                                        depth[i][j + 1].second, // 23
                                        depth[i][j - 1].second, // 21
                                        depth[i + 1][j].second }; // 32

                            if(auto value { bilinear_interpolation(x, y, z, realgrid[i][j].second.x(), realgrid[i][j].second.y()) }; depth[i][j].second > 0.) { // if height was interpolated on previous step
                                depth[i][j].second = (depth[i][j].second + value) / 2.;
                            }
                            else {
                                depth[i][j].second = value;
                            }
                        }
                        else {
                            double z[] { depth[i - 1][j].second, depth[i + 1][j].second }; // 12 and 32
                            auto value{ linear_interpolation(y, z, realgrid[i][j].second.y()) };

                            if(depth[i][j].second > 0.) { // if it was interpolated on previous stage
                                depth[i][j].second = (depth[i][j].second + value) / 2.;
                            }
                            else {
                                depth[i][j].second = value;
                            }
                        }
                    }

                    if(depth[i][j - 1].first && depth[i][j + 1].first && depth[i][j - 1].second > 0. && depth[i][j + 1].second > 0.) { // 21 and 23
                        double x[]{ realgrid[i][j - 1].second.x(), realgrid[i][j + 1].second.x() };
                        double z[]{ depth[i][j - 1].second, depth[i][j + 1].second };

                        if(auto value{ linear_interpolation(x, z, realgrid[i][j].second.x()) }; depth[i][j].second > 0.) { // if value has interpolated already
                            depth[i][j].second = (depth[i][j].second + value) / 2.;
                        }
                        else {
                            depth[i][j].second = value;
                        }
                    }

                    if(depth[i - 1][j - 1].first && depth[i + 1][j + 1].first && depth[i - 1][j - 1].second > 0. && depth[i + 1][j + 1].second > 0.) { // if 11 and 33
                        double x[]{ realgrid[i - 1][j - 1].second.x(), realgrid[i + 1][j + 1].second.x() };
                        double y[]{ realgrid[i - 1][j -1].second.y(), realgrid[i + 1][j + 1].second.y() };
                        double z[]{ depth[i - 1][j - 1].second, depth[i + 1][j + 1].second };

                        if(auto value{ linear_interpolation(x, z, realgrid[i][j].second.x()) }; depth[i][j].second > 0.) {
                            depth[i][j].second = (depth[i][j].second + value) / 2.;
                        }
                        else {
                            depth[i][j].second = value;
                        }
                        depth[i][j].second = (depth[i][j].second + linear_interpolation(y, z, realgrid[i][j].second.y())) / 2.;
                    }

                }
                else if(i > 0 && i < nrows - 1) { // if not the row border
                    if(depth[i - 1][j].first && depth[i + 1][j].first && depth[i - 1][j].second > 0. && depth[i + 1][j].second > 0.) { // if 12 and 32
                        double y[]{ realgrid[i - 1][j].second.y(), realgrid[i + 1][j].second.y() };
                        double z[]{ depth[i - 1][j].second, depth[i + 1][j].second };
                        depth[i][j].second = linear_interpolation(y, z, realgrid[i][j].second.y());
                    }
                }
                else if(j > 0 && j < ncols - 1) { // if not the column border
                    if(depth[i][j - 1].first && depth[i][j + 1].first && depth[i][j - 1].second > 0. && depth[i][j + 1].second > 0.) { // if 21 and 23
                        double x[]{ realgrid[i][j - 1].second.x(), realgrid[i][j + 1].second.x() };
                        double z[]{ depth[i][j - 1].second, depth[i][j + 1].second };
                        depth[i][j].second = linear_interpolation(x, z, realgrid[i][j].second.x());
                    }
                }
            // else - do nothing
            }
        // else - do nothing
        }
    }
}

void Object3DContainer::create_approximation_row(const GridType &realgrid, DepthType &depth)
{
    const auto nrows{ realgrid.size() };
    if(nrows == 0)  return;
    const auto ncols{ realgrid[0].size() };
    if(ncols == 0)  return;

    constexpr double load_factor{ 0.5 }; // load factor is used to determine how many times the number of known approximations should be greater than the number of unknowns

    QVector<double> values;
    QVector<QPair<int, double>> interpol_values;
    QVector<double> z;
    values.reserve(ncols);
    interpol_values.reserve(ncols);
    z.reserve(ncols);

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(depth[i][j].first) {
                if(depth[i][j].second > 0.) {
                    values.append(realgrid[i][j].second.x());
                    z.append(depth[i][j].second);
                }
                else {
                    interpol_values.append(qMakePair(j, realgrid[i][j].second.x()));
                }
            }
        }

        if(interpol_values.size() > 0 && static_cast<int>(std::ceil(load_factor * values.size())) >= interpol_values.size()) {
            auto aprx_value{ approximation(values, z, interpol_values) };
            auto apr_size{ aprx_value.size() };
            for(int j{}; j < apr_size; ++j) {
                depth[i][interpol_values[j].first].second = aprx_value[j];
            }
            interpolation(realgrid, depth);
        }

        values.clear();
        interpol_values.clear();
        z.clear();
    }

    for(int i{}; i < ncols; ++i) {
        for(int j{}; j < nrows; ++j) {
            if(depth[j][i].first) {
                if(depth[j][i].second > 0.) {
                    values.append(realgrid[j][i].second.y());
                    z.append(depth[j][i].second);
                }
                else {
                    interpol_values.append(qMakePair(j, realgrid[j][i].second.y()));
                }
            }
        }

        if(static_cast<int>(std::ceil(load_factor * values.size())) >= interpol_values.size()) {
            auto aprx_value{ approximation(values, z, interpol_values) };
            auto apr_size{ aprx_value.size() };
            for(int j{}; j < apr_size; ++j) {
                depth[interpol_values[j].first][i].second = aprx_value[j];
            }
        }

        values.clear();
        interpol_values.clear();
        z.clear();
    }
}

// average - shift for the parabola centre
#define FOO(x, xshift, yshift) (yshift - ((x) + xshift) * ((x) + xshift))
QVector<double> Object3DContainer::approximation(const QVector<double> &x, const QVector<double> &y, const QVector<QPair<int, double>> &interpol_x) const
{
    constexpr auto error{ 1e-4 };
    const auto app_size{ x.size() };
    const auto interpol_size{ interpol_x.size() };
    QVector<double> values(interpol_size, -1.); // return value

    if(app_size == 0) return values;
    if(interpol_size == 0) return values;

    auto average = [](const QVector<double> &vec) -> double {
        auto vec_size{ vec.size() };
        double average_sum{};
        for(int i{}; i < vec_size; ++i) {
            average_sum += vec[i];
        }
        return average_sum / vec_size;
    };

    // computating average value of function argument (as approximation so interpolation)
    double center{}; // must be average for all values (app and inter)
    for(int i{} ; i < app_size; ++i) {
        center += x[i];
    }
    for(int i{}; i < interpol_size; ++i) {
        center += interpol_x[i].second;
    }
    center /= (app_size + interpol_size);

    // computatin average delta with known function values and average known function arguments
    double average_ydelta{};
    double ymax{ y[0] };
    for(int i{ 1 }; i < app_size; ++i) {
        average_ydelta += std::fabs(y[i] - y[i - 1]);
        if(ymax < y[i]) ymax = y[i];
    }
    average_ydelta /= app_size - 1;

    // if all function values equal
    if(average_ydelta < error) {
        for(int i{}; i < interpol_size; ++i) {
            values[i] = y[0];
        }
        return values;
    }

    // computating function aspect ratio
    double min_compression_ratio{ 1e+10 };
    double max_compression_ratio{ -1. };
    for(int i{}; i < app_size; ++i) {
        auto cur_ratio{ std::fabs(FOO(x[i], center, ymax) / y[i]) };

        if(cur_ratio < min_compression_ratio) {
            min_compression_ratio = cur_ratio;
        }
        if(cur_ratio > max_compression_ratio) {
            max_compression_ratio = cur_ratio;
        }
    }

    double average_argument{ average(x)};

    // computating values in other points
    double average_compression_ratio{ (max_compression_ratio + min_compression_ratio) / 2. };
    for(int i{}; i < interpol_size; ++i) {
        if(interpol_x[i].second > average_argument) {
            values[i] = std::fabs(FOO(interpol_x[i].second, center, ymax)) / max_compression_ratio;
        }
        else {
            values[i] = std::fabs(FOO(interpol_x[i].second, center, ymax)) / average_compression_ratio;
        }
    }

    int first_app_index{};
    for(int i{}; i < interpol_size; ++i)  {
        if(interpol_x[i].second < x[0]) {
            first_app_index = i;
            break;
        }
    }

    int last_app_index{ interpol_size - 1};
    for(int i{ interpol_size - 1}; i >= 0; --i) {
        if(interpol_x[i].second < x[app_size - 1]) {
            last_app_index = i;
            break;
        }
    }

    if(first_app_index <= last_app_index) {
        for(int i{}; i < first_app_index; ++i) {
            values[i] = (values[i] + y[0]) / 2.;
        }

        for(int i{ first_app_index }; i <= last_app_index; ++i) {
            values[i] = (values[i] + y[binary_search(x, interpol_x[i].second)]) / 2.;
        }

        for(int i{ last_app_index + 1 }; i < interpol_size; ++i) {
            values[i] = (values[i] + y[app_size - 1]) / 2. - average_ydelta;
        }
    }
    else {
        for(int i{ }; i < interpol_size; ++i) {
            values[i] = (values[i] + y[binary_search(x, interpol_x[i].second)]) / 2. - average_ydelta;
        }
    }

    return values;
}
#undef FOO

[[nodiscard]] int Object3DContainer::binary_search(const QVector<double> &vec, double value, double atol) const
{
    const auto size{ vec.size() };
    auto left_bound{ 0 };
    auto right_bound{ size - 1 };
    auto index{ size - 1 };
    double min_diff{ vec.back() + 1. };
    auto cur_index{ right_bound / 2 };

    if (vec.front() > value) {
        return 0;
    }

    if (vec.back() < value) {
        return size - 1;
    }

    while (left_bound <= right_bound) {
        if (std::abs(vec[cur_index] - value) < atol) return cur_index;
        else {
            if (auto diff{ std::abs(vec[index] - vec[cur_index]) }; diff < min_diff) {
                min_diff = diff;
                index = cur_index;
            }
            if (value < vec[cur_index]) {
                right_bound = cur_index - 1;
            }
            else {
                left_bound = cur_index + 1;
            }
            cur_index = (right_bound + left_bound) / 2;
        }
    }

    return index;
}
