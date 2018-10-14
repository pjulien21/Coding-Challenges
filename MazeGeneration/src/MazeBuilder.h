// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef MAZEBUILDER_H
#define MAZEBUILDER_H

#include <random>
#include <set>
#include <vector>

#include "ColRow.h"
#include "Maze.h"

class MazeBuilder
   {
   public:
      MazeBuilder(int nbCols,
                  int nbRows);

      ColRow CurrentCell() const;
      
      const Maze& GetMaze();

      bool NextBuildStep();

   private:
      std::vector<Direction> UnvisitedAdjacentCells(const ColRow cellColrow);

      Maze mMaze;
      
      ColRow mCurrentCell;
      std::set<ColRow> mVisitedCellSet;
      std::vector<ColRow> mCellStack;

      std::mt19937 mGen;
   };

#endif