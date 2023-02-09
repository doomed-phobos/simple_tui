#pragma once

namespace tui {
   template<typename T>
   struct PointT {
      T x, y;

      constexpr PointT() :
         x{0}, y{0} {}
      constexpr PointT(const T& _x, const T& _y) :
         x{_x}, y{_y} {}

      PointT operator+(const PointT& pt) const {
         return {x + pt.x, y + pt.y};
      }
   };

   typedef PointT<int> Point;
} // namespace tui