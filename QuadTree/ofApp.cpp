// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ofApp.h"

#include <random>

using namespace std;

namespace Constants
   {
   constexpr char* WINDOW_TITLE = "QuadTree";
   constexpr int NB_FRAMES_PER_SECOND = 30;
   constexpr int NB_POINTS = 5000;
   constexpr float POINT_SIZE = 2.0f;
   };

//--------------------------------------------------------------
void ofApp::setup() {
   ofSetWindowTitle(Constants::WINDOW_TITLE);
   ofSetFrameRate(Constants::NB_FRAMES_PER_SECOND);

   std::random_device rd;
   mt19937 RandomEngine(rd());

   uniform_real_distribution<float> randomX(0.0f, ofGetWindowWidth());
   uniform_real_distribution<float> randomY(0.0f, ofGetWindowHeight());

   for (int i = 0; i < Constants::NB_POINTS; ++i)
      {
      mQuadTree.Insert(Point(randomX(RandomEngine), 
                             randomY(RandomEngine)));
      }
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
   ofClear(ofColor::black);

   // Draw quads
   ofNoFill();
   ofSetColor(ofColor::cyan);
   mQuadTree.ForEachQuad([](const QuadTree& quadTree)
      {
      ofDrawRectangle(ofPoint(quadTree.Region().TopLeft().x,
                              quadTree.Region().TopLeft().y), 
                      quadTree.Region().Width(),
                      quadTree.Region().Height());
      }
   );

   // Draw points
   ofFill();
   ofSetColor(ofColor::white);
   mQuadTree.ForEachPoint([](const Point& point)
      {
      ofDrawCircle(ofPoint(point.x, point.y), Constants::POINT_SIZE);
      }
   );

   // Draw query AABB
   ofNoFill();
   ofSetColor(ofColor::green);
   const Point QueryAABBTopLeft = mQueryAABB.TopLeft();
   ofDrawRectangle(ofPoint(QueryAABBTopLeft.x, QueryAABBTopLeft.y),
                   mQueryAABB.Width(),
                   mQueryAABB.Height());

   // Highlight points within query AABB (redraw over)
   ofFill();
   const vector<Point> queryPoints = mQuadTree.Query(mQueryAABB);
   for (const Point& point : queryPoints)
      {
      ofDrawCircle(ofPoint(point.x, point.y), Constants::POINT_SIZE);
      }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
   mQueryAABB = AABB(Point(ofGetMouseX() - QUERY_AABB_WIDTH / 2.0f,
                           ofGetMouseY() - QUERY_AABB_HEIGHT / 2.0f),
                     QUERY_AABB_WIDTH,
                     QUERY_AABB_HEIGHT);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) { 

}
