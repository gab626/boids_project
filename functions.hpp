#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>
#include <vector>

#include "boid.hpp"

using boidPointers = std::vector<bd::Boid*>;

namespace bd {

float norm(vector2 const&);

float distance(Boid const&, Boid const&);  // perché Boid e non vector2?

float mean(std::vector<float>);

float standardDeviation(std::vector<float>);

float orientation(vector2 const&);  // idem qua

vector2 separationVelocity(float, boidPointers const&, Boid const&);

vector2 alignmentVelocity(float, boidPointers const&, Boid const&);

vector2 cohesionVelocity(float, boidPointers const&, Boid const&);

vector2 closedSpace(Boid const&);

void speedLimit(Boid&, float);

float randomFloat(float, float);

vector2 randomVelocity(float, float);

}  // namespace bd

#endif