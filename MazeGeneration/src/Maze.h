// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef MAZE_H
#define MAZE_H

#include <functional>
#include <vector>

enum class Direction
   {
   North,
   East,
   South,
   West
   };

struct MazeCell
   {
   bool HasNorthWall = true;
   bool HasEastWall = true;
   bool HasSouthWall = true;
   bool HasWestWall = true;
   };

class Maze
   {
   public:
      Maze(int nbCols,
           int nbRows);

      int NbCols() const noexcept;
      int NbRows() const noexcept;

      void RemoveWall(int col,
                      int row,
                      Direction direction);

      void ForEachCell(std::function<void(const MazeCell& cell,
                                                int       cellCol,
                                                int       cellRow)> func) const;

   private:
      MazeCell* AdjacentCell(int col,
                             int row,
                             Direction direction);
      MazeCell* CellAt(int col,
                       int row);

      int mNbCols;
      int mNbRows;

      std::vector<MazeCell> mCells;
   };

#endif