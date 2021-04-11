#ifndef GRID_HANDLER_UTILITIES_HPP
#define GRID_HANDLER_UTILITIES_HPP
// current project
#include "Helpers/pch.hpp"

using GridType = QVector<QVector<QPair<bool, QPointF>>>;

namespace GridHandlerConstants
{
    Q_DECL_UNUSED static constexpr double s_max_error{ 1e-3 }; // max cell parameters error
}

[[nodiscard]] double toPixels(double meters) noexcept; // converts from meters to pixels; relies on current scale; defined im gridhanler.cpp
[[nodiscard]] double toMeters(double pixels) noexcept; // converts from pixels to real meters; relies on current scale; defined im gridhanler.cpp

#endif // GRID_HANDLER_UTILITIES_HPP
