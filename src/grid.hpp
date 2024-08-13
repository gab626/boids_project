#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <memory> //

#include "boid.hpp"

using boidPointers = std::vector<bd::Boid*>;
using cellPointers = std::vector<bd::Cell*>;
using cellVector = std::vector<bd::Cell>;

namespace bd {

class Cell {
 private:
  float width_ = 100.f;  // fissati per ora
  float height_ = 100.f;
  vector2 center_;
  boidPointers boidsInCell_;
  cellPointers nearCells_;

 public:
  Cell();
  ~Cell();
  float getWidth() const; //
  float getHeight() const; //
  vector2 getCenter() const;
  boidPointers getBoidsInCell() const;
  cellPointers getNearCells() const;
  void setWidth(float); //
  void setHeight(float); //
  void setCenter(vector2);
  void insertBoid(Boid&);
  void setNearCells(cellPointers);
};

class Grid {
 private:
  cellVector grid_;
  void setupGrid();
  void linkNearCells();

 public:
  Grid();
  ~Grid();
  cellVector getCellVector() const;
};

}  // namespace bd

#endif