// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef QUADTREE_H
#define QUADTREE_H

#include <functional>
#include <memory>
#include <vector>

#include "AABB.h"
#include "Point.h"

class QuadTree
   {
   public:
      QuadTree(const AABB& aabb);

      void ForEachPoint(std::function<void(const Point& point)> funct) const;
      void ForEachQuad(std::function<void(const QuadTree& quadTree)> funct) const;

      bool Insert(const Point& point);
      std::vector<Point> Query(const AABB& aabb) const;

      const AABB& Region() const noexcept { return mAABB; }

   private:
      void QueryInternal(const AABB& aabb,
                         std::vector<Point>& queryResults) const;
      bool Subdivide();

      AABB mAABB;

      constexpr static size_t sMaxCapacity = 4;
      std::vector<Point> mPoints = {};

      std::unique_ptr<QuadTree> mQuadTreeNorthWest = nullptr;
      std::unique_ptr<QuadTree> mQuadTreeNorthEast = nullptr;
      std::unique_ptr<QuadTree> mQuadTreeSouthWest = nullptr;
      std::unique_ptr<QuadTree> mQuadTreeSouthEast = nullptr;
   };

#endif
