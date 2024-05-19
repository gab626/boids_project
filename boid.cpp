#include "boid.hpp"

#include <functional>
#include <numeric>
#include <vector>

#include "functions.hpp"

bd::Boid::Boid()
    : position_{bd::randomPosition()}, velocity_{bd::randomVelocity()} {}

bd::Boid::~Boid() {}

array2 bd::Boid::getPos() const { return position_; }

array2 bd::Boid::getVel() const { return velocity_; }

double bd::Boid::getMaxSpeed() const { return maxSpeed_; }

void bd::Boid::setPos(array2 const& a) { position_ = a; }

void bd::Boid::setVel(array2 const& b) { velocity_ = b; }

void bd::Boid::setPosX(double x) { position_[0] = x; }

void bd::Boid::setPosY(double y) { position_[1] = y; }

bd::Flight::Flight() {
  for (int i{}; i < par_.N; i++) {
    bd::Boid b;
    flock_.push_back(b);
    newPositions_.push_back({});
    newVelocities_.push_back({});
  }
}

void bd::Flight::evolve() {
  for (int j{0}; j < par_.N; j++) {  // trova e salva i boids vicini
    std::vector<Boid*> nearIndex{};   // da vedere se tornare ad un vector<int>
    std::vector<Boid*> sepIndex{};
    for (int i{}; i < par_.N; i++) {
      if (i != j) {
        if (bd::distance(flock_[j], flock_[i]) < par_.d)
          nearIndex.push_back(&flock_[i]);
        if (bd::distance(flock_[j], flock_[i]) <
            par_.ds)  // sostituire flock_ i
          sepIndex.push_back(&flock_[i]);
      }
    }

    auto init1 = sepIndex.size() * flock_[j].getPos();
    auto v1 = par_.s * std::accumulate(sepIndex.begin(), sepIndex.end(), init1,
                                       [](array2 const& p, Boid* b) {
                                         return p - b->getPos();
                                       });

    int sizeNear = nearIndex.size();
    array2 v2{};
    array2 v3{};
    if (sizeNear >= 1) {  // possiamo spostare questa condizione altrove?
      array2 meanVelocity = bd::meanVelocity(nearIndex);
      v2 = par_.a * (meanVelocity - flock_[j].getVel());

      array2 centerMass = bd::centerMass(nearIndex);
      v3 = par_.c * (centerMass - flock_[j].getPos());
    }

    newVelocities_[j] = flock_[j].getVel() + v1 + v2 + v3;
    newPositions_[j] = flock_[j].getPos() + (.001 * flock_[j].getVel());
  }
}

void bd::Flight::update() {
  for (int i{}; i < par_.N; i++) {
    flock_[i].setPos(newPositions_[i]);
    flock_[i].setVel(newVelocities_[i]);
    bd::speedLimit(flock_[i]);
    bd::toroidalSpace(flock_[i]);
  }
}