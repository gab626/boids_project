#ifndef BOID_HPP
#define BOID_HPP

#include <array>
#include <vector>

using array2 = std::array<double, 2>;

namespace bd {

class Boid {
  private:
  array2 position_{0, 0};
  array2 velocity_{0, 0};
  double maxSpeed_ = 2000.;

  public:
  Boid();
  ~Boid();
  array2 getPos() const;
  array2 getVel() const;
  double getMaxSpeed() const;
  void setPos(array2 const&);
  void setVel(array2 const&);
  void setPosX(double);
  void setPosY(double);
};


struct Parameters {
  double d = 100;  // parametri temporanei fissati
  double ds = 50;
  double s = 0.5;
  double a = 0.01;
  double c = 0.05;
  int N = 20;
};

class Flight {
 public:  // TUTTO IN PUBLIC PER ORA
  Parameters par_;
  std::vector<Boid> flock_;
  std::vector<array2> newPositions_;
  std::vector<array2> newVelocities_;
  Flight();
  void evolve();
  void update();
};

}  // namespace bd

#endif