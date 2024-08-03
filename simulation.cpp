#include "simulation.hpp"

using bd::Flock;
using bd::Simulation;

Simulation::Simulation()
    : greenFlock_{Flock(sf::Color::Green)},
      redFlock_{Flock(sf::Color::Red)},
      blueFlock_{Flock(sf::Color::Blue)},
      mainWindow_{sf::RenderWindow(sf::VideoMode(1600, 900), "Window")} {}

Simulation::~Simulation() {}

void Simulation::operator()() {
  while (mainWindow_.isOpen()) {
    sf::Event event;
    while (mainWindow_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) mainWindow_.close();
    }

    mainWindow_.clear(sf::Color::Black);

    for (int i{}; i < greenFlock_.getN(); i++) {
      mainWindow_.draw(greenFlock_.getFlock()[i].getShape());
    }
    for (int i{}; i < redFlock_.getN(); i++) {
      mainWindow_.draw(redFlock_.getFlock()[i].getShape());
    }
    for (int i{}; i < blueFlock_.getN(); i++) {
      mainWindow_.draw(blueFlock_.getFlock()[i].getShape());
    }
    greenFlock_.evolve();
    redFlock_.evolve();
    blueFlock_.evolve();
    mainWindow_.display();
  }
}