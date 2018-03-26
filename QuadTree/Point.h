// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef POINT_H
#define POINT_H

struct Point
   {
   Point(float px, float py)
      : x(px)
      , y(py)
      {

      }

   float x = {};
   float y = {};
   };

#endif
