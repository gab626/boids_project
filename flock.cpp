#include "flock.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <nanoflann.hpp>  // da provare e testare
#include <numeric>
#include <vector>

#include "functions.hpp"

using bd::Boid;
using bd::Flock;

Flock::Flock() {
  flock_.resize(par_.N);
  std::generate(flock_.begin(), flock_.end(), []() { return Boid(); });
}

Flock::~Flock() {}

int Flock::getN() const { return par_.N; }

std::vector<Boid> Flock::getFlock() const { return flock_; }

void Flock::updateFlock(std::vector<Boid>& newValues) {
  std::move(newValues.begin(), newValues.end(), flock_.begin());
  std::for_each(flock_.begin(), flock_.end(),
                [&](Boid& b) {  // cattura con this? come funziona?
                  bd::speedLimit(b, par_.maxSpeed);
                });
}

void Flock::saveStatistics(float distanceMean = 0.f, float distanceStd = 0.f,
                           float speedMean = 0.f, float speedStd = 0.f) {
  statistics.distanceMean = distanceMean;
  statistics.distanceStandardDeviation = distanceStd;
  statistics.speedMean = speedMean;
  statistics.speedStandardDeviation = speedStd;
}

void Flock::printStatistics() {  // cout stampa in int?
  std::cout << "Distance mean: " << statistics.distanceMean
            << "      Distance std: " << statistics.distanceStandardDeviation
            << "\nSpeed mean: " << statistics.speedMean
            << "      Speed std: " << statistics.speedStandardDeviation << '\n';
}

void Flock::evolve() {
  std::vector<Boid> newValues;
  std::vector<float> distances;
  std::vector<float> speeds;
  // newValues.resize(par_.N);
  // std::transform(flock_.begin(), flock_.end(), newValues_.begin(), []() {});
  for (Boid const& j : flock_) {  // CREARE QUAD TREE PER MIGLIORARE QUA
    boidPointers nearIndex;
    boidPointers separationIndex;
    for (Boid& i : flock_) {
      if (&i != &j) {
        float distance = bd::distance(j, i);
        if (distance < par_.d) nearIndex.push_back(&i);
        if (distance < par_.ds) separationIndex.push_back(&i);
        distances.push_back(distance);
      }
    }

    vector2 v1 = bd::separationVelocity(par_.s, separationIndex, j);
    vector2 v2 = bd::alignmentVelocity(par_.a, nearIndex, j);
    vector2 v3 = bd::cohesionVelocity(par_.c, nearIndex, j);
    vector2 vw = bd::closedSpace(j);

    auto newPosition = j.getPosition() + (j.getVelocity() * par_.deltaT);
    auto newVelocity = j.getVelocity() + v1 + v2 + v3 + vw;

    speeds.push_back(bd::norm(newVelocity));

    newValues.push_back({newPosition, newVelocity});
  }

  float distanceMean = bd::mean(distances);
  float speedMean = bd::mean(speeds);
  std::for_each(distances.begin(), distances.end(), [=](float v) {
    return (v - distanceMean) * (v - distanceMean);
  });
  std::for_each(speeds.begin(), speeds.end(),
                [=](float v) { return (v - speedMean) * (v - speedMean); });
  float distanceStd = bd::standardDeviation(distances);
  float speedStd = bd::standardDeviation(speeds);

  Flock::saveStatistics(distanceMean, distanceStd, speedMean, speedStd);
  // Flock::printStatistics();
  Flock::updateFlock(newValues);
}