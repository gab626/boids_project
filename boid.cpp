#include "boid.hpp"

#include <random>

#include "functions.hpp"

bd::Flight::Flight() {
  for (int i{}; i < nBoids_; i++) {
    newPositions_[i] = {static_cast<double>(randomizer1()),
                        static_cast<double>(randomizer1())};
    newVelocities_[i] = {static_cast<double>(randomizer2()),
                          static_cast<double>(randomizer2())};
    flock_[i].position = {static_cast<double>(randomizer1()),
                          static_cast<double>(randomizer1())};
    flock_[i].velocity = {static_cast<double>(randomizer2()),
                          static_cast<double>(randomizer2())};
  }
}

double bd::Flight::distance(Boid const& b1, Boid const& b2) {
  return bd::norm(b1.position - b2.position);
}

std::array<double, 2> bd::Flight::vSeparation(Boid const& b1, Boid const& b2) {
  std::array<double, 2> v{0, 0};
  if (distance(b1, b2) < par_.ds) {
    v = (-1) * par_.s * (b1.position - b2.position);
  }
  return v;
}

std::array<double, 2> bd::Flight::vAlignment(Boid const& b1, Boid const& b2) {
  std::array<double, 2> v{0, 0};
  if (distance(b1, b2) < par_.d) {  // può essere portato fuori (in evolve)
    v = par_.a * (1 / (nBoids_ - 1)) * (b1.velocity - b2.velocity);
  }
  return v;
}

std::array<double, 2> bd::Flight::vCohesion(Boid const& b1, Boid const& b2) {
  std::array<double, 2> v{0, 0};
  if (distance(b1, b2) < par_.d) {
    std::array<double, 2> x = (1 / (nBoids_ - 1)) * b2.position;
    v = par_.c * (x - b1.position);
  }
  return v;
}

void bd::Flight::evolve() {
  for (int i{}; i < nBoids_; i++) {
    for (int j{}; j != i && j < nBoids_; j++) {
      newVelocities_[i] =
          newVelocities_[i] + vSeparation(flock_[i], flock_[j]) +
          vAlignment(flock_[i], flock_[j]) + vCohesion(flock_[i], flock_[j]);
      newPositions_[i] =
          newPositions_[i] + (.0001 * flock_[i].velocity);  // DELTA_T
    }
    bd::Flight::reverseV(flock_[i]);
  }
}

void bd::Flight::update() {
  for (int i{}; i < nBoids_; i++) {
    flock_[i].position = newPositions_[i];
    flock_[i].velocity = newVelocities_[i];
  }
}

void bd::Flight::reverseV(Boid& b) {
  if (b.position[0] < 10 || b.position[0] > 990)
    b.velocity[0] = (-1) * b.velocity[0];
  if (b.position[1] < 10 || b.position[1] > 990)
    b.velocity[1] = (-1) * b.velocity[1];
}

int bd::Flight::randomizer1() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(400, 800);
  return unif(eng);
}

int bd::Flight::randomizer2() {
    std::random_device eng;
    std::uniform_int_distribution<int> unif(0, 10);
    return unif(eng);
}