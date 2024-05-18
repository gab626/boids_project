#include "functions.hpp"

#include <cmath>
#include <random>
#include <numeric>

array2 bd::operator+(array2 const& v1, array2 const& v2) {
  return {v1[0] + v2[0], v1[1] + v2[1]};
}

array2 bd::operator-(array2 const& v1, array2 const& v2) {
  return {v1[0] - v2[0], v1[1] - v2[1]};
}

array2 bd::operator*(double c, array2 const& v) { return {c * v[0], c * v[1]}; }

double bd::norm(array2 const& v) {
  return std::sqrt(v[0] * v[0] + v[1] * v[1]);
}

double bd::distance(bd::Boid const& b1, bd::Boid const& b2) {
  return bd::norm(b1.position - b2.position);
}

array2 bd::centerMass(std::vector<Boid*> near) {
  array2 init{};
  array2 center = std::accumulate(near.begin(), near.end(), init, [](array2 const& p, Boid* b) {
                                         return p + b->position;
                                       });
  // for (int i{}; i < 20; i++) center = center + near[i]->position;
  return (1. / near.size() ) * center;
}

void bd::switchPosition(Boid& b) {
  auto x = b.position[0];
  auto y = b.position[1];
  if (x < 0) b.position[0] = x + 800;
  if (x > 800) b.position[0] = x - 800;
  if (y < 0) b.position[1] = y + 800;
  if (y > 800) b.position[1] = y - 800;
}

/* void bd::speedLimit(Boid& b) {
  double actualSpeed = bd::norm(b.velocity);
  if (actualSpeed > b.maxSpeed) {
    double red = actualSpeed / b.maxSpeed;
    b.velocity = red * b.velocity;
  }
} */

array2 bd::randomPosition() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(300, 500);
  array2 position = {static_cast<double>(unif(eng)),
                     static_cast<double>(unif(eng))};
  return position;
}

array2 bd::randomVelocity() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(0, 0);
  array2 velocity = {static_cast<double>(unif(eng)),
                     static_cast<double>(unif(eng))};
  return velocity;
}