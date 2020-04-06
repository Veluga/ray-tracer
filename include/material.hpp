#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "hittable.hpp"
#include "raytracer.hpp"

class material {
public:
  virtual bool scatter(const ray &r_in, const hit_record &hit,
                       vec3 &attenuation, ray &scattered) const = 0;
};

class lambertian : public material {
public:
  lambertian(const vec3 &);
  bool scatter(const ray &r_in, const hit_record &hit, vec3 &attenuation,
               ray &scattered) const;
  vec3 albedo;
};

class metal : public material {
public:
  metal(const vec3 &, double);
  bool scatter(const ray &r_in, const hit_record &hit, vec3 &attenuation,
               ray &scattered) const;
  vec3 albedo;
  double fuzz;
};

// A material that never absorbs a ray but always scatters (e.g. glass)
class dielectric : public material {
public:
  dielectric(double);
  bool scatter(const ray &r_in, const hit_record &hit, vec3 &attenuation,
               ray &scattered) const;
  double ref_index;
};

double schlick(double, double);

#endif
