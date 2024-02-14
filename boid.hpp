#ifndef BOID_HPP
#define BOID_HPP

#include <vector>

// #include "frame.hpp"

using vector2 = std::vector<double>;  // non piace al pelato? :(

namespace bd {

class Boid {  // rivedere nameing conventions + alias per i vector?
 private:
  vector2 position_{0,0};  // fissare dimensione
  vector2 velocity_{0,0};
  static int nBoids_;

 public:                                          // vanno tutti in public?
  Boid(vector2 p, vector2 v);                     // come fare costruttore?
  double distance(vector2 p1, vector2 p2) const;  // TEST
  /* vector2 vSeparation() const;
  vector2 vAlignment() const;
  vector2 vCohesion() const; */
};

vector2 operator+(vector2 const& v1, vector2 const& v2);  // TEST
vector2 operator*(double c, vector2 const& v2);           // TEST
double norm(vector2 v);                                   // TEST
}  // namespace bd

#endif