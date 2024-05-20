#include "graphics.hpp"

sf::Vector2<float> bd::boidToShape(bd::Boid& b) {
  sf::Vector2<float> v = {b.get_Pos()[0], b.get_Pos()[1]};
  return v;
}