#include "grid.hpp"

#include <algorithm>
#include <cassert>

#include "functions.hpp"

using bd::Cell;
using bd::Grid;

Cell::Cell() {}  // manca construzione esplicita

Cell::~Cell() {}

float Cell::getWidth() const { return width_; }

float Cell::getHeight() const { return height_; }

vector2 Cell::getCenter() const { return center_; }

boidPointers Cell::getBoidsInCell() const { return boidsInCell_; }

cellPointers Cell::getNearCells() const { return nearCells_; }

void Cell::setWidth(float width) { width_ = width; }

void Cell::setHeight(float height) { height_ = height; }

void Cell::setCenter(vector2 center) { center_ = center; }

void Cell::insertBoid(Boid& boid) { boidsInCell_.push_back(&boid); }

void Cell::setNearCells(cellPointers nearCellsPointers) {
  nearCells_ = nearCellsPointers;
}

void Grid::setupGrid() {  // per ora con dimensioni fissate
  grid_.resize(144);
  vector2 center{50.f, 50.f};
  assert(grid_.size() == 144);
  std::generate(grid_.begin(), grid_.end(), [&]() {
    Cell cell;
    cell.setCenter(center);
    center.x += 100.f;
    if (center.x > 1600.f) {
      center.x = 50.f;
      center.y += 100.f;
    }
    return cell;
  });
}

void Grid::linkNearCells() {
  assert(grid_.size() == 144);
  std::for_each(grid_.begin(), grid_.end(), [&](Cell& cell) {
    cellPointers nearCells = bd::findNearCellsPointers(cell, *this);
    cell.setNearCells(nearCells);
  });
}

Grid::Grid() {
  setupGrid();
  linkNearCells();
}

Grid::~Grid() {}

cellVector Grid::getCellVector() const { return grid_; }