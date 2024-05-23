#include "flight.hpp"

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

#include "functions.hpp"

bd::Flight::Flight() {
  for (int i{}; i < par_.N; i++) {
    bd::Boid b;
    bd::Boid b0{{}, {}};
    flock_.push_back(b);
    newValues_.push_back(b0);
  }
}

bd::Flight::~Flight() {}

int bd::Flight::get_N() const { return par_.N; }

std::vector<bd::Boid> bd::Flight::get_flock() const { return flock_; }

void bd::Flight::evolve() {
  for (int j{0}; j < par_.N; j++) {  // trova e salva i boids vicini
    std::vector<bd::Boid*> nearIndex{};
    std::vector<bd::Boid*> sepIndex{};
    for (int i{}; i < par_.N; i++) {
      if (i != j) {
        if (bd::distance(flock_[j], flock_[i]) < par_.d)
          nearIndex.push_back(&flock_[i]);
        if (bd::distance(flock_[j], flock_[i]) <
            par_.ds)  // sostituire flock_ i
          sepIndex.push_back(&flock_[i]);
      }
    }

    auto init1 = sepIndex.size() * flock_[j].get_Pos();
    auto v1 = par_.s * std::accumulate(sepIndex.begin(), sepIndex.end(), init1,
                                       [](array2 const& p, bd::Boid* b) {
                                         return p - b->get_Pos();
                                       });

    int sizeNear = nearIndex.size();
    array2 v2{};
    array2 v3{};
    if (sizeNear >= 1) {  // possiamo spostare questa condizione altrove?
      array2 meanVelocity = bd::meanVelocity(nearIndex);
      v2 = par_.a * (meanVelocity - flock_[j].get_Vel());

      array2 centerMass = bd::centerMass(nearIndex);
      v3 = par_.c * (centerMass - flock_[j].get_Pos());
    }

    newValues_[j] = {flock_[j].get_Pos() + (.001 * flock_[j].get_Vel()),
                     flock_[j].get_Vel() + v1 + v2 + v3};
  }
}

void bd::Flight::update() {
  std::copy(newValues_.begin(), newValues_.end(), flock_.begin());
  std::for_each(flock_.begin(), flock_.end(), [=](bd::Boid& b) {
    bd::speedLimit(b, par_.maxSpeed);
    bd::toroidalSpace(b);
  });
}