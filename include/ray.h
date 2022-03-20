#pragma once
#include <cmath>
#include <iostream>

#include "vec3.h"

// A ray is a composition of a point, and a direction, where the ray
// is formed by progressing the point across a line, which is defined
// by a function of time. e.g. P(t) = A + tB defines a line for a
// point which starts at A, and travels in direction B over time t
class ray {
    ray(point p, vec3 v): start_point(p), direction(v) {}

    point position(const int time);
    point start_point;
    vec3 direction;
};