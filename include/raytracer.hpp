#ifndef RAYTRACER_RT_MAIN_H
#define RAYTRACER_RT_MAIN_H

#include <limits>
#include <random>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions

inline double degree_to_radians(double degrees) { return degrees * pi / 180; }

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  // Equivalent lambda 'binding'
  // static auto rand_generator = [&]() { return distribution(generator); };
  static std::function<double()> rand_generator =
      std::bind(distribution, generator);
  return rand_generator();
}

inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
  if (x > max)
    return max;
  if (x < min)
    return min;
  return x;
}

#include "ray.hpp"
#include "vec3.hpp"

#endif