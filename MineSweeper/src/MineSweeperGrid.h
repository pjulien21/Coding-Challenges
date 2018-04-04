// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef MINESWEEPERGRID_H
#define MINESWEEPERGRID_H

#include <functional>
#include <vector>

struct MineSweeperCell
   {
   bool IsFlagged = false;
   bool IsMine = false;
   bool IsRevealed = false;
   short NbSurroundingMines = 0; // 0 to 8
   };

class MineSweeperGrid
   {
   public:
      MineSweeperGrid(int nbCols,
                      int nbRows,
                      int nbMines);

      bool IsGameOver() const;

      int NbCols() const noexcept { return mNbCols; }
      int NbRows() const noexcept { return mNbRows; }

      bool Reset(int nbCols,
                 int nbRows,
                 int nbMines);

      void Reveal(int col,
                  int row);

      void ToggleFlag(int col,
                      int row);

      void ForEachCell(std::function<void(const MineSweeperCell& cell,
                                                int              cellCol,
                                                int              cellRow)> func) const;

   private:
      void ForEachAdjacentCell(int col,
                               int row,
                               std::function<void(MineSweeperCell& cell,
                                                  int              cellCol,
                                                  int              cellRow)> func);

      void PlaceMinesRandomly();

      int mNbCols;
      int mNbRows;
      int mNbMines;
      std::vector<MineSweeperCell> mCells;
   };

#endif
