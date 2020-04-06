#include "camera.hpp"

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect,
               double aperture, double focus_dist) {
  this->origin = lookfrom;
  lens_radius = aperture / 2;

  auto theta = degree_to_radians(vfov);
  auto half_height = tan(theta / 2);
  auto half_width = aspect * half_height;
  this->w = unit_vector(lookfrom - lookat);
  this->u = unit_vector(cross(vup, w));
  this->v = cross(w, u);
  this->lower_left_corner = origin - half_width * focus_dist * u -
                            half_height * focus_dist * v - focus_dist * w;

  this->horizontal = 2 * half_width * focus_dist * u;
  this->vertical = 2 * half_height * focus_dist * v;
}

ray camera::get_ray(double s, double t) {
  vec3 rd = lens_radius * random_in_unit_disk();
  vec3 offset = this->u * rd.x() + this->v * rd.y();

  return ray(this->origin + offset, lower_left_corner + s * horizontal +
                                        t * vertical - origin - offset);
}