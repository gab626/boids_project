#include "graphics.hpp"

sf::Vector2<float> boidToShape(bd::Boid const& b) {
    sf::Vector2<float> v = {b.position[0], b.position[1]};
    return v;
}