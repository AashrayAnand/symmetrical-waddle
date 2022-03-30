#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"

using namespace std;

int main () {
    // Constants
    const double aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const char* f_name = "./images/out.ppm";

    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * aspect_ratio;
    const double focal_length = 1.0;

    // origin and bottom_left_corner make up parts of the screen which we base
    // rendering on, along with the viewport defined above
    point origin(0, 0, 0);
    vec3 horizontal(viewport_width, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    auto bottom_left_corner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focal_length);

    // Target
    ofstream out_ppm;
    out_ppm.open(f_name);

    // When using ppm file format, need to prepend the image content
    // with P3, to indicate PPM, and the image width and height, and 255
    // to indicate the maximum color, e.g.
    //
    // P3
    // 256 256
    // 255
    // .......
    out_ppm << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    // Iterate pixels in rows, from left to right, top to bottom
    for (auto j = img_height - 1; j >= 0; j--) {
        if (j % (img_height / 10) == 0) { std::cout << j << " Lines remaining\n"; }
        for (auto i = 0; i < img_width; i++) {
            double u = double (i) / (img_width - 1);
            double v = double(j) / (img_height - 1);

            // Create ray, with origin at the center of the screen, and direction defined
            // as fractions of horizontal and vertical vectors, as proportions of i and j
            // relative to the width and height of the screen
            vec3 direction = bottom_left_corner + u * horizontal + v * vertical - origin;
            ray r(origin, direction);

            // Create pixel for each pass, write to file (in form of "x y z" (x,y,z in range 0-255))
            color pixel = r.color();
            out_ppm << pixel;
        }
    }
}