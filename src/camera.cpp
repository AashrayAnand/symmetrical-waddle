#include "camera.h"
#include "sphere.h"

color ray_color(const ray& r, const hittable& obj, int depth) {
    // First, check if the ray is going to hit a sphere
    // at some point
    hit_record hr;

    // terminate recursion
    if (depth <= 0) {
        return make_color(0, 0, 0);
    }

    // If the ray hits some point on the object's surface
    if (obj.hit(r, 0, infin, hr)) {
        // Apply 1/2 normal to white as color
        point target = hr.hit_point + hr.normal + rand_in_unit_sphere();
        return (0.5 * ray_color(ray(hr.hit_point, target - hr.hit_point), obj, depth -1)).as_color();
    }
    // Get unit vector for the ray's direction
    vec3 ray_dir = unit_vec(r.direction());

    // t will be some value between 0 and 1, since taking the
    // unit vector in the direction of our direction vector will
    // normalize each value of the vector to the range [-1, 1]
    auto t = 0.5 * (ray_dir.y() + 1.0);

    // Return a linear interpolation over time (and as a function of
    // the y-value of the ray's direction) from white to blue
    return ((1.0 - t) * make_color(1.0, 1.0, 1.0) /* white */ 
                + t * make_color(0.5, 0.7, 1.0)).as_color(); /* blue */ 
}

void camera::render(const hittable& objects) {
    // Iterate pixels in rows, from left to right, top to bottom
    for (auto j = height_ - 1; j >= 0; j--) {
        if (j % (height_ / 10) == 0) { cout << j << " Lines remaining\n"; }
        for (auto i = 0; i < width_; i++) {
            next(objects, i, j);
        }
    }
}

// Samples a set of randomly distributed vectors, roughly in the direction
// of this pixels position on the screen, 
void camera::next(const hittable& objects, int i, int j) {
    color pixel(0, 0, 0);
    for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + rand_d()) / (width_-1);
        auto v = (j + rand_d()) / (height_-1);
        vec3 direction = bottom_left_corner + u * horizontal + v * vertical - origin;
        ray r(origin, direction);
        pixel += ray_color(r, objects, 50 /* max depth */);
    }

    // scale down the pixel, averaging on the number of samples
    auto scale = 1.0 / samples_per_pixel;
    pixel *= scale;

    out_file << pixel.as_color();
}