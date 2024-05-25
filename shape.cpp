#include "shape.hpp"

using bd::Boid;
using bd::BoidShape;

BoidShape::BoidShape() {
  this->setPointCount(4);
  this->setPoint(0, vector2(0.f, 5.f));
  this->setPoint(1, vector2(2.f, 0.f));
  this->setPoint(2, vector2(4.f, 5.f));
  this->setPoint(3, vector2(2.f, 4.f));
  this->setFillColor(sf::Color::Green);
  this->setOrigin({2.f, 3.f});
  this->setScale(2.5f, 2.5f);
}

BoidShape::~BoidShape() {}

std::size_t BoidShape::getPointCount() const { return 4; }

vector2 BoidShape::getPoint(std::size_t index) const {
  switch (index) {
    case 0:
      return vector2(0.f, 5.f);
    case 1:
      return vector2(2.f, 0.f);
    case 2:
      return vector2(4.f, 5.f);
    case 3:
      return vector2(2.f, 4.f);
    default:
      return vector2(0.f, 0.f);
  }
}