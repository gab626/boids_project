#include "cell.hpp"

using bd::Cell;

Cell::Cell() {}

Cell::~Cell() {}

float Cell::getWidth() const { return width_; }

float Cell::getHeight() const { return height_; }

vector2 Cell::getCenter() const { return center_; }

// int Cell::getKey() const { return key_; }

boidPointers Cell::getBoidsInCell() const { return boidsInCell_; }

void Cell::setWidth(float width) { width_ = width; }

void Cell::setHeight(float height) { height_ = height; }

void Cell::setCenter(vector2 center) { center_ = center; }

// void Cell::setKey(int key) { key_ = key; }

void Cell::insertBoid(Boid& boid) { boidsInCell_.push_back(&boid); }