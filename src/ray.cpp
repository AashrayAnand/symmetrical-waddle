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
    double a = direction().length_squared();
    double b = dot(direction(), center_to_orig);
    double c = center_to_orig.length_squared() - radius * radius;

    // since b has a factor 2 above, discriminant simplifies from
    // (2 * dot(dir, co)) ^ 2 - 4 * a * c -> dot(dir, co) - a * c,
    // also pulls out the 2 from the denominator and from -b
    double discrim = b * b - a * c;
    return discrim > 0 ? (-b - sqrt(discrim)) / a : -1.0;
}

// get where the ray is at, at some point in time
point ray::at(const double time) const {
    return orig + dir * time;
}