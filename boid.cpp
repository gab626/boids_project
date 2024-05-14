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
    int sizeSep = sepIndex.size();
    array2 sum1 = sizeSep * flock_[j].position;
    for (int i{}; i < sizeSep; i++) sum1 = sum1 - flock_[sepIndex[i]].position;
    auto v1 = par_.s * sum1;  // separation velocity
    // a volte non si vede il respingimento tra boids
    // vicini, forse è dovuto a velocità troppo grandi

    int sizeNear = nearIndex.size();
    array2 v2{0, 0};
    if (sizeNear >= 1) {
      array2 sum2 = -sizeNear * flock_[j].velocity;
      for (int i{}; i < sizeNear; i++)
        sum2 = sum2 + flock_[nearIndex[i]].velocity;
      v2 = par_.a / sizeNear * sum2;  // alignment velocity
    }
    // non so se sta funzionando correttamente perché si allineano "troppo" e in
    // blocco

    array2 v3{0, 0};
    if (sizeNear >= 1) {
      array2 center = {0, 0};
      for (int i{}; i < sizeNear; i++) // forse è meglio attivarla per sizeNear >= 2
        center = center + flock_[nearIndex[i]].position;
      center = (1 / sizeNear) * center;
      v3 = par_.c * (center - flock_[j].position);  // cohesion velocity
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
    if (y < 0) flock_[i].position[1] = y + 800;
    if (y > 800) flock_[i].position[1] = y - 800;
  }
}  // forse può essere fatto meglio ma per ora ci va bene

int bd::Flight::randomizer1() {
  std::random_device r;
  std::default_random_engine eng(r());
  std::uniform_int_distribution<int> unif(0, 800);
  return unif(eng);
}

int bd::Flight::randomizer2() {
  std::random_device eng;
  std::uniform_int_distribution<int> unif(-200, 200);
  return unif(eng);
}
// perché i due randomizer hanno implementazione diversa lol