// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_COMMON_HPP
#define RAY_TRACING_COMMON_HPP

#include <limits>

// Common headers
#include "ray.hpp"
#include "vec3.hpp"

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180;
}

inline double ffmin(double a, double b)
{
    return a <= b ? a : b;
}

inline double ffmax(double a, double b)
{
    return a >= b ? a : b;
}

#endif