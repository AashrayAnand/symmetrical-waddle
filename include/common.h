#pragma once

// Libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Common
#include "vec3.h"
#include "ray.h"

// Usings
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::ostream;
using std::ofstream;
using std::cout;
using std::endl;

using std::sqrt;
using std::numeric_limits;
using std::uniform_real_distribution;
using std::mt19937;

// Constants
const double infin = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Util Functions
inline double deg_to_rad (double deg) {
    return deg * pi / 180.0;
}

// random number in range [0-1]
inline double rand_d() {
    static uniform_real_distribution<double> dist(0.0, 1.0);
    static mt19937 gen;
    return dist(gen);
}

// random number in range [min-max]
inline double rand_range(double min, double max) {
    return min + (max - min) * rand_d();
}

inline vec3 rand_v() {return vec3(rand_d(), rand_d(), rand_d());}

inline vec3 rand_v(double min, double max) {
    return vec3(rand_range(min, max), rand_range(min, max), rand_range(min, max));
}

// For diffuse/opaque materials, we don't want to let rays pass through and apply
// their color to the material the same as clear ones. We can simulate
// the ray bouncing off the surface by getting a random vector in the unit sphere (the
// sphere made by the unit normal either into or out of the sphere at the ray's
// hit point).
inline vec3 rand_in_unit_sphere() {
    while(true) {
        auto v = rand_v(-1, 1);
        if (v.length_squared() >= 1) continue;
        return v;
    }
}

// For true lambertian reflection, can't just pick a random point
// in the unit sphere, we need to pick a point on the surface
// of the unit sphere, offset along surface normal
inline vec3 random_unit_vector() {
    return unit_vec(rand_in_unit_sphere());
}

// Below computes the reflection of a vector v off
// a surface at a hit point with unit normal vecotr n.
// v is going into the surface at this point and thus the
// result is v's normal direction in going up but v dot n
// (2x to account for reversing v)
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-1 * uv, n), 1.0);
    vec3 r_o_perpend = etai_over_etat * (uv + cos_theta * n);
    vec3 r_o_parallel = -sqrt(fabs(1.0 - r_o_perpend.length_squared())) * n;
    return r_o_perpend + r_o_parallel;
}