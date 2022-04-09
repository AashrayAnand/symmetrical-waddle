#pragma once
#include "common.h"
#include "hittable.h"

// Camera encapsulates the view configuration for the ray tracer, including
// the viewport and aspect ratio values, as well as the points and vectors representing
// the screen dimensions, origin, and corner 
class camera {
public:
    camera():
        aspect_ratio(16.0 / 9.0),
        width_(400),
        viewport_height(2.0), 
        focal_length(1.0),
        samples_per_pixel(100)
        {
            height_ = static_cast<int>(width_ / aspect_ratio);
            out_file.open("./images/out.ppm"),
            origin = make_point(0, 0, 0);
            depth = vec3(0, 0, focal_length);
            vertical = vec3(0, viewport_height, 0);
            horizontal = vec3(viewport_width, 0, 0);
            viewport_width = viewport_height * aspect_ratio;
            bottom_left_corner = origin - (horizontal / 2) - (vertical / 2) - depth;

            // When using ppm file format, need to prepend the image content
            // with P3, to indicate PPM, and the image width and height, and 255
            // to indicate the maximum color, e.g.
            //
            // P3
            // 256 256
            // 255
            // .......
            out_file << "P3\n" << width_ << ' ' << height_ << "\n255\n";
        }
    
    int width() {return width_;}
    int height() {return height_;}
    
    void render(const hittable& objects);
    void next(const hittable& objects, int i, int j);
private:
    // Camera dimensions
    double aspect_ratio;
    int width_;
    int height_;
    ofstream out_file;

    // These values define the 3-dimensional space which makes up the image
    double viewport_height = 2.0;
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 1.0;

    // origin and bottom_left_corner make up parts of the screen which we base
    // rendering on, along with the viewport defined above
    point origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 depth;
    point bottom_left_corner;

    // For anti-aliasing, normalizing each pixel as an average of many samples
    int samples_per_pixel;
};