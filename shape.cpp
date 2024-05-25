#include "shape.hpp"

using bd::Boid;
using bd::BoidShape;

BoidShape::BoidShape() {
  this->setPointCount(4);
  this->setPoint(0, sf::Vector2f(0.f, 5.f));
  this->setPoint(1, sf::Vector2f(2.f, 0.f));
  this->setPoint(2, sf::Vector2f(4.f, 5.f));
  this->setPoint(3, sf::Vector2f(2.f, 4.f));
  this->setFillColor(sf::Color::Green);
  this->setOrigin({2.f, 3.f});
  this->setScale(2.5f, 2.5f);
}

BoidShape::~BoidShape() {}

std::size_t BoidShape::getPointCount() const { return 4; }

sf::Vector2f BoidShape::getPoint(std::size_t index) const {
  switch (index) {
    case 0:
      return sf::Vector2f(0.f, 5.f);
    case 1:
      return sf::Vector2f(2.f, 0.f);
    case 2:
      return sf::Vector2f(4.f, 5.f);
    case 3:
      return sf::Vector2f(2.f, 4.f);
    default:
      return sf::Vector2f(0.f, 0.f);
  }
}