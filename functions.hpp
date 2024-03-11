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

}  // namespace bd

#endif