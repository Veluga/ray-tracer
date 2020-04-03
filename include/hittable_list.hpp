#ifndef RAYTRACER_HITTABLE_LIST_H
#define RAYTRACER_HITTABLE_LIST_H

#include "hittable.hpp"

#include <vector>

class hittable_list : public hittable {
public:
  hittable_list();
  hittable_list(std::shared_ptr<hittable>);
  void clear();
  void add(std::shared_ptr<hittable>);
  bool hit(const ray &ray, double t_min, double t_max, hit_record &rec) const;
  std::vector<std::shared_ptr<hittable>> objects;
};

#endif