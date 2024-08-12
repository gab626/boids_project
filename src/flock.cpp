#include "flock.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

#include "functions.hpp"

using bd::Boid;
using bd::Flock;
// using bd::Quadtree;
// using bd::Rectangle;

void Flock::setupGrid() {
  grid_.resize(144);
  vector2 center{50.f, 50.f};
  // int key{0};
  std::generate(grid_.begin(), grid_.end(), [&]() {
    Cell cell;
    cell.setCenter(center);
    // cell.setKey(key);
    center.x += 100.f;
    if (center.x > 1600.f) {
      center.x = 50.f;
      center.y += 100.f;
    }
    // key++;
    return cell;
  });
}

Flock::Flock() {}

Flock::Flock(sf::Color color) {
  flock_.resize(parameters_.numberBoids);
  std::generate(flock_.begin(), flock_.end(), [&]() { return Boid(color); });
  Flock::setupGrid();
  std::for_each(flock_.begin(), flock_.end(),
                [&](Boid& boid) { bd::linkBoidsToCells(boid, grid_); });
}

Flock::~Flock() {}

int Flock::getNumberBoids() const { return parameters_.numberBoids; }

std::vector<Boid> Flock::getFlock() const { return flock_; }

void Flock::updateFlock(std::vector<Boid>& newBoids) {
  std::move(newBoids.begin(), newBoids.end(), flock_.begin());
  std::for_each(flock_.begin(), flock_.end(),
                [&](Boid& boid) {  // cattura con this? come funziona?
                  bd::speedLimit(boid, parameters_.maxSpeed);
                });
}

/* void Flock::saveStatistics(float distanceMean = 0.f, float distanceStd = 0.f,
                           float speedMean = 0.f, float speedStd = 0.f) {
  statistics_.distanceMean = distanceMean;
  statistics_.distanceStandardDeviation = distanceStd;
  statistics_.speedMean = speedMean;
  statistics_.speedStandardDeviation = speedStd;
} */

/* void Flock::printStatistics() {  // cout stampa in int?
  std::cout << "Distance mean: " << statistics_.distanceMean
            << "      Distance std: " << statistics_.distanceStandardDeviation
            << "\nSpeed mean: " << statistics_.speedMean
            << "      Speed std: " << statistics_.speedStandardDeviation
            << '\n';
} */

void Flock::evolve() {
  std::vector<Boid> newBoids;
  // std::vector<float> distances;
  // std::vector<float> speeds;
  for (Boid const& j : flock_) {  // CREARE QUAD TREE PER MIGLIORARE QUA
    boidPointers nearBoidsPointers;
    boidPointers separationBoidsPointers;
    for (Boid& i : flock_) {
      if (&i != &j) {
        float distance = bd::distance(j, i);
        if (distance < parameters_.distance) nearBoidsPointers.push_back(&i);
        if (distance < parameters_.distanceSeparation)
          separationBoidsPointers.push_back(&i);
        // distances.push_back(distance);
      }
    }

    vector2 separationVelocity = bd::separationVelocity(
        parameters_.separationCoefficient, separationBoidsPointers, j);
    vector2 alignmentVelocity = bd::alignmentVelocity(
        parameters_.alignmentCoefficient, nearBoidsPointers, j);
    vector2 cohesionVelocity = bd::cohesionVelocity(
        parameters_.cohesionCoefficient, nearBoidsPointers, j);
    vector2 wallsVelocity = bd::closedSpace(j);

    vector2 newPosition =
        j.getPosition() + (j.getVelocity() * parameters_.deltaTime);
    vector2 newVelocity = j.getVelocity() + separationVelocity +
                          alignmentVelocity + cohesionVelocity + wallsVelocity;

    // speeds.push_back(bd::norm(newVelocity));

    newBoids.push_back({newPosition, newVelocity, j.getShape().getFillColor()});
  }

  /* float distanceMean = bd::mean(distances);
  float speedMean = bd::mean(speeds);
  std::for_each(distances.begin(), distances.end(), [=](float v) {
    return (v - distanceMean) * (v - distanceMean);
  });
  std::for_each(speeds.begin(), speeds.end(),
                [=](float v) { return (v - speedMean) * (v - speedMean); });
  float distanceStd = bd::standardDeviation(distances);
  float speedStd = bd::standardDeviation(speeds); */

  // Flock::saveStatistics(distanceMean, distanceStd, speedMean, speedStd);
  // Flock::printStatistics();
  Flock::updateFlock(newBoids);
}