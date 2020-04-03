#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "raytracer.hpp"

class camera {
public:
  ray get_ray(double, double);

  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
};

#endif