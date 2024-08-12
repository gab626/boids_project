#include "functions.hpp"

#include <math.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>

using bd::Boid;
using bd::Cell;

float bd::norm(const vector2& vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float bd::distance(const Boid& firstBoid, const Boid& secondBoid) {
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

float bd::orientation(const vector2& velocity) {
  float angleRadians =
      std::atan2(velocity.y, velocity.x) + M_PI_2f;  // M_PI? è il miglior modo?
  float angleDegrees = angleRadians * 360.f / (2.f * M_PIf);
  return angleDegrees;  // ho dovuto togliere il meno, mi sa che non avevo
                        // capito benissimo come funziona, rivedere
}

bool bd::isBoidInCell(const vector2& position, const Cell& cell) {
  return (position.x >= cell.getCenter().x - cell.getWidth() &&
          position.x <= cell.getCenter().x + cell.getWidth() &&
          position.y >= cell.getCenter().y - cell.getHeight() &&
          position.y <= cell.getCenter().y + cell.getHeight());
}

void bd::linkBoidsToCells(Boid& boid, std::vector<Cell>& grid) {
  auto cellIterator =
      std::find_if(grid.begin(), grid.end(), [&](const Cell& cell) {
        return bd::isBoidInCell(boid.getPosition(), cell);
      });
  Cell* cellPointer = &(*cellIterator);  // non mi piace
  boid.setCellPointer(cellPointer);
  cellPointer->insertBoid(boid);
}

vector2 bd::separationVelocity(float s, const boidPointers& tooNear,
                               const Boid& boid) {
  float tooNearSize = tooNear.size();  // int?
  return std::accumulate(
             tooNear.begin(), tooNear.end(), boid.getPosition() * tooNearSize,
             [](const vector2& p, Boid* b) { return p - b->getPosition(); }) *
         s;
}

vector2 bd::alignmentVelocity(float a, const boidPointers& near,
                              const Boid& boid) {
  float nearSize = near.size();  // int?
  vector2 velocity{};
  if (nearSize >= 1) {
    vector2 mean = std::accumulate(near.begin(), near.end(), vector2{},
                                   [](const vector2& p, Boid* b) {
                                     return p + b->getVelocity();
                                   }) /
                   nearSize;
    velocity = mean - boid.getVelocity();
  }
  return velocity * a;  // implementazione simile a v3
}

vector2 bd::cohesionVelocity(float c, const boidPointers& near,
                             const Boid& boid) {
  float nearSize = near.size();  // int?
  vector2 velocity{};
  if (nearSize >= 1) {
    vector2 center = std::accumulate(
        near.begin(), near.end(), vector2{},
        [](const vector2& p, Boid* b) { return p + b->getPosition(); });
    velocity = (center * (1.f / nearSize) - boid.getPosition());
  }
  return velocity * c;  // implementazione simile a v2
}

vector2 bd::closedSpace(const Boid& boid) {
  vector2 velocity{};
  float x = boid.getPosition().x;
  if (x < 100.f) velocity.x = 100.f - x;
  if (x > 1500.f) velocity.x = 1500.f - x;
  float y = boid.getPosition().y;
  if (y < 100.f) velocity.y = 100.f - y;
  if (y > 800.f) velocity.y = 800.f - y;
  return velocity;
}

void bd::speedLimit(Boid& b, float maximum) {
  float actualSpeed = bd::norm(b.getVelocity());
  if (actualSpeed > maximum) {
    float scaling = maximum / actualSpeed;
    b.setVelocity(b.getVelocity() * scaling);
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