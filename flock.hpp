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
  float d = 70.f;   // parametri temporanei fissati
  float ds = 20.f;
  float s = 3.f;
  float a = 0.05f;
  float c = 0.02f;
  int N = 50;
  float maxSpeed = 5000.f;
  float deltaT = .002f;
};

class Flock {
 private:
  Parameters par_;
  Statistics statistics;
  std::vector<Boid> flock_;
  void updateFlock(std::vector<Boid>&);  // forse riaggiungere oldBoid vector
  void saveStatistics(float, float, float, float);
  void printStatistics();

 public:
  Flock();
  ~Flock();
  int getN() const;
  std::vector<Boid> getFlock() const;  // non mi piace
  void evolve();
};

}  // namespace bd

#endif