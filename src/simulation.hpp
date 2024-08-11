#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>

#include "flock.hpp"

namespace bd {

class Simulation {
 private:
  sf::RenderWindow mainWindow_;
  bd::Flock greenFlock_;

 public:
  Simulation();
  ~Simulation();
  void operator()();
};

}  // namespace bd

#endif