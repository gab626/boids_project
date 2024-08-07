#include "boid.hpp"

#include "functions.hpp"

using bd::Boid;

void Boid::setupShape(sf::Color color) {
  boidShape_.setPointCount(4);
  boidShape_.setPoint(0, vector2(0.f, 5.f));
  boidShape_.setPoint(1, vector2(2.f, 0.f));
  boidShape_.setPoint(2, vector2(4.f, 5.f));
  boidShape_.setPoint(3, vector2(2.f, 4.f));
  boidShape_.setFillColor(color);
  boidShape_.setOrigin({2.f, 2.5f});
  boidShape_.setScale(2.f, 2.f);
}

Boid::Boid() {}

Boid::Boid(sf::Color color)
    : position_{bd::randomFloat(0.f, 1600.f), bd::randomFloat(0.f, 900.f)},
      velocity_{bd::randomVelocity(1000.f, 2000.f)} {
  Boid::setupShape(color);
  boidShape_.setPosition(position_);
  boidShape_.setRotation(bd::orientation(velocity_));
}

Boid::Boid(vector2 const& position, vector2 const& velocity, sf::Color color)
    : position_{position}, velocity_{velocity} {
  Boid::setupShape(color);
  boidShape_.setPosition(position);
  boidShape_.setRotation(bd::orientation(velocity));
}

Boid::~Boid() {}

vector2 Boid::getPosition() const { return position_; }

vector2 Boid::getVelocity() const { return velocity_; }

sf::ConvexShape Boid::getShape() const { return boidShape_; }

void Boid::setPosition(vector2 const& position) { position_ = position; }

void Boid::setVelocity(vector2 const& velocity) { velocity_ = velocity; }

void Boid::setPositionX(float x) { position_.x = x; }

void Boid::setPositionY(float y) { position_.y = y; }

void Boid::setShapePosition(vector2 const& position) {
  boidShape_.setPosition(position);
}