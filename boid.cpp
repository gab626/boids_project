#include "boid.hpp"

#include "functions.hpp"

using bd::Boid;

Boid::Boid() : position_{}, velocity_{} {}

Boid::Boid(vector2 const& position, vector2 const& velocity)
    : position_{position}, velocity_{velocity} {}

Boid::~Boid() {}

vector2 Boid::getPosition() const { return position_; }

vector2 Boid::getVelocity() const { return velocity_; }

void Boid::setPosition(vector2 const& position) { position_ = position; }

void Boid::setVelocity(vector2 const& velocity) { velocity_ = velocity; }

void Boid::setPositionX(float x) { position_.x = x; }

void Boid::setPositionY(float y) { position_.y = y; }