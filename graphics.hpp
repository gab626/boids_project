#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>

#include "boid.hpp"

namespace bd {
// rivedere in dettaglio tutto di questa classe per sicurezza
class BoidShape : public sf::ConvexShape {
 public:
  BoidShape();
  ~BoidShape();
  virtual std::size_t getPointCount() const;
  virtual sf::Vector2f getPoint(std::size_t index) const;
};

sf::Vector2f boidToShape(Boid const&);

}  // namespace bd

#endif