#include "boid.hpp"

#include <functional>
#include <numeric>
#include <vector>

#include "functions.hpp"

bd::Boid::Boid()
    : position_{bd::randomPosition()}, velocity_{bd::randomVelocity()} {}

bd::Boid::~Boid() {}

array2 bd::Boid::get_Pos() const { return position_; }

array2 bd::Boid::get_Vel() const { return velocity_; }

void bd::Boid::set_Pos(array2 const& a) { position_ = a; }

void bd::Boid::set_Vel(array2 const& b) { velocity_ = b; }

void bd::Boid::set_PosX(float x) { position_[0] = x; }

void bd::Boid::set_PosY(float y) { position_[1] = y; }

bd::Flight::Flight() {
  for (int i{}; i < par_.N; i++) {
    bd::Boid b;
    flock_.push_back(b);
    newPositions_.push_back({});
    newVelocities_.push_back({});
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

    newVelocities_[j] = flock_[j].get_Vel() + v1 + v2 + v3;
    newPositions_[j] = flock_[j].get_Pos() + (.001 * flock_[j].get_Vel());
  }
}

void bd::Flight::update() { // CERCARE ALGORITMO
  for (int i{}; i < par_.N; i++) {
    flock_[i].set_Pos(newPositions_[i]);
    flock_[i].set_Vel(newVelocities_[i]);
    bd::speedLimit(flock_[i], par_.maxSpeed);
    bd::toroidalSpace(flock_[i]);
  }
}