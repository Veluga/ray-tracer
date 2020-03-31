#include "ray_tracer.hpp"
#include <iostream>

int main() {
  auto v = vec3(1, 1, 1);
  v += v;
  v *= 3.0;
  v.write_color(std::cout);
}
