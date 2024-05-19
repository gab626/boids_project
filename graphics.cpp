#include "graphics.hpp"

sf::Vector2<float> bd::boidToShape(bd::Boid& b) {
  sf::Vector2<float> v = {static_cast<float>(b.getPos()[0]),
                          static_cast<float>(b.getPos()[1])};
  return v;
}