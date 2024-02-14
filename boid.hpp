#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

// #include "frame.hpp"

/* double d = 150; //parametri temporanei
  double ds = 50;
  double s = 1;
  double a = 1;
  double c = 1;
  double n = 10; */

using vector2 = std::vector<double>;  // non piace al pelato? :(

namespace bd {

class Boid {  // rivedere naming conventions + alias per i vector?
 private:
  vector2 position_{0, 0};  // fissare dimensione
  vector2 velocity_{1, 1};
  // static int nBoids_;

 public:   // vanno tutti in public?
  Boid();
  double getX() const;
  double getY() const;
  double distance(Boid const& b) const;  // TEST
  double setPosition();
  // bool checkDistance();
  /* vector2 vSeparation(Boid const& b); //const?
  vector2 vAlignment(Boid const& b);
  vector2 vCohesion(Boid const& b); */
  void flight();
  void reverseVx();
  void reverseVy();
};

vector2 operator+(vector2 const& v1, vector2 const& v2);  // TEST
vector2 operator*(double c, vector2 const& v2);           // TEST
double norm(vector2 v);                                   // TEST
}  // namespace bd

#endif