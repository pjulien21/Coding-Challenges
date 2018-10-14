// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ofApp.h"

//--------------------------------------------------------------
namespace Constants
{
	constexpr char* WINDOW_TITLE = "MazeGeneration";
	constexpr int NB_FRAMES_PER_SECOND = 20;

	constexpr int MAZE_WIDTH = 24;
	constexpr int MAZE_HEIGHT = 24;
};

ofApp::ofApp()
   : mMazeBuilder(Constants::MAZE_WIDTH,
                  Constants::MAZE_HEIGHT)
   {

   }

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle(Constants::WINDOW_TITLE);
	ofSetFrameRate(Constants::NB_FRAMES_PER_SECOND);
}

//--------------------------------------------------------------
void ofApp::update() {
   mMazeBuilder.NextBuildStep();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofClear(ofColor::grey);

   const int cellUIHeight = ofGetWindowHeight() / Constants::MAZE_HEIGHT;
   const int cellUIWidth = ofGetWindowWidth() / Constants::MAZE_WIDTH;

   auto currentCell = mMazeBuilder.CurrentCell();

   const Maze& maze = mMazeBuilder.GetMaze();
   maze.ForEachCell([cellUIHeight,
                     cellUIWidth,
                     currentCell](const MazeCell& cell,
                                        int        cellCol,
                                        int        cellRow) {
      const int cellUITopX = cellCol * cellUIWidth;
      const int cellUITopY = cellRow * cellUIHeight;

      if (cellCol == currentCell.col &&
          cellRow == currentCell.row)
         {
         ofFill();
         ofSetColor(ofColor::lightGrey);
         ofDrawRectangle(cellUITopX, cellUITopY, cellUIWidth, cellUIHeight);
         }

      ofSetColor(ofColor::black);
      ofSetLineWidth(2.0f);
      
      if (cell.HasNorthWall)
         ofDrawLine(cellUITopX, cellUITopY, cellUITopX + cellUIWidth, cellUITopY);
 
      if (cell.HasEastWall)
         ofDrawLine(cellUITopX + cellUIWidth, cellUITopY, cellUITopX + cellUIWidth, cellUITopY + cellUIHeight);

      if (cell.HasSouthWall)
         ofDrawLine(cellUITopX, cellUITopY + cellUIHeight, cellUITopX + cellUIWidth, cellUITopY + cellUIHeight);

      if (cell.HasWestWall)
         ofDrawLine(cellUITopX, cellUITopY, cellUITopX, cellUITopY + cellUIHeight);
      });
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
   
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

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
