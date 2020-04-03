#ifndef RAYTRACER_RT_MAIN_H
#define RAYTRACER_RT_MAIN_H

#include "ray.hpp"
#include "vec3.hpp"

#include <limits>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degree_to_radians(double degrees) { return degrees * pi / 180; }

inline double ffmain(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

#endif