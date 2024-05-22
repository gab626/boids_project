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
  std::vector<array2> newPositions_;
  std::vector<array2> newVelocities_;

 public:
  Flight();
  ~Flight();
  int get_N() const;
  std::vector<Boid> get_flock() const;  // non mi piace
  void evolve();
  void update();
};

}  // namespace bd

#endif