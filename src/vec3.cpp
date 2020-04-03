#include "raytracer.hpp"
#include <cmath>

vec3::vec3() : e{0, 0, 0} {}
vec3::vec3(double x, double y, double z) : e{x, y, z} {}

double vec3::x() const { return this->e[0]; }
double vec3::y() const { return this->e[1]; }
double vec3::z() const { return this->e[2]; }

vec3 vec3::operator-() const {
  return vec3(-this->e[0], -this->e[1], -this->e[2]);
}

double vec3::operator[](int i) const { return this->e[i]; }
double &vec3::operator[](int i) { return this->e[i]; }

vec3 &vec3::operator+=(const vec3 &v) {
  this->e[0] += v.e[0];
  this->e[1] += v.e[1];
  this->e[2] += v.e[2];
  return *this;
}

vec3 &vec3::operator*=(const double t) {
  this->e[0] *= t;
  this->e[1] *= t;
  this->e[2] *= t;
  return *this;
}

vec3 &vec3::operator/=(const double t) { return *this *= 1 / t; }

double vec3::length_squared() const {
  return this->e[0] * this->e[0] + this->e[1] * this->e[1] +
         this->e[2] * this->e[2];
}

double vec3::length() const { return std::sqrt(this->length_squared()); }

void vec3::write_color(std::ostream &out, int samples_per_pixel) {
  auto scale = 1.0 / samples_per_pixel;
  out << static_cast<int>(256 * clamp(this->e[0] * scale, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(this->e[1] * scale, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(this->e[2] * scale, 0.0, 0.999)) << '\n';
}