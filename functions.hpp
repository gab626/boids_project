#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>
#include <vector>

#include "boid.hpp"

namespace bd {

array2 operator+(array2 const&, array2 const&);

array2 operator-(array2 const&, array2 const&);

array2 operator*(float, array2 const&);

float norm(array2 const&);

float distance(Boid const&, Boid const&);

array2 meanVelocity(std::vector<Boid*> const&);

array2 centerMass(std::vector<Boid*> const&);

void toroidalSpace(Boid&);

void speedLimit(Boid&, float);

array2 randomPosition();

array2 randomVelocity();

}  // namespace bd

#endif