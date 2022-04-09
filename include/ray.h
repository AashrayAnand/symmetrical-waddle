#pragma once
#include "vec3.h"

// A ray is a composition of a point, and a direction, where the ray
// is formed by progressing the point across a line, which is defined
// by a function of time. e.g. P(t) = A + tB defines a line for a
// point which starts at A, and travels in direction B over time t
class ray {
public:
    ray(point start, vec3 direction): orig(start), dir(direction) {}

    point at(const double time) const;
    point origin() const {return orig;};
    vec3 direction() const {return dir;}
private:
    point orig;
    vec3 dir;

    double hit_point(const point& center, const double radius);
};