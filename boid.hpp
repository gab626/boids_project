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
  array2 getPos();
  array2 getVel();
  double getMaxSpeed();
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
  static const int nBoids_ = 20;  // soluzione temporanea
  std::vector<Boid> flock_;
  std::array<array2, nBoids_> newPositions_{};
  std::array<array2, nBoids_> newVelocities_{};
  Flight();
  void evolve();
  void update();
};

}  // namespace bd

#endif