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

#endif // POLLUTIONWIDGET_UTILITIES_HPP
