#ifndef BOID_HPP
#define BOID_HPP

#include <array>

// #include "frame.hpp"

/* double d = 150; //parametri temporanei
  double ds = 50;
  double s = 1;
  double a = 1;
  double c = 1;
  double n = 10; */

using array2 = std::array<double, 2>;  // non piace al pelato? :(

namespace bd {

class Boid {  // rivedere naming conventions + alias per i vector?
 private:
  array2 position_{0, 0};  // fissare dimensione
  array2 velocity_{1, 1};
  // static int nBoids_;

 public:   // vanno tutti in public?
  Boid();
  double getX() const;
  double getY() const;
  double distance(Boid const& b) const;  // TEST
  double setPosition();
  // bool checkDistance();
  /* array2 vSeparation(Boid const& b); //const?
  array2 vAlignment(Boid const& b);
  array2 vCohesion(Boid const& b); */
  void flight();
  void reverseVx();
  void reverseVy();
};

array2 operator+(array2 const& v1, array2 const& v2);  // TEST
array2 operator*(double c, array2 const& v2);           // TEST
double norm(array2 v);                                   // TEST
}  // namespace bd

#endif