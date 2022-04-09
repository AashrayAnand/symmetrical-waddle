#pragma once
#include "vec3.h"
#include "ray.h"

// A hittable is defined as an object which can possibly
// have volume, and may be hit by a ray. We can compose
// hittables and rays to have multiple shapes and colors
// in a ray-traced image

// the hit point and t define the point on the hittable's surface
// where it is hit by the ray, the normal is 
struct hit_record {
    point hit_point;
    vec3 normal;
    double t;
    bool front_face;
};

class hittable {
public:
    // We need to define when a hittable is hit by a ray
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};