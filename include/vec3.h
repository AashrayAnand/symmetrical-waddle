#pragma once
#include <cmath>
#include <iostream>

using std::sqrt;
using std::ostream;

enum vec_t {
    COLOR,
    POINT,
    VEC
};

// clamp x to either min or max
inline double clamp(double x, double min, double max) {
    return x < min ? min : (x > max ? max : x);
}

class vec3 {
public:
    vec3(): v_type(VEC), v{0, 0, 0} {}
    vec3(double x, double y, double z): v_type(VEC), v{x, y, z} {}
    vec3(vec_t v_type, double x, double y, double z): v_type(v_type), v{x, y, z} {}

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

    friend ostream& operator<<(ostream &out, const vec3& self) {
        if (self.v_type == COLOR) {
            return out  << static_cast<int> (255.999 * clamp(self.v[0], 0.0, 0.999)) << ' ' 
                    << static_cast<int> (255.999 * clamp(self.v[1], 0.0, 0.999)) << ' ' 
                    << static_cast<int> (255.999 * clamp(self.v[2], 0.0, 0.999)) << ' ';
        }
        return out << self.v[0] << ' ' << self.v[1] << ' ' << self.v[2] << ' ';
    }

    // For 3-d location (vector of x/y/z coordinates), we can get
    // the length as the sqrt of the sum of squares of each component
    double length() const;
    // Get the sum of squares of each component of the vector
    double length_squared() const;

    vec3 as_color() {
        v_type = COLOR;
        return *this;
    }
    
    // vector
    double v[3];

    // vector type
    vec_t v_type;
};

// vector arithmetic operators
vec3 operator+(const vec3 &self, const vec3 &other);
vec3 operator-(const vec3 &self, const vec3 &other);
vec3 operator*(const vec3 &self, const vec3 &other);
vec3 operator*(const vec3 &self, const double multiplier);
vec3 operator*(const double multiplier, const vec3 &self);
vec3 operator/(const vec3 &self, const double divisor);

// vector dot product
double dot(const vec3 &self, const vec3 &other);

// vector cross product
vec3 cross(const vec3 &self, const vec3 &other);

// unit vector
vec3 unit_vec(const vec3 &self);

using color = vec3;
using point = vec3;

color make_color(double x, double y, double z);
point make_point(double x, double y, double z);