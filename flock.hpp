#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <array>
#include <vector>

#include "boid.hpp"

namespace bd {

struct Parameters {  // rivedere nomi parametri?
  float d = 100.f;   // parametri temporanei fissati
  float ds = 40.f;
  float s = 0.5f;
  float a = 0.05f;
  float c = 0.05f;
  int N = 40;
  float maxSpeed = 2000.f;
};

class Flock {
 private:
  Parameters par_;
  std::vector<Boid> flock_;

 public:
  Flock();
  ~Flock();
  int getN() const;
  std::vector<Boid> getFlock() const;    // non mi piace
  void updateFlock(std::vector<Boid>&);  // forse riaggiungere oldBoid vector
  void evolve();
};

}  // namespace bd

#endif