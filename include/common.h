#pragma once

// Libraries
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Common
#include "vec3.h"
#include "ray.h"

// Usings
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::sqrt;
using std::ostream;
using std::ofstream;
using std::numeric_limits;
using std::uniform_real_distribution;
using std::mt19937;
using std::cout;
using std::endl;

// Constants
const double infin = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Util Functions
inline double deg_to_rad (double deg) {
    return deg * pi / 180.0;
}

// random number in range [0-1]
inline double rand_d() {
    static uniform_real_distribution<double> dist(0.0, 1.0);
    static mt19937 gen;
    return dist(gen);
}

// random number in range [min-max]
inline double rand_range(double min, double max) {
    return min + (max - min) * rand_d();
}