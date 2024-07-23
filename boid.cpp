#include "boid.hpp"

#include "functions.hpp"

using bd::Boid;

void Boid::setupShape() {
  boidShape_.setPointCount(4);
  boidShape_.setPoint(0, vector2(0.f, 5.f));
  boidShape_.setPoint(1, vector2(2.f, 0.f));
  boidShape_.setPoint(2, vector2(4.f, 5.f));
  boidShape_.setPoint(3, vector2(2.f, 4.f));
  boidShape_.setFillColor(sf::Color::Green);
  boidShape_.setOrigin({2.f, 3.f});
  boidShape_.setScale(2.5f, 2.5f);
}

Boid::Boid()  // si potrebbe fare con un generate, da valutare
    : position_{bd::randomFloat(0.f, 800.f), bd::randomFloat(0.f, 800.f)},
      velocity_{bd::randomFloat(-1000.f, 1000.f), bd::randomFloat(-1000.f, 1000.f)} {
  Boid::setupShape();
  boidShape_.setPosition(position_);
  boidShape_.setRotation(bd::orientation(velocity_));
}

Boid::Boid(vector2 const& position, vector2 const& velocity)
    : position_{position}, velocity_{velocity} {
  Boid::setupShape();
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