#include "material.hpp"

lambertian::lambertian(const vec3 &a) : albedo(a) {}

bool lambertian::scatter(const ray &r_in, const hit_record &hit,
                         vec3 &attentuation, ray &scattered) const {
  vec3 scattered_direction = hit.normal + random_unit_vector();
  scattered = ray(hit.p, scattered_direction);
  attentuation = this->albedo;
  return true;
}

metal::metal(const vec3 &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool metal::scatter(const ray &r_in, const hit_record &hit, vec3 &attentuation,
                    ray &scattered) const {
  vec3 reflected = reflect(unit_vector(r_in.direction()), hit.normal);
  scattered = ray(hit.p, reflected + this->fuzz * random_in_unit_sphere());
  attentuation = albedo;
  return (dot(reflected, hit.normal) > 0);
}