#include <vector>

#ifndef BOID_HPP
#define BOID_HPP

namespace bd {
class Boid {  // rivedere names conventions + alias per i vector?
 private:
  std::vector<double> Position;
  std::vector<double> Velocity;
  std::vector<double> NewVelocity;

 public:   // vanno tutti in public?
  Boid();  // come fare costruttore?
  double Distance() const;
  std::vector<double> Separation() const;
  std::vector<double> Alignment() const;
  std::vector<double> Cohesion() const;
};
}  // namespace bd

#endif