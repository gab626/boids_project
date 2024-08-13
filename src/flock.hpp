#ifndef FLOCK_HPP
#define FLOCK_HPP

#include "grid.hpp"

using boidVector = std::vector<bd::Boid>;

namespace bd {

/* struct Statistics {
  float distanceMean{};
  float distanceStandardDeviation{};
  float speedMean{};
  float speedStandardDeviation{};
}; */

struct Parameters {
  float distance = 100.f;  // parametri temporaneamente fissati
  float distanceSeparation = 30.f;
  float separationCoefficient = 3.f;
  float alignmentCoefficient = 0.05f;
  float cohesionCoefficient = 0.3f;
  int numberBoids = 200;
  float maxSpeed = 3000.f;
  float deltaTime = .001f;
};

class Flock {
 private:
  Parameters parameters_;
  // Statistics statistics_;
  boidVector flock_;
  Grid grid_;
  // void saveStatistics(float, float, float, float);
  // void printStatistics();

 public:
  Flock();
  Flock(sf::Color);
  ~Flock();
  int getNumberBoids() const;
  boidVector getFlock() const;  // non mi piace
  void updateFlock(boidVector&);
  void evolve();
};

}  // namespace bd

#endif