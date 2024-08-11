#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <array>
#include <vector>

#include "boid.hpp"
// #include "quadtree.hpp"

namespace bd {

struct Statistics {
  float distanceMean{};
  float distanceStandardDeviation{};
  float speedMean{};
  float speedStandardDeviation{};
};

struct Parameters {  // rivedere nomi parametri?
  float d = 100.f;   // parametri temporanei fissati
  float ds = 30.f;
  float s = 3.f;
  float a = 0.05f;
  float c = 0.3f;
  int N = 500;
  float maxSpeed = 3000.f;
  float deltaT = .001f;
};

class Flock {
 private:
  Parameters par_;
  Statistics statistics_;
  // Quadtree quadtree_;
  std::vector<Boid> flock_;
  void updateFlock(std::vector<Boid>&);  // forse riaggiungere oldBoid vector
  void saveStatistics(float, float, float, float);
  void printStatistics();

 public:
  Flock();
  Flock(sf::Color);
  ~Flock();
  int getN() const;
  std::vector<Boid> getFlock() const;  // non mi piace
  void evolve();
};

}  // namespace bd

#endif