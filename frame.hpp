#ifndef FRAME_HPP
#define FRAME_HPP

namespace bd {
class Frame {
 private:
  int maxX_;
  int maxY_;

 public:
  Frame(int x = 1000, int y = 1000);
  int GetX() const;
  int GetY() const;
};
}  // namespace bd

#endif