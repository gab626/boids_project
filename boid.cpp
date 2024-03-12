#include "boid.hpp"

#include <functional>
#include <numeric>
#include <random>
#include <vector>

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

void bd::Flight::evolve() {
  bd::Flight::changePosition();
  for (int j{0}; j < nBoids_; j++) {  // trova e salva i boids vicini
    std::vector<int> nearIndex{};
    std::vector<int> sepIndex{};
    for (int i{}; i < nBoids_; i++) {
      if (i != j) {
        if (bd::distance(flock_[j], flock_[i]) < par_.d) nearIndex.push_back(i);
        if (bd::distance(flock_[j], flock_[i]) <
            par_.ds)  // sostituire flock_ i
          sepIndex.push_back(i);
      }
    }
    auto sizeSep = sepIndex.size();
    array2 sum1 = sizeSep * flock_[j].position;
    for (int i{}; i < sizeSep; i++) sum1 = sum1 - flock_[sepIndex[i]].position;
    auto v1 = par_.s * sum1;  // separation velocity
    // ho dovuto invertire il segno di v1, potrei non aver capito qualcosa nella
    // formula o invertito qualche passaggio/semplificazione

    auto sizeNear = nearIndex.size();
    array2 v2{0, 0};
    if (sizeNear >= 1) {
      array2 sum2 = sizeNear * flock_[j].velocity;
      for (int i{}; i < sizeNear; i++)
        sum2 = sum2 - flock_[nearIndex[i]].velocity;
      v2 = (-1) * par_.a / sizeNear * sum2;  // alignment velocity
    }
    // non so se sta funzionando correttamente perché si allineano "troppo" e in
    // blocco, inoltre anche qui ho dovuto invertire il segno di v2

    array2 v3{0, 0};
    if (sizeNear >= 1) {
      array2 center = {0, 0};
      for (int i{}; i < sizeNear; i++)
        center = center + flock_[nearIndex[i]].position;
      center = (1 / sizeNear) * center;
      v3 = (+1) * par_.c * (center - flock_[j].position);  // cohesion velocity
    }
    // sempre indirizzata verso l'origine o il suo punto opposto per motivi
    // ignoti sconosciuti incompresibili
    newVelocities_[j] = flock_[j].velocity + v1 + v2 + v3;
    newPositions_[j] = flock_[j].position + (.001 * flock_[j].velocity);
  }
}

void bd::Flight::update() {
  for (int i{}; i < nBoids_; i++) {
    flock_[i].position = newPositions_[i];
    flock_[i].velocity = newVelocities_[i];
  }
}

void bd::Flight::changePosition() {  // spazio toroidale
  for (int i{}; i < nBoids_; i++) {
    auto x = flock_[i].position[0];
    auto y = flock_[i].position[1];
    if (x < 0) flock_[i].position[0] = x + 800;
    if (x > 800) flock_[i].position[0] = x - 800;
    if (y < 0) flock_[i].position[1] = x + 800;
    if (y > 800) flock_[i].position[1] = x - 800;
  }
}

int bd::Flight::randomizer1() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(100, 700);
  return unif(eng);
}

int bd::Flight::randomizer2() {
  std::random_device eng;
  std::uniform_int_distribution<int> unif(-150, 150);
  return unif(eng);
}