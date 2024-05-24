#include "functions.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

array2 bd::operator+(array2 const& v1, array2 const& v2) {
  return {v1[0] + v2[0], v1[1] + v2[1]};
}

array2 bd::operator-(array2 const& v1, array2 const& v2) {
  return {v1[0] - v2[0], v1[1] - v2[1]};
}

array2 bd::operator*(float c, array2 const& v) { return {c * v[0], c * v[1]}; }

float bd::norm(array2 const& v) { return std::sqrt(v[0] * v[0] + v[1] * v[1]); }

float bd::distance(bd::Boid const& b1, bd::Boid const& b2) {
  return bd::norm(b1.get_Pos() - b2.get_Pos());
}

/* bool bd::checkDistance(bd::Boid const& boid, bd::Boid const& otherBoid,
                       float d) {
  return (&boid != &otherBoid && bd::distance(boid, otherBoid) < d);
} */

void bd::findNear(bd::Boid& mainBoid, std::vector<bd::Boid>& boidVector,
                          float d, boidPointers nearBoids) {
  std::for_each(boidVector.begin(), boidVector.end(),
                [&mainBoid, d, &nearBoids](bd::Boid otherBoid) {
                  if (&mainBoid != &otherBoid) {
                    if (bd::distance(mainBoid, otherBoid) < d)
                      nearBoids.push_back(&otherBoid);
                  }
                });
}

array2 bd::separationVelocity(float s, boidPointers const& tooNear,
                              bd::Boid const& boid) {
  return s * std::accumulate(
                 tooNear.begin(), tooNear.end(),
                 tooNear.size() * boid.get_Pos(),
                 [](array2 const& p, bd::Boid* b) { return p - b->get_Pos(); });
}

array2 bd::alignmentVelocity(float a, boidPointers const& near,
                             bd::Boid const& boid) {
  array2 velocity{};
  if (near.size() >= 1) {
    array2 mean = std::accumulate(
        near.begin(), near.end(), array2{},
        [](array2 const& p, bd::Boid* const& b) { return p + b->get_Vel(); });
    velocity = a * ((1. / near.size()) * mean - boid.get_Vel());
  }
  return velocity;  // implementazione simile a v3
}

array2 bd::cohesionVelocity(float c, boidPointers const& near,
                            bd::Boid const& boid) {
  array2 velocity{};
  if (near.size() >= 1) {
    array2 center = std::accumulate(
        near.begin(), near.end(), array2{},
        [](array2 const& p, bd::Boid* const& b) { return p + b->get_Pos(); });
    velocity = c * ((1. / near.size()) * center - boid.get_Pos());
  }
  return velocity;  // implementazione simile a v2
}

void bd::toroidalSpace(bd::Boid& b) {
  auto x = b.get_Pos()[0];
  auto y = b.get_Pos()[1];
  if (x < 0) b.set_PosX(x + 800);
  if (x > 800) b.set_PosX(x - 800);
  if (y < 0) b.set_PosY(y + 800);
  if (y > 800) b.set_PosY(y - 800);
}

void bd::speedLimit(bd::Boid& b, float ms) {
  float actualSpeed = bd::norm(b.get_Vel());
  if (actualSpeed > ms) {
    float red = ms / actualSpeed;
    b.set_Vel(red * b.get_Vel());
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
  std::uniform_real_distribution<float> unif(-200, 200);
  array2 velocity = {unif(eng), unif(eng)};
  return velocity;
}