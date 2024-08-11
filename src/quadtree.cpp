#include "quadtree.hpp"

#include "boid.hpp"

using bd::Quadtree;
using bd::Rectangle;

Rectangle::Rectangle(float x, float y, float width, float height)
    : xCenter_{x}, yCenter_{y}, width_{width}, height_{height} {}

Rectangle::~Rectangle() {}

float Rectangle::getXCenter() const { return xCenter_; }
float Rectangle::getYCenter() const { return yCenter_; }
float Rectangle::getWidth() const { return width_; }
float Rectangle::getHeight() const { return height_; }

bool Rectangle::contains(const Boid& boid) const {
  vector2 position = boid.getPosition();
  return (position.x >= xCenter_ - width_ / 2 &&
          position.x <= xCenter_ + width_ / 2 &&
          position.y >= yCenter_ - height_ / 2 &&
          position.y <= yCenter_ + height_ / 2);
}

bool Rectangle::intersects(const Rectangle& range) const {
  return !(range.xCenter_ - range.width_ / 2 > xCenter_ + width_ / 2 ||
           range.xCenter_ + range.width_ / 2 < xCenter_ - width_ / 2 ||
           range.yCenter_ - range.height_ / 2 > yCenter_ + height_ / 2 ||
           range.yCenter_ + range.height_ / 2 < yCenter_ - height_ / 2);
}

Quadtree::Quadtree(const Rectangle& boundary, int capacity)
    : boundary_{boundary},
      capacity_{capacity},
      divided{false},
      northWest_{nullptr},
      northEast_{nullptr},
      southWest_{nullptr},
      southEast_{nullptr} {}

Quadtree::~Quadtree() {
  delete northWest_;
  delete northEast_;
  delete southWest_;
  delete southEast_;
}

bool Quadtree::insert(const Boid& boid) {
  if (!boundary_.contains(boid)) return false;
  if (boids_.size() < capacity_) {
    boids_.push_back(boid);
    return true;
  }
  if (!divided) subdivide();
  if (northWest_->insert(boid)) return true;
  if (northEast_->insert(boid)) return true;
  if (southWest_->insert(boid)) return true;
  if (southEast_->insert(boid)) return true;
  return false;
}

void Quadtree::subdivide() {
  float x = boundary_.getXCenter();
  float y = boundary_.getYCenter();
  float w = boundary_.getWidth() / 2;
  float h = boundary_.getHeight() / 2;

  Rectangle nw(x - w / 2, y - h / 2, w, h);
  northWest_ = new Quadtree(nw, capacity_);
  Rectangle ne(x + w / 2, y - h / 2, w, h);
  northEast_ = new Quadtree(ne, capacity_);
  Rectangle sw(x - w / 2, y + h / 2, w, h);
  southWest_ = new Quadtree(sw, capacity_);
  Rectangle se(x + w / 2, y + h / 2, w, h);
  southEast_ = new Quadtree(se, capacity_);

  divided = true;
}