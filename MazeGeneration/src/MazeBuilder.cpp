// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "MazeBuilder.h"

ColRow AdjacentCell(ColRow cell,
                    Direction direction);

MazeBuilder::MazeBuilder(int nbCols,
                         int nbRows)
   : mMaze(nbCols,
           nbRows)
   , mGen(std::random_device()())
   {
   std::uniform_int_distribution<> randomCellCol(0, nbCols - 1);
   std::uniform_int_distribution<> randomCellRow(0, nbRows - 1);
   mCurrentCell = { randomCellCol(mGen),
                    randomCellRow(mGen) };
   }

ColRow MazeBuilder::CurrentCell() const
   {
   return mCurrentCell;
   }

const Maze& MazeBuilder::GetMaze()
   {
   return (mMaze);
   }

bool MazeBuilder::NextBuildStep()
   {
                             // Nothing left to do if all cells have been visited
   if (mVisitedCellSet.size() == mMaze.NbCols() * mMaze.NbRows())
      {
      mCurrentCell = { -1, -1 };
      return (false);
      }  

                             // Obtain next current cell with unvisited neighboors
   std::vector<Direction> NextUnvisitedCells = UnvisitedAdjacentCells(mCurrentCell);
   while (NextUnvisitedCells.empty() &&
      !mCellStack.empty())
      {
      mCurrentCell = mCellStack.back();
      mCellStack.pop_back();
      NextUnvisitedCells = UnvisitedAdjacentCells(mCurrentCell);
      }

   if (NextUnvisitedCells.empty())
      return (false);

   std::uniform_int_distribution<> randomUnvisitedCell(0, NextUnvisitedCells.size() - 1);
   const Direction randomUnivisitedDirection = NextUnvisitedCells[randomUnvisitedCell(mGen)];

   mCellStack.push_back(mCurrentCell);
   mMaze.RemoveWall(mCurrentCell.col,
                    mCurrentCell.row,
                    randomUnivisitedDirection);
   mCurrentCell = AdjacentCell(mCurrentCell,
                               randomUnivisitedDirection);
   mVisitedCellSet.insert(mCurrentCell);

   return (true);
   }

std::vector<Direction> MazeBuilder::UnvisitedAdjacentCells(const ColRow cell)
   {
   auto IsValidColRow = [this](const ColRow coord) {
      return (coord.col >= 0 &&
              coord.row >= 0 &&
              coord.col < mMaze.NbCols() &&
              coord.row < mMaze.NbRows());
      };

   auto IsUnVisited = [this](const ColRow coord) {
      return (mVisitedCellSet.find(coord) == mVisitedCellSet.end());
      };

   std::vector<Direction> unvisitedAdjacentCells;
   if (!IsValidColRow(cell))
      return (unvisitedAdjacentCells);

   const ColRow northCell = AdjacentCell(cell, Direction::North);
   const ColRow eastCell = AdjacentCell(cell, Direction::East);
   const ColRow southCell = AdjacentCell(cell, Direction::South);
   const ColRow westCell = AdjacentCell(cell, Direction::West);

   if (IsValidColRow(northCell) &&
       IsUnVisited(northCell))
      unvisitedAdjacentCells.push_back(Direction::North);

   if (IsValidColRow(eastCell) &&
       IsUnVisited(eastCell))
      unvisitedAdjacentCells.push_back(Direction::East);

   if (IsValidColRow(southCell) &&
       IsUnVisited(southCell))
      unvisitedAdjacentCells.push_back(Direction::South);

   if (IsValidColRow(westCell) &&
       IsUnVisited(westCell))
      unvisitedAdjacentCells.push_back(Direction::West);

   return (unvisitedAdjacentCells);
   }

ColRow AdjacentCell(ColRow cell,
                    Direction direction)
   {
   switch (direction)
      {
      case Direction::North:
         return { cell.col, cell.row - 1 };
      case Direction::East:
         return { cell.col + 1, cell.row };
      case Direction::South:
         return { cell.col, cell.row + 1 };
      case Direction::West:
         return { cell.col - 1, cell.row };
      }

   return (cell);
   }