#include "ray.hpp"
#include "vec3.hpp"

#include <cmath>
#include <iostream>

double hit_sphere(const vec3 &center, double radius, const ray &r) {
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-half_b - std::sqrt(discriminant)) / a;
  }
}

vec3 ray_color(const ray &r) {
  auto t = hit_sphere(vec3(0, 0, -1), 0.5, r);
  if (t > 0.0) {
    // Create normal and map to interval [0, 1]
    vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
    return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
  }
  vec3 unit_direction = unit_vector(r.direction());
  t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
  int image_width = 200;
  int image_height = 100;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  for (int i = image_height - 1; i >= 0; i--) {
    std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
    for (int j = 0; j < image_width; j++) {
      auto u = static_cast<double>(j) / image_width;
      auto v = static_cast<double>(i) / image_height;
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      vec3 color = ray_color(r);
      color.write_color(std::cout);
    }
  }
  std::cerr << "\nDone.\n";
}
