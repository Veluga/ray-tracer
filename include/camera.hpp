#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "raytracer.hpp"

class camera {
public:
  camera(vec3, vec3, vec3, double, double, double, double);
  ray get_ray(double, double);

  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u, v, w;
  double lens_radius;
};

#endif