#include "sphere.h"

// populate a record for a hit, for the given ray, sphere center, and hit time
void record_hit(hit_record& record, const ray& ray, double hit_time) {
    record.t = hit_time;
    record.hit_point = ray.at(hit_time);
}

// indicate accordingly whether a ray is hitting a surface
// from the inside, or the outside, which can be determined by whether
// the ray's direction is towards or away from the surface's outward normal
void set_face_norm(hit_record& record, const ray& ray, const vec3& outward_normal) {
    record.front_face = dot(ray.direction(), outward_normal) < 0.0;
    record.normal = record.front_face ? outward_normal : -1 * outward_normal;
}

// A vector from the center of a sphere C to any point P has equation P - C.
// This means, for P = (x, y, z), (P - C) ^ 2 = (x - Cx) ^ 2 + (y - Cy) ^ 2 + (z - Cz) ^ 2.
// If a ray hits some point on a sphere, then there exists real values such that
// (P - C) ^ 2 = R ^ 2 (since all points on a sphere satisfy this). Therefore, we just need
// to apply the quadratic formula to (P(t) - C) ^ 2 - R ^ 2 = 0
//
// which becomes (A + Bt - C) ^ 2 - R ^ 2 = 0
// -> A^2 + ABt - AC + ABt + (Bt)^2 - CBt - AC - CBt + C^2 - R^2 = 0
// -> A ^ 2 + 2ABt - 2AC - 2CBt + C ^ 2 (Bt)^2 - R ^ 2 = 0
// -> (Bt)^2 2Bt(A - C) ((A - C) ^ 2 - R ^ 2) = 0
// -> direction squared is a
// -> 2 * direction dot (origin - center) is b
// -> (origin - center) squared - R ^ 2 is c
// 
bool sphere::hit(const ray& ray, double t_min, double t_max, hit_record& record) const {
    vec3 center_to_orig = ray.origin() - center;
    double a = ray.direction().length_squared();
    double b = dot(ray.direction(), center_to_orig);
    double c = center_to_orig.length_squared() - radius * radius;

    // since b has a factor 2 above, discriminant simplifies from
    // (2 * dot(dir, co)) ^ 2 - 4 * a * c -> dot(dir, co) - a * c,
    // also pulls out the 2 from the denominator and from -b
    double discrim = b * b - a * c; 

    // Exists some real roots, now check if in the valid range of t
    if (discrim > 0) {
        double t1 = (-b - sqrt(discrim)) / a;
        if (t1 > t_min && t1 < t_max) {
            record_hit(record, ray, t1);
            vec3 outward_normal = (record.hit_point - center) / radius;
            set_face_norm(record, ray, outward_normal);
            record.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}