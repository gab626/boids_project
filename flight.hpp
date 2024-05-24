#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <array>
#include <vector>

#include "boid.hpp"

using array2 = std::array<float, 2>;

namespace bd {

struct Parameters {
  float d = 100;  // parametri temporanei fissati
  float ds = 50;
  float s = 0.5;
  float a = 0.05;
  float c = 0.05;
  int N = 20;
  float maxSpeed = 2000.;
};

class Flight {
 private:
  Parameters par_;
  std::vector<Boid> flock_;

 public:
  Flight();
  ~Flight();
  int getN() const;
  std::vector<Boid> getFlock() const;  // non mi piace
  void updateFlock(std::vector<Boid>&);
  void evolve();
};

}  // namespace bd

#endif