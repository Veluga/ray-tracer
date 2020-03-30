#include "ray_tracer.hpp"
#include <iostream>

void gen_simple_fading(int w, int h) {
  int image_height = h;
  int image_width = w;

  std::cout << "P3\n" << image_height << " " << image_width << "\n255\n";

  for (int i = image_height - 1; i >= 0; i--) {
    for (int j = 0; j < image_width; j++) {
      auto r = double(j) / image_width;
      auto g = double(i) / image_height;
      auto b = 0.2;
      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);
      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
}