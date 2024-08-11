#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>

using vector2 = sf::Vector2f;

namespace bd {

class Boid {
 private:
  vector2 position_;
  vector2 velocity_;
  sf::ConvexShape boidShape_;
  void setupShape(sf::Color);

 public:
  Boid();
  Boid(sf::Color);
  Boid(const vector2&, const vector2&, const sf::Color&);
  ~Boid();
  vector2 getPosition() const;
  vector2 getVelocity() const;
  sf::ConvexShape getShape() const;
  void setPosition(const vector2&);
  void setVelocity(const vector2&);
  void setPositionX(float);
  void setPositionY(float);
  void setShapePosition(const vector2&);
};

}  // namespace bd

#endif