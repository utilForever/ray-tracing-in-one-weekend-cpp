// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#include "ray.hpp"
#include "vec3.hpp"

#include <iostream>

vec3 ray_color(const ray& r)
{
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