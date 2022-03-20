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

// vector dot product
double dot(const vec3 &self, const vec3 &other) {
    return self.v[0] * other.v[0] + self.v[1] * other.v[1] + self.v[2] * other.v[2];
}

// vector cross product
vec3 cross(const vec3 &self, const vec3 &other) {
    return vec3(self.v[1] * other.v[2] - self.v[2] * other.v[1],
                self.v[2] * other.v[0] - self.v[0] * other.v[2],
                self.v[0] * other.v[1] - self.v[1] * other.v[0]);
}

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