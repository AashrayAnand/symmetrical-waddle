/////////////////////////////////////////////////
//
// Ray: a representation of a ray, composed of
// an origin (3-d vector) and trajectory (a
// function of a direction vector over time)
//
/////////////////////////////////////////////////
#include "ray.h"

// Solve for any roots of the quadratic formed by
// the circle's center point and radius, along with the
// ray in question, to determine if the ray hits the sphere

// The quadratic formed from a ray and a circle is of the form
//
// t^2 * B ^ 2 + 2 * t * B * (A - C) + (A - C) ^ 2 = R ^ 2
// where R is radius, t is time, B is the ray's direction, A is
// the ray's origin, and C is the center of the circle.
//
// for the quadratic formula of form -b +- sqrt(b^2 - 4 * a * c) / 2 * a
// we have
// a = B ^2
// b = 2 * B * (A - C)
// c = (A - C) ^ 2 - R ^ 2
//
// the ray hits the sphere so long as there is a real solution, which is
// when b ^ 2 - 4 * a * c = (2 * B * (A - C)) ^ 2 - 4 * B ^ 2 * (A - C) ^ 2 > 0
double ray::hit_point(const point& center, const double radius) {
    vec3 center_to_orig = origin() - center;
    double a = dot(direction(), direction());
    double b = 2 * dot(direction(), center_to_orig);
    double c = dot(center_to_orig, center_to_orig) - radius * radius;
    double discrim = b * b - 4 * a * c;
    if (discrim > 0) {
        return (-b - sqrt(discrim)) / (2.0 * a);
    }
    return -1.0;
}

// get where the ray is at, at some point in time
point ray::at(const double time) {
    return orig + dir * time;
}

color ray::color() {
    // First, check if the ray is going to hit a sphere
    // at some point
    double hp = hit_point(make_point(0, 0, -1.0), 0.5);

    if (hp > 0) {
        // get surface normal as the vector from the sphere's center
        // to the point where the ray hits the sphere
        vec3 surface_norm = unit_vec(at(hp)) - vec3(0, 0, -1.0);

        // Use surface normal to linearly shade the surface
        // of the sphere, based on the surface normal of each
        // point on the sphere
        return (0.5 * vec3(
            surface_norm.x() + 1, 
            surface_norm.y() + 1, 
            surface_norm.z() + 1)).as_color();
    }
    // Get unit vector for the ray's direction
    vec3 ray_dir = unit_vec(dir);

    // t will be some value between 0 and 1, since taking the
    // unit vector in the direction of our direction vector will
    // normalize each value of the vector to the range [-1, 1]
    auto t = 0.5 * (ray_dir.y() + 1.0);

    // Return a linear interpolation over time (and as a function of
    // the y-value of the ray's direction) from white to blue
    return ((1.0 - t) * make_color(1.0, 1.0, 1.0) /* white */ 
                + t * make_color(0.5, 0.7, 1.0) /* blue */
            ).as_color(); 
}