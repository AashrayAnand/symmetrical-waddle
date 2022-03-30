#include "vec3.h"

// Arithmetic operators
vec3 vec3::operator-() {return vec3(-v[0], -v[1], -v[2]);}

vec3& vec3::operator+=(const vec3 & other) {
    v[0] += other.x();
    v[1] += other.y();
    v[2] += other.z();
    return *this;
}

vec3& vec3::operator*=(const double multiplier) {
    v[0] *= multiplier;
    v[1] *= multiplier;
    v[2] *= multiplier;
    return *this;
}

vec3& vec3::operator/=(const double divisor) {
    *this *= (1 / divisor);
    return *this;
}

vec3 operator+(const vec3 &self, const vec3 &other) {
    return vec3(self.v[0] + other.v[0], self.v[1] + other.v[1], self.v[2] + other.v[2]);
}

vec3 operator-(const vec3 &self, const vec3 &other) {
    return vec3(self.v[0]- other.v[0], self.v[1] - other.v[1], self.v[2] - other.v[2]);
}

vec3 operator*(const vec3 &self, const vec3 &other) {
    return vec3(self.v[0] * other.v[0], self.v[1] * other.v[1], self.v[2] * other.v[2]);
}

vec3 operator*(const vec3 &self, const double multiplier) {
    return vec3(self.v[0] * multiplier, self.v[1] * multiplier, self.v[2] * multiplier);
}

vec3 operator*(const double multiplier, const vec3 &self) {
    return self * multiplier;
}

vec3 operator/(const vec3 &self, const double divisor) {
    return self * (1 / divisor);
}

// vector dot product. This is just a value that is the element-wise
// multiplication of two vectors. If the value is negative, the angle
// between the two vectors is greater than 90 deg. If positive, less than
// 90 deg. If zero, 90 deg. exactly.
double dot(const vec3 &self, const vec3 &other) {
    return self.v[0] * other.v[0] + self.v[1] * other.v[1] + self.v[2] * other.v[2];
}

// vector cross product
vec3 cross(const vec3 &self, const vec3 &other) {
    return vec3(self.v[1] * other.v[2] - self.v[2] * other.v[1],
                self.v[2] * other.v[0] - self.v[0] * other.v[2],
                self.v[0] * other.v[1] - self.v[1] * other.v[0]);
}

// get the unit vector in the direction of a given vector. The
// unit vector will be vector of length 1, in the same direction
// as the original vector. e.g. for (1,2,3), we get the length as
// the square root of the vector squared, which is sqrt(14), then
// the unit vec is (1/sqrt(14), 2/sqrt(14), 3/sqrt(14)). This vector
// will have the same direction as the original, since each value of 
// the vector is the product of the original vector value and the same
// value (1/sqrt(14)), and we have a vector of the form (a/d, b/d, c/d)
// where a^2 + b^2 + c^2 = d^2, meaning the length (sqrt of vector squared)
// is sqrt(d^2 / d^2) = 1
vec3 unit_vec(const vec3 &self) {
    return self / self.length();
}

// For 3-d location (vector of x/y/z coordinates), we can get
// the length as the sqrt of the sum of squares of each component
double vec3::length() const {
    return sqrt(length_squared());
}

// Get the sum of squares of each component of the vector
double vec3::length_squared() const {
    return pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2);
}

color make_color(double x, double y, double z) {return vec3(COLOR, x, y, z);}
point make_point(double x, double y, double z) {return vec3(POINT, x, y, z);}