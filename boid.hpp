#ifndef BOID_HPP
#define BOID_HPP

#include <array>

using array2 = std::array<double, 2>;

namespace bd {

struct Boid {
  array2 position{0, 0};
  array2 velocity{0, 0};
};

struct Parameters {
  double d = 80;  // parametri temporanei fissati
  double ds = 30;
  double s = 0;
  double a = 0;
  double c = 0;  // manca delta_t
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
  /* array2 vSeparation(Boid const& b1, Boid const& b2);
  array2 vAlignment(Boid const& b1, Boid const& b2);
  array2 vCohesion(Boid const& b1, Boid const& b2); */
  void changePosition();
  void evolve();
  void update();
  int randomizer1(); //*************
  int randomizer2(); //*************
};

}  // namespace bd

#endif