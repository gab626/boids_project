#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>
#include <vector>

#include "boid.hpp"

using boidPointers = std::vector<bd::Boid*>;

namespace bd {

array2 operator+(array2 const&, array2 const&);

array2 operator-(array2 const&, array2 const&);

array2 operator*(float, array2 const&);

float norm(array2 const&);

float distance(Boid const&, Boid const&);

array2 separationVelocity(float, boidPointers const&, Boid const&);

array2 alignmentVelocity(float, boidPointers const&, Boid const&);

array2 cohesionVelocity(float, boidPointers const&, Boid const&);

void toroidalSpace(Boid&);

void speedLimit(Boid&, float);

array2 randomPosition();

array2 randomVelocity();

}  // namespace bd

#endif