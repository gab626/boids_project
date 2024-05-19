#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>
#include <vector>

#include "boid.hpp"

using array2 = std::array<double, 2>;

namespace bd {

array2 operator+(array2 const&, array2 const&);

array2 operator-(array2 const&, array2 const&);

array2 operator*(double, array2 const&);

double norm(array2 const&);

double distance(Boid const&, Boid const&);

array2 meanVelocity(std::vector<Boid*> const&);

array2 centerMass(std::vector<Boid*> const&);

void switchPosition(Boid&);

void speedLimit(Boid&);

array2 randomPosition();

array2 randomVelocity();

}  // namespace bd

#endif