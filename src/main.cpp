#include <iostream>
#include <fstream>

#include "vec3.h"
#include "ray.h"

using namespace std;

int main () {
    // Constants
    const int img_width = 256;
    const int img_height = 256;
    const char* f_name = "./images/out.ppm";

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
        if (j % 10 == 0) { std::cout << j << " Lines remaining\n"; }
        for (auto i = 0; i < img_width; i++) {
            // Create pixel for each pass, write to file (in form of "x y z" (x,y,z in range 0-255))
            color pixel(double(i) / (img_width - 1), double(j) / (img_height - 1), 0.25);
            out_ppm << pixel;
        }
    }
}