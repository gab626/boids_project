#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>

#include "boid.hpp"

using array2 = std::array<double, 2>;

namespace bd {

array2 operator+(array2 const&, array2 const&);

array2 operator-(array2 const&, array2 const&);

array2 operator*(double, array2 const&);

double norm(array2 const&);

double distance(Boid const&, Boid const&);

array2 centerMass(std::array<Boid, 20> const&);

void switchPosition(Boid&);

array2 randomPosition();

array2 randomVelocity();

}  // namespace bd

#endif