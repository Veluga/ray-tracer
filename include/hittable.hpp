#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "ray.hpp"
#include "vec3.hpp"

struct hit_record {
  vec3 p;
  vec3 normal;
};

class hittable {
public:
  virtual bool hit(const ray &ray, double t_min, double t_max,
                   hit_record &rec) const = 0;
};

#endif