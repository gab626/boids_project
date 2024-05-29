#include "flock.hpp"

#include <algorithm>
#include <functional>
#include <nanoflann.hpp>  // da provare e testare
#include <numeric>
#include <vector>

#include "functions.hpp"

using bd::Boid;
using bd::Flock;

Flock::Flock() {
  flock_.resize(par_.N);
  std::generate(flock_.begin(), flock_.end(), []() {
    return Boid();
  });
}

Flock::~Flock() {}

int Flock::getN() const { return par_.N; }

std::vector<Boid> Flock::getFlock() const { return flock_; }

void Flock::updateFlock(std::vector<Boid>& newValues) {
  std::move(newValues.begin(), newValues.end(), flock_.begin());
  std::for_each(flock_.begin(), flock_.end(),
                [&](Boid& b) {  // cattura con this? come funziona?
                  bd::speedLimit(b, par_.maxSpeed);
                  bd::toroidalSpace(b);
                });
}

void Flock::evolve() {
  std::vector<Boid> newValues;
  // newValues.resize(par_.N);
  // std::transform(flock_.begin(), flock_.end(), newValues_.begin(), []() {});
  for (Boid const& j : flock_) {  // CREARE QUAD TREE PER MIGLIORARE QUA
    boidPointers nearIndex;
    boidPointers separationIndex;
    for (Boid& i : flock_) {
      if (&i != &j) {
        if (bd::distance(j, i) < par_.d) nearIndex.push_back(&i);
        if (bd::distance(j, i) < par_.ds) separationIndex.push_back(&i);
      }
    }

    vector2 v1 = bd::separationVelocity(par_.s, separationIndex, j);
    vector2 v2 = bd::alignmentVelocity(par_.a, nearIndex, j);
    vector2 v3 = bd::cohesionVelocity(par_.c, nearIndex, j);

    newValues.push_back({j.getPosition() + (j.getVelocity() * par_.deltaT),
                         j.getVelocity() + v1 + v2 + v3});
  }

  Flock::updateFlock(newValues);
}