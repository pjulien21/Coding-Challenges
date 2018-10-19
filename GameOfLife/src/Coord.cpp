// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "Coord.h"

#include <tuple>

bool operator<(const Coord& first,
               const Coord& second)
   {
   return std::tie(first.col, first.row) < std::tie(second.col, second.row);
   }