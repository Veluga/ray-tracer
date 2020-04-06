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
  // Divide the total by the number of samples and gamma-correct
  // for a gamma of 2.0
  auto r = sqrt(this->e[0] * scale);
  auto g = sqrt(this->e[1] * scale);
  auto b = sqrt(this->e[2] * scale);
  out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1.0, 1.0);
    if (p.length_squared() >= 1)
      continue;
    return p;
  }
}

vec3 random_unit_vector() {
  auto a = random_double(0, 2.0 * pi);
  auto z = random_double(-1.0, 1.0);
  auto r = sqrt(1 - z * z);
  return vec3(r * cos(a), r * sin(a), z);
}

vec3 reflect(const vec3 &v, const vec3 &n) { return v - 2 * dot(v, n) * n; }

vec3 refract(const vec3 &v, const vec3 &n, double etai_over_etat) {
  auto cos_theta = dot(-v, n);
  vec3 r_out_parallel = etai_over_etat * (v + cos_theta * n);
  vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
  return r_out_parallel + r_out_perp;
}