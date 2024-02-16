#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>

#include "boid.hpp"

namespace bd {

std::array<double, 2> operator+(std::array<double, 2> const&,
                                std::array<double, 2> const&);
std::array<double, 2> operator-(std::array<double, 2> const&,
                                std::array<double, 2> const&);

std::array<double, 2> operator*(double, std::array<double, 2> const&);
//non riesco a fare overload di operator +=
double norm(std::array<double, 2> const&);

double distance(Boid const&, Boid const&);

}  // namespace bd

#endif