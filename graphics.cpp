#include "graphics.hpp"

using bd::Boid;

sf::Vector2<float> bd::boidToShape(Boid const& b) {
  return {b.getPositionX(), b.getPositionY()};
}