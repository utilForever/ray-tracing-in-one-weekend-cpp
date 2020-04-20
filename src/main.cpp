// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#include "camera.hpp"
#include "common.hpp"
#include "dielectric.hpp"
#include "hittable_list.hpp"
#include "lambertian.hpp"
#include "metal.hpp"
#include "sphere.hpp"

#include <iostream>

vec3 ray_color(const ray& r, const hittable& world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
    {
        return vec3{0, 0, 0};
    }

    if (world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        vec3 attenuation;

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth - 1);
        }

        return vec3{0, 0, 0};
    }

    const vec3 unit_direction = unit_vector(r.direction());
    const auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3{1.0, 1.0, 1.0} + t * vec3{0.5, 0.7, 1.0};
}

int main()
{
    const int image_width = 500;
    const int image_height = 250;
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const auto aspect_ratio = static_cast<double>(image_width) / image_height;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    hittable_list world;
    world.add(std::make_shared<sphere>(
        vec3(0, 0, -1), 0.5,
        std::make_shared<lambertian>(vec3(0.1, 0.2, 0.5))));
    world.add(std::make_shared<sphere>(
        vec3(0, -100.5, -1), 100,
        std::make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));
    world.add(std::make_shared<sphere>(
        vec3(1, 0, -1), 0.5, std::make_shared<metal>(vec3(0.8, 0.6, 0.2))));
    world.add(std::make_shared<sphere>(vec3(-1, 0, -1), 0.5,
                                       std::make_shared<dielectric>(1.5)));
    world.add(std::make_shared<sphere>(vec3(-1, 0, -1), -0.45,
                                       std::make_shared<dielectric>(1.5)));

    const camera cam(vec3{-2, 2, 1}, vec3{0, 0, -1}, vec3{0, 1, 0}, 90,
                     aspect_ratio);

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i)
        {
            vec3 color{0, 0, 0};

            for (int s = 0; s < samples_per_pixel; ++s)
            {
                const auto u = (i + random_double()) / image_width;
                const auto v = (j + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, max_depth);
            }

            color.write_color(std::cout, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";

    return 0;
}