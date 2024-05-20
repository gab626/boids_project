#include "graphics.hpp"

sf::Vector2<float> bd::boidToShape(bd::Boid& b) {
  return {b.get_Pos_X(), b.get_Pos_Y()};
}