#include "functions.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

using bd::Boid;

array2 bd::operator+(array2 const& v1, array2 const& v2) {
  return {v1[0] + v2[0], v1[1] + v2[1]};
}

array2 bd::operator-(array2 const& v1, array2 const& v2) {
  return {v1[0] - v2[0], v1[1] - v2[1]};
}

array2 bd::operator*(float c, array2 const& v) { return {c * v[0], c * v[1]}; }

float bd::norm(array2 const& v) { return std::sqrt(v[0] * v[0] + v[1] * v[1]); }

float bd::distance(Boid const& b1, Boid const& b2) {
  return bd::norm(b1.getPosition() - b2.getPosition());
}

array2 bd::separationVelocity(float s, boidPointers const& tooNear,
                              Boid const& boid) {
  return s * std::accumulate(
                 tooNear.begin(), tooNear.end(),
                 tooNear.size() * boid.getPosition(),
                 [](array2 const& p, Boid* b) { return p - b->getPosition(); });
}

array2 bd::alignmentVelocity(float a, boidPointers const& near,
                             Boid const& boid) {
  array2 velocity{};
  if (near.size() >= 1) {
    array2 mean = std::accumulate(
        near.begin(), near.end(), array2{},
        [](array2 const& p, Boid* const& b) { return p + b->getVelocity(); });
    velocity = a * ((1. / near.size()) * mean - boid.getVelocity());
  }
  return velocity;  // implementazione simile a v3
}

array2 bd::cohesionVelocity(float c, boidPointers const& near,
                            Boid const& boid) {
  array2 velocity{};
  if (near.size() >= 1) {
    array2 center = std::accumulate(
        near.begin(), near.end(), array2{},
        [](array2 const& p, Boid* const& b) { return p + b->getPosition(); });
    velocity = c * ((1. / near.size()) * center - boid.getPosition());
  }
  return velocity;  // implementazione simile a v2
}

void bd::toroidalSpace(Boid& b) {
  auto x = b.getPositionX();
  auto y = b.getPositionY();
  if (x < 0) b.setPositionX(x + 1000);
  if (x > 1000) b.setPositionX(x - 1000);
  if (y < 0) b.setPositionY(y + 1000);
  if (y > 1000) b.setPositionY(y - 1000);
}

void bd::speedLimit(Boid& b, float ms) {
  float actualSpeed = bd::norm(b.getVelocity());
  if (actualSpeed > ms) {
    float red = ms / actualSpeed;
    b.setVelocity(red * b.getVelocity());
  }
}

array2 bd::randomPosition() {  // provare algoritmi
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<float> unif(0, 800);
  array2 position = {unif(eng), unif(eng)};
  return position;
}

array2 bd::randomVelocity() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<float> unif(-500, 500);
  array2 velocity = {unif(eng), unif(eng)};
  return velocity;
}