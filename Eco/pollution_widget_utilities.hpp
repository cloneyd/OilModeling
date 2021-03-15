#ifndef POLLUTION_WIDGET_UTILITIES_HPP
#define POLLUTION_WIDGET_UTILITIES_HPP

enum SourceType : unsigned char
{
    MIN,
    Point = MIN,
    Diffusion,
    MAX = Diffusion
};

enum class WidgetMode : unsigned char
{
    Create,
    Display
};

#endif // POLLUTION_WIDGET_UTILITIES_HPP
