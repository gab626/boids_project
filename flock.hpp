#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <array>
#include <vector>

#include "boid.hpp"

namespace bd {

struct Statistics {
  float distanceMean{};
  float distanceStandardDeviation{};
  float speedMean{};
  float speedStandardDeviation{};
};

struct Parameters {  // rivedere nomi parametri?
  float d = 80.f;   // parametri temporanei fissati
  float ds = 20.f;
  float s = 1.f;
  float a = 0.03f;
  float c = 0.01f;
  int N = 100;
  float maxSpeed = 5000.f;
  float deltaT = .002f;
};

class Flock {
 private:
  Parameters par_;
  Statistics statistics_;
  sf::Color color_;
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