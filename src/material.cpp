#include "material.hpp"
#include "raytracer.hpp"

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

dielectric::dielectric(double ref_index) : ref_index(ref_index) {}

bool dielectric::scatter(const ray &r_in, const hit_record &hit,
                         vec3 &attenuation, ray &scattered) const {
  attenuation = vec3(1.0, 1.0, 1.0);
  double etai_over_etat =
      hit.front_face ? 1.0 / this->ref_index : this->ref_index;
  vec3 unit_direction = unit_vector(r_in.direction());
  double cos_theta = ffmin(dot(-unit_direction, hit.normal), 1.0);
  double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
  if (etai_over_etat * sin_theta > 1.0 ||
      random_double() < schlick(cos_theta, etai_over_etat)) {
    // Must reflect
    vec3 reflected = reflect(unit_direction, hit.normal);
    scattered = ray(hit.p, reflected);
    return true;
  }
  vec3 refracted = refract(unit_direction, hit.normal, etai_over_etat);
  scattered = ray(hit.p, refracted);
  return true;
}

double schlick(double cosine, double ref_idx) {
  auto r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow(1 - cosine, 5);
}