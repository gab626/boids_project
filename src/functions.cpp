#include "functions.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <random>

using bd::Boid;
using bd::Cell;
using bd::Grid;

float bd::norm(const vector2& vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float bd::distance(const Boid& firstBoid,
                   const Boid& secondBoid) {  // rimettere toroidal distance?
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
  return angleDegrees;
}

void bd::toroidalSpace(vector2& position) {  // potrebbe non funzionare così
  /* if (position.x < 0) {
    position.x += 1600.f;
  }
  if (position.x > 1600.f) {
    position.x -= 1600.f;
  }
  if (position.y < 0) {
    position.y += 900.f;
  }
  if (position.y > 900.f) {
    position.y -= 900.f;
  } */
  position.x = std::fmod(position.x + 1600.f, 1600.f);
  assert(position.x >= 0.f && position.x <= 1600.f);
  position.y = std::fmod(position.y + 900.f, 900.f);
  assert(position.y >= 0.f && position.y <= 900.f);
}

bool bd::isInCell(const vector2& position, const Cell& cell) {
  return (position.x >= cell.getCenter().x - cell.getWidth() &&
          position.x <= cell.getCenter().x + cell.getWidth() &&
          position.y >= cell.getCenter().y - cell.getHeight() &&
          position.y <= cell.getCenter().y + cell.getHeight());
}

void bd::linkBoidsToCells(Boid& boid, Grid& grid) {
  cellVector gridCells = grid.getCellVector();
  assert(gridCells.size() == 144);
  vector2 boidPosition = boid.getPosition();
  auto cellIterator = std::find_if(
      gridCells.begin(), gridCells.end(),
      [&](const Cell& cell) { return bd::isInCell(boidPosition, cell); });
  assert(cellIterator != gridCells.end());
  Cell* cellPointer = &(*cellIterator);  // non mi piace
  boid.setCellPointer(cellPointer);
  cellPointer->insertBoid(boid);
}

std::vector<vector2> bd::findNearCellsCenters(const Cell& cell) {
  vector2 position = cell.getCenter();
  std::vector<vector2> nearCellsCenters;
  assert(nearCellsCenters.empty());
  nearCellsCenters.push_back(position + vector2{0.f, -100.f});     // north
  nearCellsCenters.push_back(position + vector2{0.f, 100.f});      // south
  nearCellsCenters.push_back(position + vector2{-100.f, 0.f});     // west
  nearCellsCenters.push_back(position + vector2{100.f, 0.f});      // east
  nearCellsCenters.push_back(position + vector2{100.f, -100.f});   // north-east
  nearCellsCenters.push_back(position + vector2{-100.f, -100.f});  // north-west
  nearCellsCenters.push_back(position + vector2{100.f, 100.f});    // south-east
  nearCellsCenters.push_back(position + vector2{-100.f, 100.f});   // south-west
  std::for_each(nearCellsCenters.begin(), nearCellsCenters.end(),
                [](vector2& position) { bd::toroidalSpace(position); });
  assert(nearCellsCenters.size() == 8);
  return nearCellsCenters;
}

cellPointers bd::findNearCellsPointers(const Cell& cell, const Grid& grid) {
  std::vector<vector2> nearCellsCenters = bd::findNearCellsCenters(cell);
  assert(nearCellsCenters.size() == 8);
  cellVector gridCells = grid.getCellVector();
  assert(gridCells.size() == 144);
  cellPointers nearCellsPointers;
  assert(nearCellsPointers.empty());
  // nearCellsPointers.resize(8);
  std::for_each(
      nearCellsCenters.begin(),  // provare poi con transform
      nearCellsCenters.end(),    // NESTED ALGORITHMS ???
      [&](const vector2& cellCenter) {
        auto cellIterator = std::find_if(
            gridCells.begin(), gridCells.end(),
            [&](const Cell& cell) { return bd::isInCell(cellCenter, cell); });
        assert(cellIterator != gridCells.end());
        Cell* cellPointer = &(*cellIterator);
        //  return cellPointer;
        nearCellsPointers.push_back(cellPointer);
      });
  assert(nearCellsPointers.size() == 8);
  return nearCellsPointers;
}

boidPointers bd::findNearBoids(const Boid& mainBoid, float distance) {
  Cell* mainCell = mainBoid.getCellPointer();
  cellPointers nearCells = mainCell->getNearCells();
  assert(nearCells.size() == 8);
  nearCells.push_back(mainCell);
  assert(nearCells.size() == 9);
  boidPointers nearBoids;
  std::for_each(nearCells.begin(), nearCells.end(), [&](Cell* cell) {
    boidPointers boidsToCheck = cell->getBoidsInCell();
    std::for_each(boidsToCheck.begin(), boidsToCheck.end(),
                  [&](Boid* otherBoid) {
                    if (&mainBoid != otherBoid) {
                      if (bd::distance(mainBoid, *otherBoid) < distance) {
                        nearBoids.push_back(otherBoid);
                      }
                    }
                  });
  });
  return nearBoids;
}

/* boidPointers bd::findSeparationBoids(const boidPointers& nearBoids,
                                     float separationDistance) {
  boidPointers separationBoids;
  std::for_each(nearBoids.begin(), nearBoids.end(), []() {});
} */

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