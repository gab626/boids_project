#ifndef BOID_HPP
#define BOID_HPP

#include <array>

namespace bd {

struct Boid {  // rivedere naming conventions + alias per i vector?
  std::array<double, 2> position{0, 0};  // meglio 2 array o 4 double?
  std::array<double, 2> velocity{0, 0};
};

struct Parameters {
  double d = 150;  // parametri temporanei fissati
  double ds = 50;
  double s = .5;
  double a = .5;
  double c = .5;  // manca delta_t
};

class Flight {  // inizializzare membri  //class che prima o poi verrà
                // decomposta
 private:
  Parameters par_;
  std::array<Boid, 10> flock_;
  int nBoids_ = 10;  // fissato per ora
  std::array<std::array<double, 2>, 10> newPositions_;
  std::array<std::array<double, 2>, 10> newVelocities_;
  double distance(Boid const&, Boid const&);  // si può essere più specifici
  std::array<double, 2> vSeparation(Boid const&, Boid const&);
  std::array<double, 2> vAlignment(Boid const&, Boid const&);
  std::array<double, 2> vCohesion(Boid const&, Boid const&);

 public:
  Flight();  // max dim fissata momentaneamente a 10
  void evolve();
  void update();
};

}  // namespace bd

#endif