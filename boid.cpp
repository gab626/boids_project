#include "boid.hpp"

#include <cmath>
#include <random>
#include <numeric>  //ancora non ho usato accumulate

vector2 bd::operator+(vector2 const& v1, vector2 const& v2) {
  double x = v1[0] + v2[0];
  double y = v1[1] + v2[1];
  return vector2{x, y};
};

vector2 bd::operator*(double c, vector2 const& v) {
  double x = c * v[0];
  double y = c * v[1];
  return vector2{x, y};
};

double bd::norm(vector2 v) {
  double x2 = v[0] * v[0];
  double y2 = v[1] * v[1];
  return std::sqrt(x2 + y2);
};

double bd::Boid::setPosition() {
  std::random_device eng;  // default random engine non funziona?
  std::uniform_int_distribution<> uniform(0, 1000);
  return uniform(eng);
}

bd::Boid::Boid() {
  position_[0] = setPosition();
  position_[1] = setPosition();
};

double bd::Boid::getX() const { return position_[0]; };

double bd::Boid::getY() const { return position_[1]; };

double bd::Boid::distance(Boid const& b) const {
  return norm(this->position_ + (-1) * b.position_);
};
//inizializzando i parametri di v1 v2 v3 a caso
/* vector2 bd::Boid::vSeparation(Boid const& b) {
  if (this->distance(b) < ds) {
    vector2 v1 = -1 * s * (this->position_ + (-1) * b.position_);
    return v1;
  } else return {0,0};
};  //SBAGLIATA

vector2 bd::Boid::vAlignment(Boid const& b) {};
vector2 bd::Boid::vCohesion(Boid const& b) {}; */

void bd::Boid::flight() {  // velocità fissate per ora
  position_ = position_ + velocity_;  // rivedere overload (esempio nelle slides)
};

void bd::Boid::reverseVx() { velocity_[0] = -1 * velocity_[0]; };

void bd::Boid::reverseVy() { velocity_[1] *= -1 * velocity_[1]; };