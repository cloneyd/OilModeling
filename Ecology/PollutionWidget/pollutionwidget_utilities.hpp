#ifndef POLLUTIONWIDGET_UTILITIES_HPP
#define POLLUTIONWIDGET_UTILITIES_HPP
#include "Helpers/pch.hpp"
#include "PollutionWidget/pollution_source_types.hpp"

enum class SourceType : unsigned char
{
    MIN,
    PointSource = MIN,
    DiffusionSource,
    MAX = DiffusionSource
};

enum class WidgetMode : unsigned char
{
    MIN,
    Create = MIN,
    Display,
    MAX = Display
};

struct FileMatterInformation // struct represent information about matter which can be read from file
{
    QString m_name;
    double m_mpc;
    QString m_group;
};

#endif // POLLUTIONWIDGET_UTILITIES_HPP
