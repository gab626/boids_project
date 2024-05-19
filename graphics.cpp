#include "graphics.hpp"

sf::Vector2<float> bd::boidToShape(bd::Boid& b) {
  sf::Vector2<float> v = {static_cast<float>(b.get_Pos()[0]),
                          static_cast<float>(b.get_Pos()[1])};
  return v;
}