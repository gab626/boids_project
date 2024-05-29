#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <array>
#include <vector>

#include "boid.hpp"

namespace bd {

struct Statistics {
  float meanDistance{};
  float distanceStandardDeviation{};
  float meanSpeed{};
  float speedStandardDeviation{};
};

struct Parameters {  // rivedere nomi parametri?
  float d = 100.f;   // parametri temporanei fissati
  float ds = 40.f;
  float s = 0.1f;
  float a = 0.02f;
  float c = 0.005f;
  int N = 40;
  float maxSpeed = 2000.f;
  float deltaT = .01f;
};

class Flock {
 private:
  Parameters par_;
  std::vector<Boid> flock_;
  Statistics statistics;
  void updateFlock(std::vector<Boid>&);  // forse riaggiungere oldBoid vector

 public:
  Flock();
  ~Flock();
  int getN() const;
  std::vector<Boid> getFlock() const;  // non mi piace
  void evolve();
};

}  // namespace bd

#endif