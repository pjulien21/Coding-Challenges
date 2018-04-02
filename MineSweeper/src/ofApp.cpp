// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ofApp.h"

//--------------------------------------------------------------
namespace Constants
   {
   constexpr char* WINDOW_TITLE = "MineSweeper";
   constexpr int NB_FRAMES_PER_SECOND = 30;

   constexpr int GRID_WIDTH = 16;
   constexpr int GRID_HEIGHT = 16;
   constexpr int MINES_COUNT = 40;

   const char* IMG_DIGIT1_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\1.png";
   const char* IMG_DIGIT2_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\2.png";
   const char* IMG_DIGIT3_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\3.png";
   const char* IMG_DIGIT4_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\4.png";
   const char* IMG_DIGIT5_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\5.png";
   const char* IMG_DIGIT6_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\6.png";
   const char* IMG_DIGIT7_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\7.png";
   const char* IMG_DIGIT8_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\8.png";
   const char* IMG_FLAG_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\flag.png";
   const char* IMG_MINE_PATH = "C:\\Users\\Phil\\Desktop\\Solutions\\VisualStudio\\Github\\MineSweeper\\img\\mine.png";
   };

//--------------------------------------------------------------
namespace _ofApp
   {
   GLuint CreateGLTextureFromImage(const char* imgPath);
   };

//--------------------------------------------------------------
ofApp::ofApp()
   : mGrid(Constants::GRID_WIDTH,
           Constants::GRID_HEIGHT,
           Constants::MINES_COUNT)
   {

   }

//--------------------------------------------------------------
void ofApp::setup() {
   ofSetWindowTitle(Constants::WINDOW_TITLE);
   ofSetFrameRate(Constants::NB_FRAMES_PER_SECOND);

   mGLTextureDigit1 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT1_PATH);
   mGLTextureDigit2 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT2_PATH);
   mGLTextureDigit3 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT3_PATH);
   mGLTextureDigit4 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT4_PATH);
   mGLTextureDigit5 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT5_PATH);
   mGLTextureDigit6 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT6_PATH);
   mGLTextureDigit7 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT7_PATH);
   mGLTextureDigit8 = _ofApp::CreateGLTextureFromImage(Constants::IMG_DIGIT8_PATH);
   mGLTextureFlag = _ofApp::CreateGLTextureFromImage(Constants::IMG_FLAG_PATH);
   mGLTextureMine = _ofApp::CreateGLTextureFromImage(Constants::IMG_MINE_PATH);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
                             // Clear background with unrevealed cells color
   ofClear(ofColor::grey);

   const float cellsHeight = ofGetWindowHeight() / static_cast<float>(mGrid.NbRows());
   const float cellsWidth = ofGetWindowWidth() / static_cast<float>(mGrid.NbCols());

                             // Draw cells background
   ofFill();
   mGrid.ForEachCell([&](const MineSweeperCell& cell, int cellCol, int cellRow)
      {
      const float cellX = 0.0f + cellCol * cellsWidth;
      const float cellY = 0.0f + cellRow * cellsHeight;

      if (cell.IsRevealed)
         {
         if (cell.IsMine)
            ofSetColor(ofColor::red);
         else
            ofSetColor(ofColor::darkGray);

         ofDrawRectangle(cellX,
                         cellY,
                         cellsWidth,
                         cellsHeight);
         }
      });


                             // Draw characters from textures
   glEnable(GL_TEXTURE_2D);

   mGrid.ForEachCell([&](const MineSweeperCell& cell, int cellCol, int cellRow)
      {
      ofColor color = ofColor::blue;
      GLuint textureId = 0;
      if (!GetGLTextureToDisplay(cell, textureId, color))
         return;
         
      const float cellX = 0.0f + cellCol * cellsWidth;
      const float cellY = 0.0f + cellRow * cellsHeight;

      ofSetColor(color);
      glBindTexture(GL_TEXTURE_2D, textureId);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      glBegin(GL_QUADS);
         glTexCoord2f(0, 0); glVertex3f(cellX, cellY, 0);
         glTexCoord2f(0, 1); glVertex3f(cellX, cellY + cellsHeight, 0);
         glTexCoord2f(1, 1); glVertex3f(cellX + cellsWidth, cellY + cellsHeight, 0);
         glTexCoord2f(1, 0); glVertex3f(cellX + cellsWidth, cellY, 0);
      glEnd();
      });

   glDisable(GL_TEXTURE_2D);

                             // Draw grid
   ofSetColor(ofColor::black);

                             // 1) Vertical lines
   const int nbCols = mGrid.NbCols();
   for (int i = 0; i <= nbCols; ++i)
      {
      const float curX = i * cellsWidth;
      ofDrawLine(curX, 0.0f,
                 curX, ofGetWindowHeight());
      }

                             // 2) Horizontal lines
   const int nbRows = mGrid.NbRows();
   for (int i = 0; i <= nbRows; ++i)
      {
      const float curY = i * cellsHeight;
      ofDrawLine(0.0f, curY,
                 ofGetWindowWidth(), curY);
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

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

   if (mGrid.IsGameOver())
      {
                             // Start a new game
      mGrid.Reset(Constants::GRID_WIDTH,
                  Constants::GRID_HEIGHT,
                  Constants::MINES_COUNT);
      return;
      }

   constexpr int LEFT_CLICK = 0;
   constexpr int RIGHT_CLICK = 2;

   const int gridCol = x / (ofGetWindowWidth() / mGrid.NbCols());
   const int gridRow = y / (ofGetWindowHeight() / mGrid.NbRows());
   switch (button)
      {
      case LEFT_CLICK:
         {
         mGrid.Reveal(gridCol, gridRow);
         break;
         }
      case RIGHT_CLICK:
         {
         mGrid.ToggleFlag(gridCol, gridRow);
         break;
         }
      default:
         break;
      }
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
bool ofApp::GetGLTextureToDisplay(const MineSweeperCell& cell,
                                        GLuint&          glTextureId,
                                        ofColor&         color)
   {
   color = ofColor::white;
   glTextureId = 0;

   if (cell.IsRevealed)
      {
      if (cell.IsMine)
         {
         color = ofColor::white;
         glTextureId = mGLTextureMine;
         return (true);
         }

      if (cell.NbSurroundingMines <= 0)
         return (false);
  
      color = ofColor::blue;
      switch (cell.NbSurroundingMines)
         {
         case 1: { glTextureId = mGLTextureDigit1; break; }
         case 2: { glTextureId = mGLTextureDigit2; break; }
         case 3: { glTextureId = mGLTextureDigit3; break; }
         case 4: { glTextureId = mGLTextureDigit4; break; }
         case 5: { glTextureId = mGLTextureDigit5; break; }
         case 6: { glTextureId = mGLTextureDigit6; break; }
         case 7: { glTextureId = mGLTextureDigit7; break; }
         case 8: { glTextureId = mGLTextureDigit8; break; }
         default: break;
         }
      return (true);
      }
   else if (cell.IsFlagged)
      {
      color = ofColor::yellow;
      glTextureId = mGLTextureFlag;
      return (true);
      }

   return (false);
   }

//--------------------------------------------------------------
GLuint _ofApp::CreateGLTextureFromImage(const char* imgPath)
   {
   GLuint GLTextureId;
   glGenTextures(1, &GLTextureId);

   ofPixels imgPixels;
   ofLoadImage(imgPixels, imgPath);

   glBindTexture(GL_TEXTURE_2D, GLTextureId);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgPixels.getWidth(), imgPixels.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imgPixels.getData());
   
   return (GLTextureId);
   }