// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef AABB_H
#define AABB_H

#include "Point.h"

class AABB
   {
   public:
      AABB(const Point& topLeft,
                 float  width,
                 float  height);

      bool Contains(const Point& point) const;
      bool Overlaps(const AABB& otherRect) const;

      const Point& TopLeft() const { return mTopLeft; }

      float Height() const { return mBottomRight.y - mTopLeft.y; }
      float Width() const { return mBottomRight.x - mTopLeft.x; }
   private:
      Point mTopLeft;
      Point mBottomRight;
   };

#endif
