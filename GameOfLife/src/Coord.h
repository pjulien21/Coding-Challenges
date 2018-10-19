// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef COORD_H
#define COORD_H

struct Coord
   {
   int col = 0;
   int row = 0;
   };

bool operator<(const Coord& first,
               const Coord& second);

#endif
