#include "simulation.hpp"

using bd::Flock;
using bd::Simulation;

Simulation::Simulation()
    : greenFlock_{Flock(sf::Color::Green)},
      mainWindow_{sf::RenderWindow(sf::VideoMode(1600, 900), "Window")} {}

Simulation::~Simulation() {}

void Simulation::operator()() {
  mainWindow_.setPosition(sf::Vector2i{10, 10});
  while (mainWindow_.isOpen()) {
    sf::Event event;
    while (mainWindow_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) mainWindow_.close();
    }

    mainWindow_.clear(sf::Color::Black);

    for (int i{}; i < greenFlock_.getN(); i++) {
      mainWindow_.draw(greenFlock_.getFlock()[i].getShape());
    }
    greenFlock_.evolve();
    mainWindow_.display();
  }
}