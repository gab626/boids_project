#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SFML/Graphics.hpp>

#include "boid.hpp"

namespace bd {
// rivedere in dettaglio tutto di questa classe per sicurezza
class BoidShape : public sf::ConvexShape {
 public:
  BoidShape();
  ~BoidShape();
  virtual std::size_t getPointCount() const;
  virtual vector2 getPoint(std::size_t index) const;
};

}  // namespace bd

#endif