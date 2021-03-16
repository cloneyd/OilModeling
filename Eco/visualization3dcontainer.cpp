#include "visualization3dcontainer.hpp"

#include <QMessageBox>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTableWidgetItem>

// STL
#include <algorithm>

extern void showErrorMessageBox(const QString &message, const QString &title = "");

// ctor and dtor
Visualization3DContainer::Visualization3DContainer(QWidget *parent) :
    QWidget(parent),
    m_container{}, // will be deleted automatically with widget
    m_3dobject{},
    m_gr_label{ new QLabel } // WARNING: may throw; should be replaced
{
    auto graph{ new QtDataVisualization::Q3DSurface }; // WARNING: may throw; // FIXME!!!: deletion problem (leak now)
    if (!graph->hasContext()) {
        showErrorMessageBox(QString("Couldn't initialize the OpenGL context."), "OpenGL error");
        return;
    }
    m_container = QWidget::createWindowContainer(graph, this); // adopt the graph to container

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

    m_3dobject = new Visualization3DObject(graph); // WARNING: may throw; should be replaced
}

Visualization3DContainer::~Visualization3DContainer() noexcept
{
    delete m_gr_label;
    delete m_3dobject;
}


// public slots
void Visualization3DContainer::setupGrid(const QVector<QVector<QPair<bool, QPointF>>> &grid)
{
    m_3dobject->setGrid(grid);
    m_gr_label->setPixmap(m_3dobject->getGradientPixmap());
    m_3dobject->updateMap();

    emit heightsChanged(m_3dobject->getHeights());
}

void Visualization3DContainer::setupHeights(QTableWidget &table)
{
    const auto &grid{ m_3dobject->getGrid() };
    auto rows{ grid.size() };
    auto cols{ rows > 0 ? grid[0].size() : 0 };
    QVector<QVector<QPair<bool, double>>> heights(rows);

    bool convertion_flag{};
    for(int i{}; i < rows; ++i) {
        QVector<QPair<bool, double>> tmp(cols, {false, -1.});
        for(int j{}; j < cols; ++j) {
            if(grid[i][j].first) {
                if(auto value{ table.item(i, j)->text().toDouble(&convertion_flag) }; convertion_flag) {
                    tmp[j] = qMakePair(true, value);
                }
                else {
                    tmp[j] = qMakePair(false, -1);
                }
            }
        }
        heights[i] = std::move(tmp); // WARNING: extra copy
    }

    interpolation_and_approximation(heights);
    m_3dobject->setHeights(std::move(heights));

    m_gr_label->clear();
    m_gr_label->setPixmap(m_3dobject->getGradientPixmap());


    emit heightsChanged(m_3dobject->getHeights());
}

void Visualization3DContainer::setupHeights(QVector<QVector<QPair<bool, double>>> &heights)
{
    interpolation_and_approximation(heights);
    m_3dobject->setHeights(std::move(heights));

    m_gr_label->clear();
    m_gr_label->setPixmap(m_3dobject->getGradientPixmap());

    emit heightsChanged(m_3dobject->getHeights());
}

void Visualization3DContainer::setupScale(double scale)
{
    m_3dobject->setScale(screen()->physicalDotsPerInch() / 2.54 / scale);
}


// private helper methods
void Visualization3DContainer::interpolation_and_approximation(QVector<QVector<QPair<bool, double>>> &heights)
{
    const auto &grid{ m_3dobject->getGrid() };
    const auto nrows{ heights.size() };
    if(nrows == 0)  return;
    const auto ncols{ heights[0].size() };
    if(ncols == 0)  return;

    interpolation(grid, heights); // first interpolation

    // check that there is no uniterlopated values in heights
    auto is_interpolated_flag{ true };
    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
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
        // TODO: normalizing with approximated values; these values must be returned by this funtion
        create_approximation_row(grid, heights); // approximation + second interpolation
        interpolation(grid, heights); // third interpolation
    }
}

void Visualization3DContainer::interpolation(const QVector<QVector<QPair<bool, QPointF>>> &grid, QVector<QVector<QPair<bool, double>>> &heights)
{
    const auto nrows{ heights.size() };
    const auto ncols{ heights[0].size() };

    for(int i{}; i < nrows; ++i) {
        for(int j{}; j < ncols; ++j) {
            if(heights[i][j].first && heights[i][j].second < 0.) { // if interpolation is needed
                if(i > 0 && i < nrows - 1 && j > 0 && j < ncols - 1) { // if point not belong to borders
                    if(heights[i - 1][j - 1].first && heights[i - 1][j + 1].first && heights[i - 1][j - 1].second > 0. && heights[i - 1][j + 1].second > 0.) { // if 11 and 13
                        double x[]{ grid[i][j - 1].second.x(), grid[i][j + 1].second.x() };
                        if(heights[i + 1][j - 1].first && heights[i + 1][j + 1].first && heights[i + 1][j - 1].second > 0. && heights[i + 1][j + 1].second > 0.) { // if 31 and 33
                            double y[]{ grid[i - 1][j].second.y(), grid[i + 1][j].second.y() };
                            double z[]{ heights[i - 1][j - 1].second, // 11
                                        heights[i - 1][j + 1].second, // 13
                                        heights[i + 1][j - 1].second, // 31
                                        heights[i + 1][j + 1].second }; // 33
                            heights[i][j].second = bilinear_interpolation(x, y, z, grid[i][j].second.x(), grid[i][j].second.y());
                        }
                        else {
                            double z[]{ heights[i - 1][j - 1].second, // 11
                                        heights[i - 1][j + 1].second }; // 13
                            heights[i][j].second = linear_interpolation(x, z, grid[i][j].second.x());
                        }
                    }

                    if(heights[i - 1][j].first && heights[i + 1][j].first && heights[i - 1][j].second > 0. && heights[i + 1][j].second > 0.) { // if 12 and 32
                        double y[]{ grid[i - 1][j].second.y(), grid[i + 1][j].second.y() };
                        if(heights[i][j - 1].first && heights[i][j + 1].first && heights[i][j - 1].second > 0. && heights[i][j + 1].second > 0.) { // if 21 and 23
                            double x[]{ grid[i][j - 1].second.x(), grid[i][j + 1].second.x() };
                            double z[]{ heights[i - 1][j].second, // 12
                                        heights[i][j + 1].second, // 23
                                        heights[i][j - 1].second, // 21
                                        heights[i + 1][j].second }; // 32

                            if(auto value { bilinear_interpolation(x, y, z, grid[i][j].second.x(), grid[i][j].second.y()) }; heights[i][j].second > 0.) { // if height was interpolated on previous step
                                heights[i][j].second = (heights[i][j].second + value) / 2.;
                            }
                            else {
                                heights[i][j].second = value;
                            }
                        }
                        else {
                            double z[] { heights[i - 1][j].second, heights[i + 1][j].second }; // 12 and 32
                            auto value{ linear_interpolation(y, z, grid[i][j].second.y()) };

                            if(heights[i][j].second > 0.) { // if it was interpolated on previous stage
                                heights[i][j].second = (heights[i][j].second + value) / 2.;
                            }
                            else {
                                heights[i][j].second = value;
                            }
                        }
                    }

                    if(heights[i][j - 1].first && heights[i][j + 1].first && heights[i][j - 1].second > 0. && heights[i][j + 1].second > 0.) { // 21 and 23
                        double x[]{ grid[i][j - 1].second.x(), grid[i][j + 1].second.x() };
                        double z[]{ heights[i][j - 1].second, heights[i][j + 1].second };

                        if(auto value{ linear_interpolation(x, z, grid[i][j].second.x()) }; heights[i][j].second > 0.) { // if value has interpolated already
                            heights[i][j].second = (heights[i][j].second + value) / 2.;
                        }
                        else {
                            heights[i][j].second = value;
                        }
                    }

                    if(heights[i - 1][j - 1].first && heights[i + 1][j + 1].first && heights[i - 1][j - 1].second > 0. && heights[i + 1][j + 1].second > 0.) { // if 11 and 33
                        double x[]{ grid[i - 1][j - 1].second.x(), grid[i + 1][j + 1].second.x() };
                        double y[]{ grid[i - 1][j -1].second.y(), grid[i + 1][j + 1].second.y() };
                        double z[]{ heights[i - 1][j - 1].second, heights[i + 1][j + 1].second };

                        if(auto value{ linear_interpolation(x, z, grid[i][j].second.x()) }; heights[i][j].second > 0.) {
                            heights[i][j].second = (heights[i][j].second + value) / 2.;
                        }
                        else {
                            heights[i][j].second = value;
                        }
                        heights[i][j].second = (heights[i][j].second + linear_interpolation(y, z, grid[i][j].second.y())) / 2.;
                    }

                }
                else if(i > 0 && i < nrows - 1) { // if not the row border
                    if(heights[i - 1][j].first && heights[i + 1][j].first && heights[i - 1][j].second > 0. && heights[i + 1][j].second > 0.) { // if 12 and 32
                        double y[]{ grid[i - 1][j].second.y(), grid[i + 1][j].second.y() };
                        double z[]{ heights[i - 1][j].second, heights[i + 1][j].second };
                        heights[i][j].second = linear_interpolation(y, z, grid[i][j].second.y());
                    }
                }
                else if(j > 0 && j < ncols - 1) { // if not the column border
                    if(heights[i][j - 1].first && heights[i][j + 1].first && heights[i][j - 1].second > 0. && heights[i][j + 1].second > 0.) { // if 21 and 23
                        double x[]{ grid[i][j - 1].second.x(), grid[i][j + 1].second.x() };
                        double z[]{ heights[i][j - 1].second, heights[i][j + 1].second };
                        heights[i][j].second = linear_interpolation(x, z, grid[i][j].second.x());
                    }
                }
            // else - do nothing
            }
        // else - do nothing
        }
    }
}

void Visualization3DContainer::create_approximation_row(const QVector<QVector<QPair<bool, QPointF>>> &grid, QVector<QVector<QPair<bool, double>>> &heights)
{
    const auto nrows{ grid.size() };
    if(nrows == 0)  return;
    const auto ncols{ grid[0].size() };
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
            if(heights[i][j].first) {
                if(heights[i][j].second > 0.) {
                    values.append(grid[i][j].second.x());
                    z.append(heights[i][j].second);
                }
                else {
                    interpol_values.append(qMakePair(j, grid[i][j].second.x()));
                }
            }
        }

        if(interpol_values.size() > 0 && static_cast<int>(std::ceil(load_factor * values.size())) >= interpol_values.size()) {
            auto aprx_value{ approximation(values, z, interpol_values) };
            auto apr_size{ aprx_value.size() };
            for(int j{}; j < apr_size; ++j) {
                heights[i][interpol_values[j].first].second = aprx_value[j];
            }
            interpolation(grid, heights);
        }

        values.clear();
        interpol_values.clear();
        z.clear();
    }

    for(int i{}; i < ncols; ++i) {
        for(int j{}; j < nrows; ++j) {
            if(heights[j][i].first) {
                if(heights[j][i].second > 0.) {
                    values.append(grid[j][i].second.y());
                    z.append(heights[j][i].second);
                }
                else {
                    interpol_values.append(qMakePair(j, grid[j][i].second.y()));
                }
            }
        }

        if(static_cast<int>(std::ceil(load_factor * values.size())) >= interpol_values.size()) {
            auto aprx_value{ approximation(values, z, interpol_values) };
            auto apr_size{ aprx_value.size() };
            for(int j{}; j < apr_size; ++j) {
                heights[interpol_values[j].first][i].second = aprx_value[j];
            }
        }

        values.clear();
        interpol_values.clear();
        z.clear();
    }
}

// average - shift for the parabola centre
#define FOO(x, xshift, yshift) (yshift - ((x) + xshift) * ((x) + xshift))
QVector<double> Visualization3DContainer::approximation(const QVector<double> &x, const QVector<double> &y, const QVector<QPair<int, double>> &interpol_x) const
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

int Visualization3DContainer::binary_search(const QVector<double> &vec, double value, double atol) const
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

[[nodiscard]] double Visualization3DContainer::bilinear_interpolation(const double (&x)[2], const double (&y)[2], const double (&z)[4], double interpol_x, double interpol_y) const
{
    auto f1{ z[0] + (interpol_x - x[0]) * (z[2] - z[0]) / (x[1] - x[0]) };
    auto f2{ z[2] + (interpol_x - x[0]) * (z[3] - z[2]) / (x[1] - x[0]) };
    return f1 + (interpol_y - y[0]) * (f2 - f1) / (y[1] - y[0]);
}

[[nodiscard]] double Visualization3DContainer::linear_interpolation(const double (&x)[2], const double (&y)[2], double interpol_x) const
{
    return y[0] + (interpol_x - x[0]) * (y[1] - y[0]) / (x[1] - x[0]);
}
