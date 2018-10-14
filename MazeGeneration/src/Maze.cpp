// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "Maze.h"

Maze::Maze(int nbCols,
           int nbRows)
   : mNbCols(nbCols)
   , mNbRows(nbRows)
   , mCells(nbCols * nbRows)
   {

   }

MazeCell* Maze::AdjacentCell(int col,
                             int row,
                             Direction direction)
   {
   MazeCell* cell = CellAt(col,
                           row);
   if (cell == nullptr)
      return (nullptr);

   int adjacentCol = col;
   int adjacentRow = row;
   switch (direction)
      {
      case Direction::North:
         {
         --adjacentRow;
         break;
         }
      case Direction::East:
         {
         ++adjacentCol;
         break;
         }
      case Direction::South:
         {
         ++adjacentRow;
         break;
         }
      case Direction::West:
         {
         --adjacentCol;
         break;
         }
      }

   return (CellAt(adjacentCol,
                  adjacentRow));
   }

MazeCell* Maze::CellAt(int col,
                       int row)
   {
   if (col < 0 || row < 0 || col >= mNbCols || row >= mNbRows)
      return (nullptr);

   return (&(mCells[col + row * mNbCols]));
   }

int Maze::NbCols() const noexcept
   {
   return mNbCols;
   }

int Maze::NbRows() const noexcept
   {
   return mNbRows;
   }

void Maze::ForEachCell(std::function<void(const MazeCell& cell,
                                                int       cellCol,
                                                int       cellRow)> func) const
   {
   int curIdx = 0;
   for (const auto& cell : mCells)
      {
      func(cell,
           curIdx % mNbCols,
           curIdx / mNbCols);
      ++curIdx;
      }
   }

void Maze::RemoveWall(int col,
                      int row,
                      Direction direction)
   {
   MazeCell* cell = CellAt(col,
                           row);
   if (cell == nullptr)
      return;

   MazeCell* adjacentCell = AdjacentCell(col,
                                         row,
                                         direction);
   switch (direction)
      {
      case Direction::North:
         {
         cell->HasNorthWall = false;
         if (adjacentCell != nullptr)
            adjacentCell->HasSouthWall = false;
         break;
         }
      case Direction::East:
         {
         cell->HasEastWall = false;
         if (adjacentCell != nullptr)
            adjacentCell->HasWestWall = false;
         break;
         }
      case Direction::South:
         {
         cell->HasSouthWall = false;
         if (adjacentCell != nullptr)
            adjacentCell->HasNorthWall = false;
         break;
         }
      case Direction::West:
         {
         cell->HasWestWall = false;
         if (adjacentCell != nullptr)
            adjacentCell->HasEastWall = false;
         break;
         }
      }
   }
