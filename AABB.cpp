// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "AABB.h"

AABB::AABB(const Point& topLeft,
                 float  width,
                 float  height)
   : mTopLeft(topLeft)
   , mBottomRight(topLeft.x + width,
                  topLeft.y + height)
   {

   }

bool AABB::Contains(const Point& point) const
   {
   return (point.x >= mTopLeft.x &&
           point.x <= mBottomRight.x &&
           point.y >= mTopLeft.y &&
           point.y <= mBottomRight.y);
   }

bool AABB::Overlaps(const AABB& otherRect) const
   {
   // No overlap if a rectangle is on the left of the other 
   if (mTopLeft.x > otherRect.mBottomRight.x || otherRect.mTopLeft.x > mBottomRight.x)
      return (false);

   // No overlap if a rectangle is on top of the other
   if (mTopLeft.y > otherRect.mBottomRight.y || otherRect.mTopLeft.y > mBottomRight.y)
      return (false);

   return (true);
   }