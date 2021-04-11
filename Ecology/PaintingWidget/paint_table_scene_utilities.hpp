#ifndef PAINT_TABLE_SCENE_UTILITIES_HPP
#define PAINT_TABLE_SCENE_UTILITIES_HPP
// current project
#include "Helpers/pch.hpp"

// static constants
namespace PaintTableSceneConstants // constants will be unused it this file
{
// FIXME: replace static variables to templates functions
    Q_DECL_UNUSED static constexpr double s_line_width{ 3. };
    Q_DECL_UNUSED static constexpr double s_length_ratio{ 2.5 }; // used to determine max point distance (s_line_width * s_length_ratio = max_distance)
}

enum class PaintStyle : unsigned char
{
    Ellipse,
    Lines
};

enum class ChangeType : unsigned char
{
    Buffering,
    Stashing,
    Deleted
};
#endif // PAINT_TABLE_SCENE_UTILITIES_HPP
