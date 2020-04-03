#include "camera.hpp"
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
  int samples_per_pixel = 100;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  hittable_list world;
  world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(vec3(0, -100.5, -1), 100));
  camera cam;
  for (int i = image_height - 1; i >= 0; i--) {
    std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
    for (int j = 0; j < image_width; j++) {
      vec3 color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; s++) {
        auto u = (j + random_double()) / image_width;
        auto v = (i + random_double()) / image_height;
        ray r = cam.get_ray(u, v);
        color += ray_color(r, world);
      }
      color.write_color(std::cout, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}
