#include "hittable_list.hpp"

hittable_list::hittable_list() {}
hittable_list::hittable_list(std::shared_ptr<hittable> object) {
  this->add(object);
}

void hittable_list::clear() { this->objects.clear(); }

void hittable_list::add(std::shared_ptr<hittable> object) {
  this->objects.push_back(object);
}

bool hittable_list::hit(const ray &ray, double t_min, double t_max,
                        hit_record &rec) const {
  hit_record tmp_record;
  bool hit_anything = false;
  double closest_hit = t_max;
  for (const auto &object : this->objects) {
    if (object->hit(ray, t_min, closest_hit, tmp_record)) {
      hit_anything = true;
      closest_hit = tmp_record.t;
      rec = tmp_record;
    }
  }
  return hit_anything;
}