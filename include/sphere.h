#pragma once
// A sphere is defined as a hittable object with
// a sphere-equation defined shape.
#include "common.h"
#include "hittable.h"

class sphere : public hittable {
public:
    sphere() {}
    sphere(point center, double radius, shared_ptr<material> mats): 
        center(center), radius(radius), mat_ptr(mats) {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    point c() const {return center;}
    double r() const {return radius;}
private:
    point center;
    double radius;

    // Used to implement the material type for the sphere, when
    // indicating in a hit record its type
    shared_ptr<material> mat_ptr;
};

// populate a record for a hit, for the given ray, sphere center, and hit time
void record_hit(hit_record& record, const ray& ray, double hit_time);

// Determine the outward normal and whether a ray hits the front/back of a surface
void set_face_norm(hit_record& record, const ray& ray, const vec3& outward_normal);