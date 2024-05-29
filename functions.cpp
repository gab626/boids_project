#include "functions.hpp"

#include <math.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

using bd::Boid;

float bd::norm(vector2 const& velocity) {
  return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

float bd::distance(Boid const& firstBoid, Boid const& secondBoid) {
  return bd::norm(firstBoid.getPosition() - secondBoid.getPosition());
}

float bd::orientation(vector2 const& velocity) {
  float angleRadians =
      std::atan2(velocity.y, velocity.x) + M_PI_2f;  // M_PI? è il miglior modo?
  float angleDegrees = angleRadians * 360 / (2 * M_PIf);
  return angleDegrees;  // ho dovuto togliere il meno, mi sa che non avevo
                        // capito benissimo come funziona, rivedere
}

vector2 bd::separationVelocity(float s, boidPointers const& tooNear,
                               Boid const& boid) {
  float tooNearSize = tooNear.size();
  return std::accumulate(
             tooNear.begin(), tooNear.end(), boid.getPosition() * tooNearSize,
             [](vector2 const& p, Boid* b) { return p - b->getPosition(); }) *
         s;
}

vector2 bd::alignmentVelocity(float a, boidPointers const& near,
                              Boid const& boid) {
  float nearSize = near.size();
  vector2 velocity{};
  if (nearSize >= 1) {
    vector2 mean = std::accumulate(
        near.begin(), near.end(), vector2{},
        [](vector2 const& p, Boid* const& b) { return p + b->getVelocity(); });
    velocity = (mean * (1.f / nearSize) - boid.getVelocity()) * a;
  }
  return velocity;  // implementazione simile a v3
}

vector2 bd::cohesionVelocity(float c, boidPointers const& near,
                             Boid const& boid) {
  float nearSize = near.size();
  vector2 velocity{};
  if (nearSize >= 1) {
    vector2 center = std::accumulate(
        near.begin(), near.end(), vector2{},
        [](vector2 const& p, Boid* const& b) { return p + b->getPosition(); });
    velocity = (center * (1.f / nearSize) - boid.getPosition()) * c;
  }
  return velocity;  // implementazione simile a v2
}

void bd::toroidalSpace(Boid& b) {
  auto x = b.getPosition().x;
  auto y = b.getPosition().y;
  if (x < 0) b.setPositionX(x + 1000);
  if (x > 1000) b.setPositionX(x - 1000);
  if (y < 0) b.setPositionY(y + 1000);
  if (y > 1000) b.setPositionY(y - 1000);
}

void bd::speedLimit(Boid& b, float ms) {
  float actualSpeed = bd::norm(b.getVelocity());
  if (actualSpeed > ms) {
    float red = ms / actualSpeed;
    b.setVelocity(b.getVelocity() * red);
  }
}

vector2 bd::randomPosition() {  // provare algoritmi
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<float> unif(0, 1000);
  vector2 position = {unif(eng), unif(eng)};
  return position;
}

vector2 bd::randomVelocity() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_real_distribution<float> unif(-500, 500);
  vector2 velocity = {unif(eng), unif(eng)};
  return velocity;
}