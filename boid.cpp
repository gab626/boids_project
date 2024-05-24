#include "boid.hpp"

#include "functions.hpp"

using bd::Boid;

Boid::Boid() : position_{}, velocity_{} {}

Boid::Boid(array2 const& position, array2 const& velocity)
    : position_{position}, velocity_{velocity} {}

Boid::~Boid() {}

array2 Boid::getPosition() const { return position_; }

array2 Boid::getVelocity() const { return velocity_; }

float Boid::getPositionX() const { return position_[0]; }

float Boid::getPositionY() const { return position_[1]; }

void Boid::setPosition(array2 const& a) { position_ = a; }

void Boid::setVelocity(array2 const& b) { velocity_ = b; }

void Boid::setPositionX(float x) { position_[0] = x; }

void Boid::setPositionY(float y) { position_[1] = y; }