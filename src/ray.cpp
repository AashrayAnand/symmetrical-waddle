#include "ray.h"

point ray::position(const int time) {
    return start_point + (direction * time);
}