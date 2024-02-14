#include "boid.hpp"

#include <cmath>

vector2 bd::operator+(vector2 const& v1, vector2 const& v2) {
  double x = v1[0] + v2[0];
  double y = v1[1] + v2[1];
  return vector2{x, y};
};

vector2 bd::operator*(double c, vector2 const& v) {
  double x = c * v[0];
  double y = c * v[1];
  return vector2{x, y};
};

double bd::norm(vector2 v) {
  double x2 = v[0] * v[0];
  double y2 = v[1] * v[1];
  return std::sqrt(x2 + y2);
};

bd::Boid::Boid(vector2 p, vector2 v) : position_(p), velocity_(v){};

double bd::Boid::distance(vector2 p1, vector2 p2) const {
  return norm(p1 + (-1) * p2);
};

/* vector2 bd::Boid::vSeparation() const {};
vector2 bd::Boid::vAlignment() const {};
vector2 bd::Boid::vCohesion() const {}; */