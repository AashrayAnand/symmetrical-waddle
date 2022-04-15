#include "common.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main () {
    // Camera
    camera c;

    // Objects
    hittable_list objects;

    auto mat_ground = make_shared<lambertian>(make_color(0.8, 0.8, 0.0));
    auto mat_center = make_shared<lambertian>(make_color(0.7, 0.3, 0.3));
    auto mat_l = make_shared<metal>(make_color(0.8, 0.8, 0.8), 0.3);
    auto mat_r = make_shared<metal>(make_color(0.8, 0.6, 0.2), 0.1);

    // Add spheres to objects
    objects.add(make_shared<sphere>(point(0.0, -100.5, -1.0), 100.0, mat_ground));
    objects.add(make_shared<sphere>(point(0.0,    0.0, -1.0),   0.5, mat_center));
    objects.add(make_shared<sphere>(point(-1.0,    0.0, -1.0),   0.5, mat_l));
    objects.add(make_shared<sphere>(point(1.0,    0.0, -1.0),   0.5, mat_r));

    c.render(objects);
}