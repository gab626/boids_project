#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
#include <array>

using vector2 = sf::Vector2f;

namespace bd {

class Boid {
 private:
  vector2 position_;
  vector2 velocity_;

 public:
  Boid();
  Boid(vector2 const&, vector2 const&);
  ~Boid();
  vector2 getPosition() const;
  vector2 getVelocity() const;
  void setPosition(vector2 const&);
  void setVelocity(vector2 const&);
  void setPositionX(float);
  void setPositionY(float);
};

}  // namespace bd

#endif