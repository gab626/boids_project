#ifndef BOID_HPP
#define BOID_HPP

#include <array>

namespace bd {

struct Boid {
  std::array<double, 2> position{0, 0};
  std::array<double, 2> velocity{0, 0};
};

struct Parameters {
  double d = 300;  // parametri temporanei fissati
  double ds = 10;
  double s = 10;
  double a = .01;
  double c = .001;  // manca delta_t
};

class Flight {  // inizializzare membri  //class che prima o poi verrà
                // decomposta
 public:  //TUTTO IN PUBLIC PER ORA
  Parameters par_;
  static const int nBoids_ = 20;  //soluzione temporanea
  std::array<std::array<double, 2>, nBoids_> newPositions_;
  std::array<std::array<double, 2>, nBoids_> newVelocities_;
  std::array<double, 2> vSeparation(Boid const& b1, Boid const& b2);
  std::array<double, 2> vAlignment(Boid const& b1, Boid const& b2);
  std::array<double, 2> vCohesion(Boid const& b1, Boid const& b2);
  // void reverseV();

  int randomizer1(); //*************
  int randomizer2(); //*************

 std::array<Boid, nBoids_> flock_;
  Flight();
  void evolve();
  void update();
};

}  // namespace bd

#endif