#include "ray_tracer.hpp"
#include <iostream>

void gen_simple_fading(int w, int h) {
  int image_height = h;
  int image_width = w;

  std::cout << "P3\n" << image_height << " " << image_width << "\n255\n";

  for (int i = image_height - 1; i >= 0; i--) {
    std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
    for (int j = 0; j < image_width; j++) {
      vec3 color(static_cast<double>(j) / image_width,
                 static_cast<double>(i) / image_height, 0.2);
      color.write_color(std::cout);
    }
  }
  std::cerr << "\nDone.\n";
}