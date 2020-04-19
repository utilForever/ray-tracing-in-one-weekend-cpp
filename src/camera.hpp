// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_CAMERA_HPP
#define RAY_TRACING_CAMERA_HPP

#include "common.hpp"

class camera
{
 public:
    camera()
        : origin(vec3(0.0, 0.0, 0.0)),
          lower_left_corner(vec3(-2.0, -1.0, -1.0)),
          horizontal(vec3(4.0, 0.0, 0.0)),
          vertical(vec3(0.0, 2.0, 0.0))
    {
        // Do nothing
    }

    ray get_ray(double u, double v) const
    {
        return ray(origin,
                   lower_left_corner + u * horizontal + v * vertical - origin);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif