// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "GameOfLifeWorld.h"

#include <algorithm>
#include <map>

GameOfLifeWorld::GameOfLifeWorld(int nbCols,
                                 int nbRows)
   : mNbCols(nbCols)
   , mNbRows(nbRows)
   {

   }

void GameOfLifeWorld::Animate(int col,
                              int row)
   {
   if (col < 0 || row < 0 || col >= mNbCols || row >= mNbRows)
      return;

   mAliveCells.insert({ col, row });
   }

void GameOfLifeWorld::ForEachAliveCell(std::function<void(int cellCol,
                                                          int cellRow)> func) const
   {
   for (const Coord& aliveCell : mAliveCells)
      {
      func(aliveCell.col,
           aliveCell.row);
      }
   }

void GameOfLifeWorld::Kill(int col,
                           int row)
   {
   if (col < 0 || row < 0 || col >= mNbCols || row >= mNbRows)
      return;

   mAliveCells.erase({ col, row });
   }

int GameOfLifeWorld::NbCols() const
   {
   return (mNbCols);
   }

int GameOfLifeWorld::NbRows() const
   {
   return (mNbRows);
   }

void GameOfLifeWorld::Update()
   {
                             // For each cell adjacent to alive cells,
                             // count the number of alive neighboors. 
   std::map<Coord, int> cellNbAliveNeighboorsMap;
   for (const Coord& aliveCell : mAliveCells)
      {
      const int adjMinCol = std::max(0, aliveCell.col - 1);
      const int adjMaxCol = std::min(mNbCols - 1, aliveCell.col + 1);
      const int adjMinRow = std::max(0, aliveCell.row - 1);
      const int adjMaxRow = std::min(mNbRows - 1, aliveCell.row + 1);
      for (int curCol = adjMinCol; curCol <= adjMaxCol; ++curCol)
         {
         for (int curRow = adjMinRow; curRow <= adjMaxRow; ++curRow)
            {
                             // Ignore self
            if (curCol == aliveCell.col &&
                curRow == aliveCell.row)
               continue;

            const Coord curCoord { curCol,
                                   curRow };

            auto it = cellNbAliveNeighboorsMap.find(curCoord);
            if (it != cellNbAliveNeighboorsMap.end())
               ++(it->second);
            else
               cellNbAliveNeighboorsMap.insert(std::make_pair(curCoord, 1));
            }
         }
      }

   std::set<Coord> mNextAliveCells;
   for (const auto& cellWithAliveNeighboors : cellNbAliveNeighboorsMap)
      {
      const Coord& cell = cellWithAliveNeighboors.first;
      const int nbAliveNeighboors = cellWithAliveNeighboors.second;
      const bool cellIsAlive = (mAliveCells.find(cell) != mAliveCells.end());

                             // Alive cells remains alive only if they have
                             // two or three alive neighboors.
      if (cellIsAlive &&
          nbAliveNeighboors != 2 &&
          nbAliveNeighboors != 3)
         continue;

                             // Dead cells becomes alive if they have exactly
                             // three alive neighboors.
      if (!cellIsAlive &&
          nbAliveNeighboors != 3)
         continue;

      mNextAliveCells.insert(cell);
      }

   mAliveCells = std::move(mNextAliveCells);
   }
