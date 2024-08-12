#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <array>
#include <vector>

#include "boid.hpp"
#include "cell.hpp"
// #include "quadtree.hpp"

namespace bd {

/* struct Statistics {
  float distanceMean{};
  float distanceStandardDeviation{};
  float speedMean{};
  float speedStandardDeviation{};
}; */

struct Parameters {        // rivedere nomi parametri?
  float distance = 100.f;  // parametri temporanei fissati
  float distanceSeparation = 30.f;
  float separationCoefficient = 3.f;
  float alignmentCoefficient = 0.05f;
  float cohesionCoefficient = 0.3f;
  int numberBoids = 500;
  float maxSpeed = 3000.f;
  float deltaTime = .001f;
};

class Flock {
 private:
  Parameters parameters_;
  // Statistics statistics_;
  // Quadtree quadtree_;
  std::vector<Boid> flock_;
  std::vector<Cell> grid_;
  void setupGrid();
  // void saveStatistics(float, float, float, float);
  // void printStatistics();

 public:
  Flock();
  Flock(sf::Color);
  ~Flock();
  int getNumberBoids() const;
  std::vector<Boid> getFlock() const;  // non mi piace
  void updateFlock(std::vector<Boid>&);
  void evolve();
};

}  // namespace bd

#endif