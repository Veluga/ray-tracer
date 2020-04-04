#include "sphere.hpp"

#include <cmath>

sphere::sphere() {}
sphere::sphere(const vec3 &center, double radius, std::shared_ptr<material> m)
    : center(center), radius(radius), mat_ptr(m) {}

bool sphere::hit(const ray &ray, double t_min, double t_max,
                 hit_record &rec) const {
  vec3 oc = ray.origin() - this->center;
  auto a = ray.direction().length_squared();
  auto half_b = dot(oc, ray.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;
  if (discriminant > 0) {
    auto root = std::sqrt(discriminant);
    auto t = (-half_b - root) / a;
    if (t < t_max && t > t_min) {
      rec.t = t;
      rec.p = ray.at(t);
      rec.set_face_normal(ray, unit_vector(rec.p - this->center));
      rec.mat_ptr = this->mat_ptr;
      return true;
    }
    t = (-half_b + root) / a;
    if (t < t_max && t > t_min) {
      rec.t = t;
      rec.p = ray.at(t);
      rec.set_face_normal(ray, unit_vector(rec.p - this->center));
      rec.mat_ptr = this->mat_ptr;
      return true;
    }
  }
  return false;
}