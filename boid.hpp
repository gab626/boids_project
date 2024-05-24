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
  array2 getPosition() const;
  array2 getVelocity() const;
  float getPositionX() const;
  float getPositionY() const;
  void setPosition(array2 const&);
  void setVelocity(array2 const&);
  void setPositionX(float);
  void setPositionY(float);
};

}  // namespace bd

#endif