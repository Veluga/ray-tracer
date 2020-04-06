#include "camera.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "raytracer.hpp"
#include "sphere.hpp"

#include <cmath>
#include <iostream>
#include <vector>

vec3 ray_color(const ray &r, hittable_list world, int depth) {
  hit_record hit;

  if (depth <= 0) {
    return vec3(0, 0, 0);
  }

  if (world.hit(r, 0.001, infinity, hit)) {
    ray scattered;
    vec3 attenuation;
    if (hit.mat_ptr->scatter(r, hit, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth - 1);
    }
    return vec3(0, 0, 0);
  }

  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
  hittable_list world;

  world.add(std::make_shared<sphere>(
      vec3(0, -1000, 0), 1000,
      std::make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

  int i = 1;
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
      if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = vec3::random() * vec3::random();
          world.add(std::make_shared<sphere>(
              center, 0.2, std::make_shared<lambertian>(albedo)));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = vec3::random(.5, 1);
          auto fuzz = random_double(0, .5);
          world.add(std::make_shared<sphere>(
              center, 0.2, std::make_shared<metal>(albedo, fuzz)));
        } else {
          // glass
          world.add(std::make_shared<sphere>(
              center, 0.2, std::make_shared<dielectric>(1.5)));
        }
      }
    }
  }

  world.add(std::make_shared<sphere>(vec3(0, 1, 0), 1.0,
                                     std::make_shared<dielectric>(1.5)));

  world.add(std::make_shared<sphere>(
      vec3(-4, 1, 0), 1.0, std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));

  world.add(std::make_shared<sphere>(
      vec3(4, 1, 0), 1.0, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

  return world;
}

int main() {
  const int image_width = 800;
  const int image_height = 400;
  const int samples_per_pixel = 50;
  const int max_depth = 50;
  const auto aspect_ratio = double(image_width) / image_height;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  auto world = random_scene();

  vec3 lookfrom(13, 2, 3);
  vec3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10;
  auto aperture = 0.1;
  camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
  for (int i = image_height - 1; i >= 0; i--) {
    std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
    for (int j = 0; j < image_width; j++) {
      vec3 color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; s++) {
        auto u = (j + random_double()) / image_width;
        auto v = (i + random_double()) / image_height;
        ray r = cam.get_ray(u, v);
        color += ray_color(r, world, max_depth);
      }
      color.write_color(std::cout, samples_per_pixel);
    }
  }
  std::cerr << "\nDone.\n";
}
