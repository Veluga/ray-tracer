#include "camera.hpp"

camera::camera() {
  this->lower_left_corner = vec3(-2.0, -1.0, -1.0);
  this->origin = vec3(0.0, 0.0, 0.0);
  this->horizontal = vec3(4.0, 0.0, 0.0);
  this->vertical = vec3(0.0, 2.0, 0.0);
}

ray camera::get_ray(double u, double v) {
  return ray(this->origin,
             lower_left_corner + u * horizontal + v * vertical - origin);
}