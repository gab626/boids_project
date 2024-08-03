#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>
#include <vector>

#include "boid.hpp"

using boidPointers = std::vector<bd::Boid*>;

namespace bd {

float norm(const vector2&);

float distance(const Boid&, const Boid&);  // perché Boid e non vector2?

float mean(std::vector<float>); // const&?

float standardDeviation(std::vector<float>); // const&?

float orientation(const vector2&);  // idem qua

vector2 separationVelocity(float, const boidPointers&, const Boid&);

vector2 alignmentVelocity(float, const boidPointers&, const Boid&);

vector2 cohesionVelocity(float, const boidPointers&, const Boid&);

vector2 closedSpace(const Boid&);

void speedLimit(Boid&, float);

float randomFloat(float, float);

vector2 randomVelocity(float, float);

}  // namespace bd

#endif