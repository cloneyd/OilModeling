#ifndef POLLUTIONWIDGET_UTILITIES_HPP
#define POLLUTIONWIDGET_UTILITIES_HPP
#include "Helpers/pch.hpp"
#include "PollutionWidget/pollution_source_types.hpp"

enum class SourceType : unsigned char
{
    PointSource,
    DiffusionSource
};

enum class WidgetMode : unsigned char
{
    Create,
    Display
};

#endif // POLLUTIONWIDGET_UTILITIES_HPP
