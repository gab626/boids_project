#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>

#include "boid.hpp"

namespace bd {

class Rectangle {
  private:
  float xCenter_{};
  float yCenter_{};
  float width_{};
  float height_{};

  public:
  Rectangle(float, float, float, float);
  ~Rectangle();
  float getXCenter() const;
  float getYCenter() const;
  float getWidth() const;
  float getHeight() const;
  bool contains(const Boid&) const;
  bool intersects(const Rectangle&) const;
};

class Quadtree {
 private:
  Rectangle boundary_;
  int capacity_;
  std::vector<Boid> boids_;  // meglio boidPointers?
  bool divided;
  Quadtree* northWest_;  // std::unique_pointer?
  Quadtree* northEast_;
  Quadtree* southWest_;
  Quadtree* southEast_;

 public:
  Quadtree(const Rectangle&, int);
  ~Quadtree();
  bool insert(const Boid&);
  void subdivide();
  // void display(sf::RenderWindow&);  // non credo che mi serva
};

}  // namespace bd

#endif