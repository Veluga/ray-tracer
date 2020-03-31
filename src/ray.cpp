#include "ray_tracer.hpp"

ray::ray(){};

ray::ray(const vec3 &origin, const vec3 &direction)
    : orig(origin), dir(direction) {}

vec3 ray::origin() const { return this->orig; }

vec3 ray::direction() const { return this->dir; }

vec3 ray::at(double t) const { return this->orig + t * this->dir; }