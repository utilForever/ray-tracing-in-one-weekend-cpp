// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_MATERIAL_HPP
#define RAY_TRACING_MATERIAL_HPP

#include "common.hpp"

struct hit_record;

class material
{
 public:
    virtual ~material() = default;

    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         vec3& attenuation, ray& scattered) const = 0;
};

#endif