#include "ray_tracer.hpp"
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

void vec3::write_color(std::ostream &out) {
  out << static_cast<int>(255.999 * this->e[0]) << ' '
      << static_cast<int>(255.999 * this->e[1]) << ' '
      << static_cast<int>(255.999 * this->e[2]) << '\n';
}