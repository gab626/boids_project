#include "frame.hpp"

bd::Frame::Frame(int x, int y) : maxX_(x), maxY_(y){};
int bd::Frame::GetX() const { return maxX_; };
int bd::Frame::GetY() const { return maxY_; };