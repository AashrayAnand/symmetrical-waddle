#pragma once
#include <cmath>
#include <iostream>

using std::sqrt;
using std::ostream;

class vec3 {
public:
    vec3(): v{0, 0, 0} {}
    vec3(double x, double y, double z): v{x, y, z} {}

    // getters
    double x() const {return v[0];}
    double y() const {return v[1];}
    double z() const {return v[2];}

    // Array indexing
    double operator[](const int i) const { return v[i];}
    double& operator[](const int i) { return v[i];}

    // Arithmetic operators
    vec3 operator-();
    vec3& operator+=(const vec3 &);
    vec3& operator*=(const double);
    vec3& operator/=(const double);

    // For 3-d location (vector of x/y/z coordinates), we can get
    // the length as the sqrt of the sum of squares of each component
    double length() const;
    // Get the sum of squares of each component of the vector
    double length_squared() const;
    
    // vector
    double v[3];
};

// Both colors and points are represented by 3-vectors, define as child classes rather than 
// with aliases, so we ensure type checking when passing points/colors
class color : vec3 {
public:
    color(): vec3(0, 0, 0) {}
    color(double x, double y, double z): vec3(x, y, z) {}
    // Output
    friend ostream& operator<<(ostream &out, const color& self) {
        return out  << static_cast<int> (255.999 * self.v[0]) << ' ' 
                    << static_cast<int> (255.999 * self.v[1]) << ' ' 
                    << static_cast<int> (255.999 * self.v[2]) << ' ';
    }
};

class point : vec3 {
public:
    point(): vec3(0, 0, 0) {}
    point(double x, double y, double z): vec3(x, y, z) {}
    // Output
    friend ostream& operator<<(ostream &out, const point& self) {
        return out  << self.v[0] << ' ' << self.v[1] << ' ' << self.v[2] << ' ';
    }
};