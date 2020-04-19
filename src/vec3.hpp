// Copyright (c) 2020 Chris Ohk

// I am making my contributions/submissions to this project solely in my
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on Ray Tracing in One Weekend book.
// References: https://raytracing.github.io

#ifndef RAY_TRACING_VEC3_HPP
#define RAY_TRACING_VEC3_HPP

#include <algorithm>
#include <iostream>

class vec3
{
 public:
    vec3() : e{0, 0, 0}
    {
        // Do nothing
    }

    vec3(double e0, double e1, double e2) : e{e0, e1, e2}
    {
        // Do nothing
    }

    vec3 operator-() const
    {
        return vec3{-e[0], -e[1], -e[2]};
    }

    double operator[](int i) const
    {
        return e[i];
    }

    double& operator[](int i)
    {
        return e[i];
    }

    vec3& operator+=(const vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3& operator*=(const double t)
    {
        e[0] += t;
        e[1] += t;
        e[2] += t;

        return *this;
    }

    vec3& operator/=(const double t)
    {
        return *this *= (1 / t);
    }

    double x() const
    {
        return e[0];
    }

    double y() const
    {
        return e[1];
    }

    double z() const
    {
        return e[2];
    }

    double length() const
    {
        return std::sqrt(length_squared());
    }

    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    void write_color(std::ostream& out, int samples_per_pixel)
    {
        // Divide the color total by the number of samples.
        const auto scale = 1.0 / samples_per_pixel;
        auto r = scale * e[0];
        auto g = scale * e[1];
        auto b = scale * e[2];

        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << '\n';
    }

    double e[3];
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline vec3 operator*(double t, const vec3& v)
{
    return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline vec3 operator*(const vec3& v, double t)
{
    return t * v;
}

inline vec3 operator/(vec3 v, double t)
{
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v)
{
    return {u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]};
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

#endif