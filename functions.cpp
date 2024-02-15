#include "functions.hpp"

#include <cmath>

std::array<double, 2> bd::operator+(std::array<double, 2> const& v1,
                                    std::array<double, 2> const& v2) {
  return {v1[0] + v2[0], v1[1] + v2[1]};
}

std::array<double, 2> bd::operator-(std::array<double, 2> const& v1,
                                    std::array<double, 2> const& v2) {
  return {v1[0] - v2[0], v1[1] - v2[1]};
}

std::array<double, 2> bd::operator*(double c, std::array<double, 2> const& v) {
  return {c * v[0], c * v[1]};
}

double bd::norm(std::array<double, 2> const& v) {
  return std::sqrt(v[0] * v[0] + v[1] * v[1]);
}