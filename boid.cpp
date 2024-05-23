#include "boid.hpp"

#include "functions.hpp"

bd::Boid::Boid(array2 const& pos, array2 const& vel)
    : position_{pos}, velocity_{vel} {}

bd::Boid::~Boid() {}

array2 bd::Boid::get_Pos() const { return position_; }

array2 bd::Boid::get_Vel() const { return velocity_; }

float bd::Boid::get_Pos_X() const { return position_[0]; }

float bd::Boid::get_Pos_Y() const { return position_[1]; }

void bd::Boid::set_Pos(array2 const& a) { position_ = a; }

void bd::Boid::set_Vel(array2 const& b) { velocity_ = b; }

void bd::Boid::set_PosX(float x) { position_[0] = x; }

void bd::Boid::set_PosY(float y) { position_[1] = y; }