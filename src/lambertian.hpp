// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_LAMBERTIAN_HPP
#define RAY_TRACING_LAMBERTIAN_HPP

#include "hittable.hpp"
#include "material.hpp"

class lambertian final : public material
{
 public:
    lambertian(const vec3& a) : albedo(a)
    {
        // Do nothing
    }

    bool scatter([[maybe_unused]] const ray& r_in, const hit_record& rec,
                 vec3& attenuation, ray& scattered) const override
    {
        const vec3 scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;

        return true;
    }

    vec3 albedo;
};

#endif