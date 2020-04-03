#include "hittable_list.hpp"
#include "raytracer.hpp"
#include "sphere.hpp"

#include <cmath>
#include <iostream>

vec3 ray_color(const ray &r, hittable_list world) {
  struct hit_record hit;
  if (world.hit(r, 0, infinity, hit)) {
    return 0.5 * (hit.normal + vec3(1, 1, 1));
  } else {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  int image_width = 200;
  int image_height = 100;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  hittable_list world;
  world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(vec3(0, -100.5, -1), 100));

  for (int i = image_height - 1; i >= 0; i--) {
    std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
    for (int j = 0; j < image_width; j++) {
      auto u = static_cast<double>(j) / image_width;
      auto v = static_cast<double>(i) / image_height;
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      vec3 color = ray_color(r, world);
      color.write_color(std::cout);
    }
  }
  std::cerr << "\nDone.\n";
}
