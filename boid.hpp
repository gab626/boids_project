#ifndef BOID_HPP
#define BOID_HPP

#include <array>

using array2 = std::array<double, 2>;

namespace bd {

struct Boid {
  array2 position{0, 0};
  array2 velocity{0, 0};
  double maxSpeed = 2000.;
};

struct Parameters {
  double d = 100;  // parametri temporanei fissati
  double ds = 50;
  double s = 0.5;
  double a = 0.01;
  double c = 0.05;
};

class Flight {  // inizializzare membri  //class che prima o poi verrà
                // decomposta
 public:  //TUTTO IN PUBLIC PER ORA
  Parameters par_;
  static const int nBoids_ = 20;  //soluzione temporanea
  std::array<Boid, nBoids_> flock_;
  std::array<array2, nBoids_> newPositions_;
  std::array<array2, nBoids_> newVelocities_;
  Flight();
  void toroidalSpace();
  void evolve();
  void update();
};

}  // namespace bd

#endif