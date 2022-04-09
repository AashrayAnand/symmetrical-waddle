#include "common.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main () {
    // Camera
    camera c;

    // Objects
    hittable_list objects;

    // Add spheres to objects
    objects.add(make_shared<sphere>(point(0, 0, -1), 0.5));
    objects.add(make_shared<sphere>(point(0, -100.5, -1), 100));

    c.render(objects);
}