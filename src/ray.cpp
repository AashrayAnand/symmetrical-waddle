#include "ray.h"

/////////////////////////////////////////////////
//
// Ray: a representation of a colored ray, composed of
// an origin (3-d vector) and some trajectory (a
// direction vector as a function of time)
//
/////////////////////////////////////////////////

// get where the ray is at, at some point in time
point ray::at(const double time) {
    return orig + dir * time;
}

color ray::color() {
    vec3 ray_dir = unit_vec(dir);
    auto t = 0.5 * (ray_dir.y() + 1.0);
    auto v = (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * make_color(0.5, 0.7, 1.0);
    return make_color(v.x(), v.y(), v.z());
}