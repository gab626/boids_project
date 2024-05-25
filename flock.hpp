#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <array>
#include <vector>

#include "boid.hpp"

using array2 = std::array<float, 2>;

namespace bd {

struct Parameters {  // rivedere nomi parametri?
  float d = 100;     // parametri temporanei fissati
  float ds = 30;
  float s = 0.5;
  float a = 0.05;
  float c = 0.1;
  int N = 40;
  float maxSpeed = 2000.;
};

class Flock {
 private:
  Parameters par_;
  std::vector<Boid> flock_;

 public:
  Flock();
  ~Flock();
  int getN() const;
  std::vector<Boid> getFlock() const;  // non mi piace
  void updateFlock(std::vector<Boid>&);
  void evolve();
};

}  // namespace bd

#endif