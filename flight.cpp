#include "flight.hpp"

#include <algorithm>
#include <functional>
#include <nanoflann.hpp>  // da provare e testare
#include <numeric>
#include <vector>

#include "functions.hpp"

bd::Flight::Flight() {
  flock_.resize(par_.N);
  std::generate(flock_.begin(), flock_.end(), []() {
    return bd::Boid(bd::randomPosition(), bd::randomVelocity());
  });
}

bd::Flight::~Flight() {}

int bd::Flight::get_N() const { return par_.N; }

std::vector<bd::Boid> bd::Flight::get_flock() const { return flock_; }

void bd::Flight::updateFlock(std::vector<Boid>& newValues) {
  std::move(newValues.begin(), newValues.end(), flock_.begin());
  std::for_each(flock_.begin(), flock_.end(), [=](bd::Boid& b) {
    bd::speedLimit(b, par_.maxSpeed);
    bd::toroidalSpace(b);
  });
}

void bd::Flight::evolve() {
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

    newValues.push_back(
        {j.get_Pos() + (.001 * j.get_Vel()), j.get_Vel() + v1 + v2 + v3});
  }

  bd::Flight::updateFlock(newValues);
}