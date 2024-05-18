#include "boid.hpp"

#include <functional>
#include <numeric>
#include <vector>

#include "functions.hpp"

bd::Flight::Flight() {  // constructor
  for (int i{}; i < nBoids_; i++) {
    flock_[i].position = bd::randomPosition();
    flock_[i].velocity = bd::randomVelocity();
    newPositions_[i] = {0, 0};
    newVelocities_[i] = {0, 0};
  }
}

void bd::Flight::toroidalSpace() {  // spazio toroidale
  for (int i{}; i < nBoids_; i++) bd::switchPosition(flock_[i]);
}

void bd::Flight::evolve() {
  bd::Flight::toroidalSpace();
  for (int j{0}; j < nBoids_; j++) {  // trova e salva i boids vicini
    std::vector<Boid*> nearIndex{};   // da vedere se tornare ad un vector<int>
    std::vector<Boid*> sepIndex{};
    for (int i{}; i < nBoids_; i++) {
      if (i != j) {
        if (bd::distance(flock_[j], flock_[i]) < par_.d)
          nearIndex.push_back(&flock_[i]);
        if (bd::distance(flock_[j], flock_[i]) <
            par_.ds)  // sostituire flock_ i
          sepIndex.push_back(&flock_[i]);
      }
    }

    auto init1 = sepIndex.size() * flock_[j].position;
    auto v1 = par_.s * std::accumulate(sepIndex.begin(), sepIndex.end(), init1,
                                       [](array2 const& p, Boid* b) {
                                         return p - b->position;
                                       });

    int sizeNear = nearIndex.size();
    auto init2 = sizeNear * flock_[j].velocity;
    auto v2 = (par_.a / sizeNear) *
              std::accumulate(
                  nearIndex.begin(), nearIndex.end(), init2,
                  [](array2 const& p, Boid* b) { return p - b->velocity; });
    /* for (int i{}; i < sizeNear; i++)
      sum2 = sum2 + flock_[nearIndex[i]].velocity;
    v2 = par_.a / sizeNear * sum2;  // alignment velocity */

    array2 v3{0, 0};
    if (sizeNear >= 1) {
      array2 center = bd::centerMass(nearIndex);
      v3 = par_.c * (center - flock_[j].position);
    }
    
    newVelocities_[j] = flock_[j].velocity + v1 + v3;
    newPositions_[j] = flock_[j].position + (.001 * flock_[j].velocity);
  }
}

void bd::Flight::update() {
  for (int i{}; i < nBoids_; i++) {
    flock_[i].position = newPositions_[i];
    flock_[i].velocity = newVelocities_[i];
    // bd::speedLimit(flock_[i]);
  }
}