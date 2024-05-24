#include "flight.hpp"

#include <algorithm>
#include <functional>
#include <nanoflann.hpp>  // da provare e testare
#include <numeric>
#include <vector>

#include "functions.hpp"

using bd::Boid;
using bd::Flight;

Flight::Flight() {
  flock_.resize(par_.N);
  std::generate(flock_.begin(), flock_.end(), []() {
    return Boid(bd::randomPosition(), bd::randomVelocity());
  });
}

Flight::~Flight() {}

int Flight::getN() const { return par_.N; }

std::vector<Boid> Flight::getFlock() const { return flock_; }

void Flight::updateFlock(std::vector<Boid>& newValues) {
  std::move(newValues.begin(), newValues.end(), flock_.begin());
  std::for_each(flock_.begin(), flock_.end(), [=](Boid& b) {
    bd::speedLimit(b, par_.maxSpeed);
    bd::toroidalSpace(b);
  });
}

void Flight::evolve() {
  std::vector<Boid> newValues;
  // newValues.resize(par_.N);
  // std::transform(flock_.begin(), flock_.end(), newValues_.begin(), []() {});
  for (Boid const& j : flock_) {  // CERCARE KD TREE PER MIGLIORARE QUA
    boidPointers nearIndex;
    boidPointers separationIndex;
    for (Boid& i : flock_) {
      if (&i != &j) {
        if (bd::distance(j, i) < par_.d) nearIndex.push_back(&i);
        if (bd::distance(j, i) < par_.ds) separationIndex.push_back(&i);
      }
    }

    array2 v1 = bd::separationVelocity(par_.s, separationIndex, j);
    array2 v2 = bd::alignmentVelocity(par_.a, nearIndex, j);
    array2 v3 = bd::cohesionVelocity(par_.c, nearIndex, j);

    newValues.push_back({j.getPosition() + (.001 * j.getVelocity()),
                         j.getVelocity() + v1 + v2 + v3});
  }

  Flight::updateFlock(newValues);
}