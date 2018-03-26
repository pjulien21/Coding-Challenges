// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "QuadTree.h"

using namespace std;

QuadTree::QuadTree(const AABB& aabb)
   : mAABB(aabb)
   {

   }

void QuadTree::ForEachPoint(function<void(const Point& point)> funct) const
   {
   for (const Point& point : mPoints)
      funct(point);

   if (mQuadTreeNorthWest != nullptr) mQuadTreeNorthWest->ForEachPoint(funct);
   if (mQuadTreeNorthEast != nullptr) mQuadTreeNorthEast->ForEachPoint(funct);
   if (mQuadTreeSouthWest != nullptr) mQuadTreeSouthWest->ForEachPoint(funct);
   if (mQuadTreeSouthEast != nullptr) mQuadTreeSouthEast->ForEachPoint(funct);
   }

void QuadTree::ForEachQuad(std::function<void(const QuadTree& quadTree)> funct) const
   {
   funct(*this);

   if (mQuadTreeNorthWest != nullptr) mQuadTreeNorthWest->ForEachQuad(funct);
   if (mQuadTreeNorthEast != nullptr) mQuadTreeNorthEast->ForEachQuad(funct);
   if (mQuadTreeSouthWest != nullptr) mQuadTreeSouthWest->ForEachQuad(funct);
   if (mQuadTreeSouthEast != nullptr) mQuadTreeSouthEast->ForEachQuad(funct);
   }

bool QuadTree::Insert(const Point& point)
   {
   if (!mAABB.Contains(point))
      return (false);

   if (mPoints.size() < sMaxCapacity)
      {
      mPoints.push_back(point);
      return (true);
      }

   Subdivide();

   if (mQuadTreeNorthWest != nullptr &&
       mQuadTreeNorthWest->Insert(point))
      return (true);

   if (mQuadTreeNorthEast != nullptr &&
       mQuadTreeNorthEast->Insert(point))
      return (true);

   if (mQuadTreeSouthWest != nullptr &&
       mQuadTreeSouthWest->Insert(point))
      return (true);

   if (mQuadTreeSouthEast != nullptr &&
       mQuadTreeSouthEast->Insert(point))
      return (true);

   return (false);
   }

bool QuadTree::Subdivide()
   {
   if (mQuadTreeNorthWest != nullptr ||
       mQuadTreeNorthEast != nullptr ||
       mQuadTreeSouthWest != nullptr ||
       mQuadTreeSouthEast != nullptr)
      return (false);

   const float subdivideHeight = mAABB.Height() / 2.0f;
   const float subdivideWidth = mAABB.Width() / 2.0f;

   const float leftX = mAABB.TopLeft().x;
   const float topY = mAABB.TopLeft().y;
   const float middleX = leftX + subdivideWidth;
   const float middleY = topY + subdivideHeight;

   const AABB AABBNorthWest = { Point(leftX, topY), subdivideWidth, subdivideHeight };
   const AABB AABBNorthEast = { Point(middleX, topY), subdivideWidth, subdivideHeight };
   const AABB AABBSouthWest = { Point(leftX, middleY), subdivideWidth, subdivideHeight };
   const AABB AABBSouthEast = { Point(middleX, middleY), subdivideWidth, subdivideHeight };

   mQuadTreeNorthWest.reset(new QuadTree(AABBNorthWest));
   mQuadTreeNorthEast.reset(new QuadTree(AABBNorthEast));
   mQuadTreeSouthWest.reset(new QuadTree(AABBSouthWest));
   mQuadTreeSouthEast.reset(new QuadTree(AABBSouthEast));

   return (true);
   }

vector<Point> QuadTree::Query(const AABB& aabb) const
   {
   vector<Point> Points = {};
   QueryInternal(aabb, Points);
   return (Points);
   }

void QuadTree::QueryInternal(const AABB& aabb,
                             std::vector<Point>& queryResults) const
   {
   if (!mAABB.Overlaps(aabb))
      return;

   for (const Point& point : mPoints)
      {
      if (aabb.Contains(point))
         queryResults.push_back(point);
      }

   if (mQuadTreeNorthWest != nullptr) mQuadTreeNorthWest->QueryInternal(aabb, queryResults);
   if (mQuadTreeNorthEast != nullptr) mQuadTreeNorthEast->QueryInternal(aabb, queryResults);
   if (mQuadTreeSouthWest != nullptr) mQuadTreeSouthWest->QueryInternal(aabb, queryResults);
   if (mQuadTreeSouthEast != nullptr) mQuadTreeSouthEast->QueryInternal(aabb, queryResults);
   }
