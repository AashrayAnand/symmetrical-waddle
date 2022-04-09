#include "hittable_list.h"

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // iterate over hittables, changing upper bound every time
    // we hit some hittable, ending with the tightest bound
    double t_closest = t_max;
    bool hit_something = false;

    for (const auto& object: objects) {
        if (object->hit(r, t_min, t_closest, rec)) {
            hit_something = true;
            t_closest = rec.t;
        }
    }

    return hit_something;
}