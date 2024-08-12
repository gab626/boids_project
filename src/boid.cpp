#include "boid.hpp"

#include "functions.hpp"

using bd::Boid;
using bd::Cell;

void Boid::setupShape(sf::Color color) {
  boidShape_.setPointCount(4);
  boidShape_.setPoint(0, vector2(0.f, 5.f));
  boidShape_.setPoint(1, vector2(2.f, 0.f));
  boidShape_.setPoint(2, vector2(4.f, 5.f));
  boidShape_.setPoint(3, vector2(2.f, 4.f));
  boidShape_.setFillColor(color);
  boidShape_.setOrigin({2.f, 2.5f});
  boidShape_.setScale(1.5f, 1.5f);
}

Boid::Boid() {}

Boid::Boid(sf::Color color)
    : position_{bd::randomFloat(0.f, 1600.f), bd::randomFloat(0.f, 900.f)},
      velocity_{bd::randomVelocity(1000.f, 2000.f)},
      cellPointer_{nullptr} {
  Boid::setupShape(color);
  boidShape_.setPosition(position_);
  boidShape_.setRotation(bd::orientation(velocity_));
}

Boid::Boid(const vector2& position,
           const vector2& velocity,  // manca inizializzazione cellPointer_
           const sf::Color& color)
    : position_{position}, velocity_{velocity} {
  Boid::setupShape(color);
  boidShape_.setPosition(position);
  boidShape_.setRotation(bd::orientation(velocity));
}

Boid::~Boid() {}

vector2 Boid::getPosition() const { return position_; }

vector2 Boid::getVelocity() const { return velocity_; }

sf::ConvexShape Boid::getShape() const { return boidShape_; }

Cell* Boid::getCellPointer() const { return cellPointer_; }

void Boid::setPosition(const vector2& position) { position_ = position; }

void Boid::setVelocity(const vector2& velocity) { velocity_ = velocity; }

void Boid::setPositionX(float x) { position_.x = x; }

void Boid::setPositionY(float y) { position_.y = y; }

void Boid::setShapePosition(const vector2& position) {
  boidShape_.setPosition(position);
}

void Boid::setCellPointer(Cell* cellPointer) { cellPointer_ = cellPointer; }