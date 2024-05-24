#include "flight.hpp"

#include <algorithm>
#include <functional>
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

void bd::Flight::updateFlock(std::vector<Boid> const& newValues) {
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
  for (int j{0}; j < par_.N; j++) {
    boidPointers nearIndex;
    boidPointers separationIndex;
    for (int i{}; i < par_.N; i++) {
      if (&flock_[i] != &flock_[j]) {
        if (bd::distance(flock_[j], flock_[i]) < par_.d)
          nearIndex.push_back(&flock_[i]);
        if (bd::distance(flock_[j], flock_[i]) <
            par_.ds)
          separationIndex.push_back(&flock_[i]);
      }
    }

    array2 v1 = bd::separationVelocity(par_.s, separationIndex, flock_[j]);
    array2 v2 = bd::alignmentVelocity(par_.a, nearIndex, flock_[j]);
    array2 v3 = bd::cohesionVelocity(par_.c, nearIndex, flock_[j]);

    newValues.push_back({flock_[j].get_Pos() + (.001 * flock_[j].get_Vel()),
                         flock_[j].get_Vel() + v1 + v2 + v3});
  }

  bd::Flight::updateFlock(newValues);
}