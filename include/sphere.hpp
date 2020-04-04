#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "hittable.hpp"

class sphere : public hittable {
public:
  sphere();
  sphere(const vec3 &, double, std::shared_ptr<material>);
  bool hit(const ray &ray, double t_min, double t_max, hit_record &rec) const;

  vec3 center;
  double radius;
  std::shared_ptr<material> mat_ptr;
};

#endif