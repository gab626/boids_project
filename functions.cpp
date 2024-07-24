#include "functions.hpp"

#include <math.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

using bd::Boid;

float bd::norm(vector2 const& vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float bd::distance(Boid const& firstBoid, Boid const& secondBoid) {
  return bd::norm(firstBoid.getPosition() - secondBoid.getPosition());
}

float bd::mean(std::vector<float> values) {
  return std::accumulate(values.begin(), values.end(), 0) / values.size();
}

float bd::standardDeviation(std::vector<float> valuesSquared) {
  return std::sqrt(
      std::accumulate(valuesSquared.begin(), valuesSquared.end(), 0) /
      (valuesSquared.size() - 1));
}

float bd::orientation(vector2 const& velocity) {
  float angleRadians =
      std::atan2(velocity.y, velocity.x) + M_PI_2f;  // M_PI? è il miglior modo?
  float angleDegrees = angleRadians * 360.f / (2.f * M_PIf);
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

vector2 bd::closedSpace(Boid const& boid) {
  float ws = 3.f;  // wall separation
  vector2 velocity{};
  float x = boid.getPosition().x;
  if (x < 100.f) velocity.x = ws * (100.f - x);
  if (x > 1500.f) velocity.x = ws * (1500.f - x);
  float y = boid.getPosition().y;
  if (y < 100.f) velocity.y = ws * (100.f - y);
  if (y > 800.f) velocity.y = ws * (800.f - y);
  return velocity;
}

void bd::speedLimit(Boid& b, float ms) {
  float actualSpeed = bd::norm(b.getVelocity());
  if (actualSpeed > ms) {
    float red = ms / actualSpeed;
    b.setVelocity(b.getVelocity() * red);
  }
}

float bd::randomFloat(float minimum, float maximum) {
  std::random_device seed;
  std::default_random_engine engine(seed());
  std::uniform_real_distribution<float> unif(minimum, maximum);
  return unif(engine);
}

vector2 bd::randomVelocity(float minimum, float maximum) {
  float rho = bd::randomFloat(minimum, maximum);
  float theta = bd::randomFloat(0, 2.f * M_PI);
  return {rho * std::cos(theta), rho * std::sin(theta)};
}