#ifndef BOID_HPP
#define BOID_HPP

#include <array>

namespace bd {

struct Boid {  // rivedere naming conventions + alias per i vector?
  std::array<double, 2> position{0, 0};  // meglio 2 array o 4 double?
  std::array<double, 2> velocity{0, 0};
};

struct Parameters {
  double d = 200;  // parametri temporanei fissati
  double ds = 20;
  double s = 2;
  double a = .05;
  double c = .001;  // manca delta_t
};

class Flight {  // inizializzare membri  //class che prima o poi verrà
                // decomposta
 private:
  Parameters par_;
  int nBoids_ = 30;  // fissato per ora
  std::array<std::array<double, 2>, 30> newPositions_;
  std::array<std::array<double, 2>, 30> newVelocities_;
  double distance(Boid const&, Boid const&);  // si può essere più specifici (o meno)
  std::array<double, 2> vSeparation(Boid const&, Boid const&);
  std::array<double, 2> vAlignment(Boid const&, Boid const&);
  std::array<double, 2> vCohesion(Boid const&, Boid const&);
  void reverseV(Boid&);

  int randomizer1(); //*************
  int randomizer2(); //*************

 public:
 std::array<Boid, 30> flock_; //vergognati fatti schifo cavati gli occhi mozzati le dita
  Flight();  // max dim fissata momentaneamente a 10
  void evolve();
  void update();
};

}  // namespace bd

#endif