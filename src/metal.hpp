// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_METAL_HPP
#define RAY_TRACING_METAL_HPP

#include "hittable.hpp"
#include "material.hpp"

class metal final : public material
{
 public:
    metal(const vec3& a) : albedo(a)
    {
        // Do nothing
    }

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation,
                 ray& scattered) const override
    {
        const vec3 reflected =
            reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;

        return dot(scattered.direction(), rec.normal) > 0;
    }

    vec3 albedo;
};

#endif