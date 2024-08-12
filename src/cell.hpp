#ifndef CELL_HPP
#define CELL_HPP

#include <vector>

#include "boid.hpp"

using boidPointers = std::vector<bd::Boid*>;

namespace bd {

class Cell {
 private:
  float width_ = 100.f;  // fissati per ora
  float height_ = 100.f;
  vector2 center_;
  // int key_;
  boidPointers boidsInCell_;

 public:
  Cell();
  ~Cell();
  float getWidth() const;
  float getHeight() const;
  vector2 getCenter() const;
  // int getKey() const;
  boidPointers getBoidsInCell() const;
  void setWidth(float);
  void setHeight(float);
  void setCenter(vector2);
  void setKey(int);
  void insertBoid(Boid&);
};

}  // namespace bd

#endif