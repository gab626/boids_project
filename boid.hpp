#ifndef BOID_HPP
#define BOID_HPP

#include <array>
#include <vector>

using array2 = std::array<float, 2>;

namespace bd {

class Boid {
 private:
  array2 position_{0, 0};
  array2 velocity_{0, 0};

 public:
  Boid();
  ~Boid();
  array2 get_Pos() const;
  array2 get_Vel() const;
  void set_Pos(array2 const&);
  void set_Vel(array2 const&);
  void set_PosX(float);
  void set_PosY(float);
};

struct Parameters {
  float d = 100;  // parametri temporanei fissati
  float ds = 50;
  float s = 0.5;
  float a = 0.05;
  float c = 0.05;
  int N = 20;
  float maxSpeed = 2000.;
};

class Flight {
 private:
  Parameters par_;
  std::vector<Boid> flock_;
  std::vector<array2> newPositions_;
  std::vector<array2> newVelocities_;

 public:
  Flight();
  ~Flight();
  int get_N() const;
  std::vector<Boid> get_flock() const; // non mi piace
  void evolve();
  void update();
};

}  // namespace bd

#endif