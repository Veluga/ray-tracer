#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "vec3.hpp"

class ray {
public:
  ray();
  ray(const vec3 &, const vec3 &);

  vec3 origin() const;
  vec3 direction() const;

  vec3 at(double) const;

  vec3 orig;
  vec3 dir;
};

#endif