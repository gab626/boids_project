#include "boid.hpp"

#include <random>

#include "functions.hpp"

bd::Flight::Flight() {
  for (int i{}; i < nBoids_; i++) {
    flock_[i].position = {static_cast<double>(randomizer1()),
                          static_cast<double>(randomizer1())};
    flock_[i].velocity = {static_cast<double>(randomizer2()),
                          static_cast<double>(randomizer2())};
    newPositions_[i] = {0, 0};
    newVelocities_[i] = {0, 0};
  }
}

std::array<double, 2> bd::Flight::vSeparation(Boid const& b1, Boid const& b2) {
  std::array<double, 2> v{0, 0};
  if (bd::distance(b1, b2) < par_.ds) {
    v = v + ((-1) * par_.s * (b1.position - b2.position));
  }
  return v;
}

std::array<double, 2> bd::Flight::vAlignment(Boid const& b1, Boid const& b2) {
  std::array<double, 2> v{0, 0};
  if (bd::distance(b1, b2) < par_.d) {
    v = v + (par_.a * (1 / (nBoids_ - 1)) * (b1.velocity - b2.velocity));
  }
  return v;
}

std::array<double, 2> bd::Flight::vCohesion(Boid const& b1, Boid const& b2) {
  std::array<double, 2> v{0, 0};
  if (bd::distance(b1, b2) < par_.d) {
    std::array<double, 2> x = (1 / (nBoids_ - 1)) * b2.position;
    v = v + (par_.c * (x - b1.position));
  }
  return v;
}

void bd::Flight::evolve() {
  for (int i{}; i < nBoids_; i++) {
    for (int j{}; j < nBoids_; j++) {
      if (i != j) {
        newVelocities_[i] =
            flock_[i].velocity + vSeparation(flock_[i], flock_[j]) +
            vAlignment(flock_[i], flock_[j]) + vCohesion(flock_[i], flock_[j]);
        newPositions_[i] =
            flock_[i].position + (.01 * flock_[i].velocity);  // DELTA_T
      }
    }
  }
  // bd::Flight::reverseV();
}

void bd::Flight::update() {
  for (int i{}; i < nBoids_; i++) {
    flock_[i].position = newPositions_[i];
    flock_[i].velocity = newVelocities_[i];
  }
}

/* void bd::Flight::reverseV() {
  for (int i{}; i < nBoids_; i++) {
    if (flock_[i].position[0] < 10 || flock_[i].position[0] > 790)
      flock_[i].velocity[0] = (-1) * flock_[i].velocity[0];
    if (flock_[i].position[1] < 10 || flock_[i].position[1] > 790)
      flock_[i].velocity[1] = (-1) * flock_[i].velocity[1];
  }
} */

int bd::Flight::randomizer1() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(100, 700);
  return unif(eng);
}

int bd::Flight::randomizer2() {
  std::random_device eng;
  std::uniform_int_distribution<int> unif(10, 20);
  return unif(eng);
}