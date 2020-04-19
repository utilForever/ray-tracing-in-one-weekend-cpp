// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_HITTABLE_LIST_HPP
#define RAY_TRACING_HITTABLE_LIST_HPP

#include "hittable.hpp"

#include <memory>
#include <utility>
#include <vector>

class hittable_list final : public hittable
{
 public:
    hittable_list() = default;
    hittable_list(std::shared_ptr<hittable> object)
    {
        add(std::move(object));
    }

    void clear()
    {
        objects.clear();
    }

    void add(std::shared_ptr<hittable>&& object)
    {
        objects.emplace_back(object);
    }

    bool hit(const ray& r, double t_min, double t_max,
             hit_record& rec) const override;

    std::vector<std::shared_ptr<hittable>> objects;
};

inline bool hittable_list::hit(const ray& r, double t_min, double t_max,
                               hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif