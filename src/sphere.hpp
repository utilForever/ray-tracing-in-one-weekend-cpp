// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_SPHERE_HPP
#define RAY_TRACING_SPHERE_HPP

#include "hittable.hpp"
#include "vec3.hpp"

class sphere final : public hittable
{
 public:
    sphere() = default;
    sphere(vec3 cen, double r, std::shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(m)
    {
        // Do nothing
    }

    bool hit(const ray& r, double t_min, double t_max,
             hit_record& rec) const override;

    vec3 center;
    double radius{0.0};
    std::shared_ptr<material> mat_ptr;
};

inline bool sphere::hit(const ray& r, double t_min, double t_max,
                        hit_record& rec) const
{
    const vec3 oc = r.origin() - center;
    const auto a = r.direction().length_squared();
    const auto half_b = dot(oc, r.direction());
    const auto c = oc.length_squared() - radius * radius;
    const auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0)
    {
        const auto root = sqrt(discriminant);
        auto temp = (-half_b - root) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);

            const vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;

            return true;
        }

        temp = (-half_b + root) / a;

        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);

            const vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;

            return true;
        }
    }

    return false;
}

#endif