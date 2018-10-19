// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef GAMEOFLIFEWORLD_H
#define GAMEOFLIFEWORLD_H

#include <functional>
#include <set>

#include "Coord.h"

class GameOfLifeWorld
   {
   public:
      GameOfLifeWorld(int nbCols,
                      int nbRows);

      void ForEachAliveCell(std::function<void(int cellCol,
                                               int cellRow)> func) const;

      int NbCols() const;
      int NbRows() const;

      void Animate(int col,
                   int row);
      void Kill(int col,
                int row);
      void Update();

   private:
      int mNbCols;
      int mNbRows;

      std::set<Coord> mAliveCells;
   };

#endif
