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
  array2 get_Pos() const;
  array2 get_Vel() const;
  double get_MaxSpeed() const;
  void set_Pos(array2 const&);
  void set_Vel(array2 const&);
  void set_PosX(double);
  void set_PosY(double);
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
 private:
  Parameters par_;
  std::vector<Boid> flock_;
  std::vector<array2> newPositions_;
  std::vector<array2> newVelocities_;

 public:
  Flight();
  int get_N() const;
  std::vector<Boid> get_flock() const; // non mi piace
  void evolve();
  void update();
};

}  // namespace bd

#endif