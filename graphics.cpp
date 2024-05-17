#include "graphics.hpp"

sf::Vector2<float> boidToShape(bd::Boid const& b) {
  sf::Vector2<float> v = {static_cast<float>(b.position[0]),
                          static_cast<float>(b.position[1])};
  return v;
}