#pragma once

namespace tui {
   struct Point {
      int x, y;

      constexpr Point() :
         x{0}, y{0} {}
      constexpr Point(const int& _x, const int& _y) :
         x{_x}, y{_y} {}

      Point operator+(const Point& pt) const {
         return {x + pt.x, y + pt.y};
      }
   };
} // namespace tui