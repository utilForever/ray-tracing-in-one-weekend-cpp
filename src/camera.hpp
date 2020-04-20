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
    // vfov: top to bottom, in degrees
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect)
    {
        origin = lookfrom;

        const auto theta = degrees_to_radians(vfov);
        const auto half_height = tan(theta / 2);
        const auto half_width = aspect * half_height;

        const vec3 w = unit_vector(lookfrom - lookat);
        const vec3 u = unit_vector(cross(vup, w));
        const vec3 v = cross(w, u);

        lower_left_corner = origin - half_width * u - half_height * v - w;

        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
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