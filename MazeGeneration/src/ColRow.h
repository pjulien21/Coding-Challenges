// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef COLROW_H
#define COLROW_H

struct ColRow
   {
   int col = {};
   int row = {};
   };

bool operator<(const ColRow& first,
               const ColRow& second);

#endif
