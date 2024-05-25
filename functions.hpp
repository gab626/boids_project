#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>
#include <vector>

#include "boid.hpp"

using boidPointers = std::vector<bd::Boid*>;

namespace bd {

float norm(vector2 const&);

float distance(Boid const&, Boid const&);

vector2 separationVelocity(float, boidPointers const&, Boid const&);

vector2 alignmentVelocity(float, boidPointers const&, Boid const&);

vector2 cohesionVelocity(float, boidPointers const&, Boid const&);

void toroidalSpace(Boid&);

void speedLimit(Boid&, float);

vector2 randomPosition();

vector2 randomVelocity();

}  // namespace bd

#endif