#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <array>

namespace bd {

std::array<double, 2> operator+(std::array<double, 2> const&,
                                std::array<double, 2> const&);
std::array<double, 2> operator-(std::array<double, 2> const&,
                                std::array<double, 2> const&);

std::array<double, 2> operator*(double, std::array<double, 2> const&);

double norm(std::array<double, 2> const&);

}  // namespace bd

#endif