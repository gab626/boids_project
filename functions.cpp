#include "functions.hpp"

#include <cmath>
#include <numeric>
#include <random>

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

double bd::distance(bd::Boid& b1, bd::Boid& b2) {
  return bd::norm(b1.getPos() - b2.getPos());
}

array2 bd::meanVelocity(std::vector<bd::Boid*> const& near) {
  array2 init{};
  array2 mean = std::accumulate(
      near.begin(), near.end(), init,
      [](array2 const& p, bd::Boid* b) { return p + b->getVel(); });
  return (1. / near.size()) * mean;
}

array2 bd::centerMass(std::vector<bd::Boid*> const& near) {
  array2 init{};
  array2 center = std::accumulate(
      near.begin(), near.end(), init,
      [](array2 const& p, bd::Boid* b) { return p + b->getPos(); });
  return (1. / near.size()) * center;
}

void bd::toroidalSpace(bd::Boid& b) {
  auto x = b.getPos()[0];
  auto y = b.getPos()[1];
  if (x < 0) b.setPosX(x + 800);
  if (x > 800) b.setPosX(x - 800);
  if (y < 0) b.setPosY(y + 800);
  if (y > 800) b.setPosY(y - 800);
}

void bd::speedLimit(bd::Boid& b) {
  double actualSpeed = bd::norm(b.getVel());
  if (actualSpeed > b.getMaxSpeed()) {
    double red = b.getMaxSpeed() / actualSpeed;
    b.setVel(red * b.getVel());
  }
}

array2 bd::randomPosition() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(0, 800);
  array2 position = {static_cast<double>(unif(eng)),
                     static_cast<double>(unif(eng))};
  return position;
}

array2 bd::randomVelocity() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(-200, 200);
  array2 velocity = {static_cast<double>(unif(eng)),
                     static_cast<double>(unif(eng))};
  return velocity;
}