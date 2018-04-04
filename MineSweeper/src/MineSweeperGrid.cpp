// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "MineSweeperGrid.h"

#include <algorithm>
#include <random>
#include <vector>

//--------------------------------------------------------------
MineSweeperGrid::MineSweeperGrid(int nbCols,
                                 int nbRows,
                                 int nbMines)
   : mNbCols(nbCols)
   , mNbRows(nbRows)
   , mNbMines(nbMines)
   , mCells(nbCols * nbRows)
   {
   PlaceMinesRandomly();
   }

//--------------------------------------------------------------
void MineSweeperGrid::ForEachCell(std::function<void(const MineSweeperCell& cellInfo,
                                                           int              cellCol,
                                                           int              cellRow)> func) const
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

//--------------------------------------------------------------
void MineSweeperGrid::ForEachAdjacentCell(int col,
                                          int row,
                                          std::function<void(MineSweeperCell& cell,
                                                             int cellCol,
                                                             int cellRow)> func)
   {
   if (col < 0 || row < 0 || col >= mNbCols || row >= mNbRows)
      return;

   const int adjMinCol = std::max(0, col - 1);
   const int adjMaxCol = std::min(mNbCols - 1, col + 1);
   const int adjMinRow = std::max(0, row - 1);
   const int adjMaxRow = std::min(mNbRows - 1, row + 1);
   for (int curCol = adjMinCol; curCol <= adjMaxCol; ++curCol)
      {
      for (int curRow = adjMinRow; curRow <= adjMaxRow; ++curRow)
         {
                             // Ignore current cell
         if (curCol == col && curRow == row)
            continue;

         func(mCells[curCol + curRow * mNbCols],
              curCol,
              curRow);
         }
      }
   }

//--------------------------------------------------------------
bool MineSweeperGrid::IsGameOver() const
   {
   for (const MineSweeperCell& cell : mCells)
      {
      if (cell.IsMine && cell.IsRevealed)
         return (true);
      }

   return (false);
   }

//--------------------------------------------------------------
void MineSweeperGrid::PlaceMinesRandomly()
   {
   const int nbCells = mCells.size();
   if (mNbMines <= 0 || nbCells <= 0)
      return;

                             // Use Fisher–Yates shuffle to randomly place mines
   int curId = 0;
   std::vector<int> RemainingVacantCellsIdx(nbCells);
   for (int& elem : RemainingVacantCellsIdx)
      {
      elem = curId++;
      }

   std::random_device rd;
   std::mt19937 RandomEngine(rd());

   const int nbMinesToPlace = std::min(mNbMines, nbCells);
   for (int i = 0; i < nbMinesToPlace; ++i)
      {
      std::uniform_int_distribution<int> randomVacantCellLeft(0, RemainingVacantCellsIdx.size() - 1);

      const int randomRemainingVacantCell = randomVacantCellLeft(RandomEngine);
      std::swap(RemainingVacantCellsIdx[randomRemainingVacantCell], RemainingVacantCellsIdx.back());
      const int mineCellIdx = RemainingVacantCellsIdx.back();
      RemainingVacantCellsIdx.pop_back();

      mCells[mineCellIdx].IsMine = true;

                             // Increase mine count for surrounding cells
      const int col = mineCellIdx % mNbCols;
      const int row = mineCellIdx / mNbCols;
      ForEachAdjacentCell(col,
                          row,
                          [](MineSweeperCell& cell,
                             int              cellCol,
                             int              cellRow)
         {
         cell.NbSurroundingMines++;
         });
      }
   }

//--------------------------------------------------------------
bool MineSweeperGrid::Reset(int nbCols,
                            int nbRows,
                            int nbMines)
   {
   if (nbCols < 1 || nbRows < 1 || nbMines < 1 || nbMines >= (nbCols * nbRows))
      return (false);

   mNbCols = nbCols;
   mNbRows = nbRows;
   mNbMines = nbMines;

                             // Reinitialize cells to default values
   mCells.clear();
   mCells.resize(nbCols * nbRows);

   PlaceMinesRandomly();
   return (true);
   }

//--------------------------------------------------------------
void MineSweeperGrid::Reveal(int col,
                             int row)
   {
   if (col < 0 || row < 0 || col >= mNbCols || row >= mNbRows)
      return;

   MineSweeperCell& cell = mCells[col + row * mNbCols];

                             // Nothing to do if cell is already visible
   if (cell.IsRevealed)
      return;

   cell.IsRevealed = true;

                             // Don't reveal additionnal cells if we revealed a mine
   if (cell.IsMine)
      return;

                             // Flood algorithm to reveal adjacent cells
   ForEachAdjacentCell(col,
                       row,
                       [&](MineSweeperCell& cell,
                           int              cellCol,
                           int              cellRow)
      {
      if (cell.IsMine)
         return;

      if (cell.NbSurroundingMines > 0)
         {
         cell.IsRevealed = true;
         return;
         }

      Reveal(cellCol,
             cellRow);
      });
   }

//--------------------------------------------------------------
void MineSweeperGrid::ToggleFlag(int col,
                                 int row)
   {
   MineSweeperCell& cell = mCells[col + row * mNbCols];
   cell.IsFlagged = !cell.IsFlagged;
   }
