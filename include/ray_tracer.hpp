#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>

void gen_simple_fading(int, int);

class vec3 {
public:
  vec3();
  vec3(double, double, double);

  double x() const;
  double y() const;
  double z() const;

  vec3 operator-() const;
  double operator[](int i) const;
  double &operator[](int i);

  vec3 &operator+=(const vec3 &);
  vec3 &operator*=(const double t);
  vec3 &operator/=(const double t);

  double length() const;
  double length_squared() const;
  void write_color(std::ostream &);

  double e[3];
};

#endif