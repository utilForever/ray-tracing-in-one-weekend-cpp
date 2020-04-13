// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>

// Ray equation: p(t) = a + t * vec(b).
// The equation of sphere: (p(t) - c) dot (p(t) - c) = r^2.
// Therefore, (a + t * vec(b) - c) dot (a + t * vec(b) - c) = r^2.
// => t^2 * vec(b) dot vec(b) + 2 * t * vec(b) dot vec(a - c) + vec(a - c) dot vec(a - c) - r^2 = 0.
bool hit_sphere(const vec3& center, double radius, const ray& r)
{
    const vec3 oc = r.origin() - center;
    const auto a = dot(r.direction(), r.direction());
    const auto b = 2.0 * dot(oc, r.direction());
    const auto c = dot(oc, oc) - radius * radius;

    const auto discriminant = b * b - 4 * a * c;
    return discriminant > 0;
}

vec3 ray_color(const ray& r)
{
    if (hit_sphere(vec3{0, 0, -1}, 0.5, r))
    {
        return vec3{1, 0, 0};
    }

    const vec3 unit_direction = unit_vector(r.direction());
    const auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3{1.0, 1.0, 1.0} + t * vec3{0.5, 0.7, 1.0};
}

int main()
{
    const int image_width = 200;
    const int image_height = 100;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    const vec3 lower_left_corner{-2.0, -1.0, -1.0};
    const vec3 horizontal{4.0, 0.0, 0.0};
    const vec3 vertical{0.0, 2.0, 0.0};
    const vec3 origin{0.0, 0.0, 0.0};

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i)
        {
            const auto u = double(i) / image_width;
            const auto v = double(j) / image_height;
            ray r{origin, lower_left_corner + u * horizontal + v * vertical};
            vec3 color = ray_color(r);

            color.write_color(std::cout);
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}