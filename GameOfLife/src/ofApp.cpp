// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ofApp.h"

//--------------------------------------------------------------
namespace Constants
   {
   constexpr char* WINDOW_TITLE = "GameOfLife";
   constexpr int NB_FRAMES_PER_SECOND = 30;
   constexpr int UPDATE_EVERY_X_FRAMES = 10;

   constexpr int BOARD_WIDTH = 40;
   constexpr int BOARD_HEIGHT = 40;
   };

ofApp::ofApp()
   : mGameOfLifeWorld(Constants::BOARD_WIDTH,
                      Constants::BOARD_HEIGHT)
   {

   }

//--------------------------------------------------------------
void ofApp::setup() {
   ofSetWindowTitle(Constants::WINDOW_TITLE);
   ofSetFrameRate(Constants::NB_FRAMES_PER_SECOND);
}

//--------------------------------------------------------------
void ofApp::update() {
   if (mIsPaused)
      return;

   static int sCounter = 0;
   if (++sCounter % Constants::UPDATE_EVERY_X_FRAMES == 0)
      mGameOfLifeWorld.Update();    
}

//--------------------------------------------------------------
void ofApp::draw() {
   ofClear(ofColor::grey);

   const int cellUIHeight = ofGetWindowHeight() / mGameOfLifeWorld.NbRows();
   const int cellUIWidth = ofGetWindowWidth() / mGameOfLifeWorld.NbCols();

   ofSetColor(ofColor::black);
   ofSetLineWidth(2.0f);

   for (int i = 0; i <= mGameOfLifeWorld.NbCols(); ++i)
      {
      const int curX = i * cellUIWidth;
      ofDrawLine(curX, 0.0f, curX, ofGetWindowHeight());
      }

   for (int j = 0; j <= mGameOfLifeWorld.NbRows(); ++j)
      {
      const int curY = j * cellUIHeight;
      ofDrawLine(0.0f, curY, ofGetWindowWidth(), curY);
      }

   mGameOfLifeWorld.ForEachAliveCell([cellUIHeight,
                                      cellUIWidth](int cellCol,
                                                   int cellRow) {
         const int cellUITopX = cellCol * cellUIWidth;
         const int cellUITopY = cellRow * cellUIHeight;
         ofDrawRectangle(cellUITopX, cellUITopY, cellUIWidth, cellUIHeight);
      });
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
   mIsPaused = !mIsPaused;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
   processMouseEvent(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
   processMouseEvent(x, y, button);
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

//--------------------------------------------------------------
void ofApp::processMouseEvent(int x, int y, int button) {

   const int cellUIHeight = ofGetWindowHeight() / mGameOfLifeWorld.NbRows();
   const int cellUIWidth = ofGetWindowWidth() / mGameOfLifeWorld.NbCols();

   const int col = x / cellUIWidth;
   const int row = y / cellUIHeight;

   constexpr int LEFT_CLICK = 0;
   constexpr int RIGHT_CLICK = 2;
   switch (button)
      {
         case LEFT_CLICK:
            {
            mGameOfLifeWorld.Animate(col, row);
            break;
            }
         case RIGHT_CLICK:
            {
            mGameOfLifeWorld.Kill(col, row);
            break;
            }
      }
   }
