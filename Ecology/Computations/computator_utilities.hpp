#ifndef COMPUTATOR_UTILITIES_HPP
#define COMPUTATOR_UTILITIES_HPP
#include "Helpers/pch.hpp"

enum class WaterObjectType : unsigned char // AHTUNG!!! IF WATER OBJECT COMBO BOX(class - MainWindow) WILL BE CHANGED - UB!!!!!
{
    MIN,
    River = MIN,
    Lake,
    MAX = Lake
};

enum class WindDirection : unsigned char // AHTUNG!!! IF SYSTEM COMBO BOX(class - MainWindow) WILL BE CHANGED - UB!!!
{
    MIN,
    North = MIN, // first el
    Northeast,
    East,
    Southeast,
    South,
    Southwest,
    West,
    Northwest, // last el
    MAX = Northwest // must be equal to last el
};

#endif // COMPUTATOR_UTILITIES_HPP
