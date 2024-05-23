#ifndef BOID_HPP
#define BOID_HPP

#include <array>

using array2 = std::array<float, 2>;

namespace bd {

class Boid {
 private:
  array2 position_{0, 0};
  array2 velocity_{0, 0};

 public:
  Boid();
  Boid(array2 const&, array2 const&);
  ~Boid();
  array2 get_Pos() const;
  array2 get_Vel() const;
  float get_Pos_X() const;
  float get_Pos_Y() const;
  void set_Pos(array2 const&);
  void set_Vel(array2 const&);
  void set_PosX(float);
  void set_PosY(float);
};

}  // namespace bd

#endif