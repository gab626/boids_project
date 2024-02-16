#ifndef BOID_HPP
#define BOID_HPP

#include <array>

namespace bd {

struct Boid {
  std::array<double, 2> position{0, 0};
  std::array<double, 2> velocity{0, 0};
};

struct Parameters {
  double d = 200;  // parametri temporanei fissati
  double ds = 50;
  double s = 2;
  double a = .5;
  double c = .1;  // manca delta_t
};

class Flight {  // inizializzare membri  //class che prima o poi verrà
                // decomposta
 public:  //TUTTO IN PUBLIC PER ORA
  Parameters par_;
  int nBoids_ = 20;  // fissato per ora
  std::array<std::array<double, 2>, 20> newPositions_;
  std::array<std::array<double, 2>, 20> newVelocities_;
  std::array<double, 2> vSeparation(Boid const&, Boid const&);
  std::array<double, 2> vAlignment(Boid const&, Boid const&);
  std::array<double, 2> vCohesion(Boid const&, Boid const&);
  void reverseV(Boid&);

  int randomizer1(); //*************
  int randomizer2(); //*************

 std::array<Boid, 20> flock_; //vergognati fatti schifo cavati gli occhi mozzati le dita
  Flight();  // max dim fissata momentaneamente a 10
  void evolve();
  void update();
};

}  // namespace bd

#endif