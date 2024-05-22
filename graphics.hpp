#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>

#include "boid.hpp"

namespace bd {

sf::Vector2<float> boidToShape(Boid&);

}

#endif