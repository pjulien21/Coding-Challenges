// Copyright (c) 2023 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#include "ofApp.h"

namespace Constants
{
   constexpr char* WINDOW_TITLE = "SimonSays";
   constexpr int NB_FRAMES_PER_SECOND = 30;
   constexpr char* IMAGE_PATH = "img\\Square-shape.png";

   // Animation Timing
   constexpr float TimeOffInSeconds = 0.5f;
   constexpr float TimeOnInSeconds = 1.0f;
   constexpr float TimePeriodInSeconds = (TimeOffInSeconds + TimeOnInSeconds);
};

//--------------------------------------------------------------
void ofApp::setup() {
   ofSetWindowTitle(Constants::WINDOW_TITLE);
   ofSetFrameRate(Constants::NB_FRAMES_PER_SECOND);

   mFont.load("verdana.ttf", 32);
   mImage.load(Constants::IMAGE_PATH);
}

//--------------------------------------------------------------
void ofApp::update() {
   // Update animation
   if (not mIsShowingSequence)
      return;

   const float ElapsedTimeInSeconds = ofGetElapsedTimef();
   const int curSequenceIdx = static_cast<int>(ElapsedTimeInSeconds / Constants::TimePeriodInSeconds);
   if (curSequenceIdx >= mSequence.size())
      {
      mActiveButton = mHoveredButton;
      mIsShowingSequence = false;
      return;
      }

   const float CurPeriodTimeInSeconds = ElapsedTimeInSeconds - (curSequenceIdx * Constants::TimePeriodInSeconds);
   const bool isOnAnimation = (CurPeriodTimeInSeconds > Constants::TimeOffInSeconds);
   mActiveButton = (isOnAnimation) ? mSequence[curSequenceIdx] : Button::NONE;
}

//--------------------------------------------------------------
void ofApp::draw() {
   ofClear(ofColor::cadetBlue);

   const int boardLength = BoardLength();
   const int boardHalfLength = boardLength / 2;

   ofSetColor(ofColor::black);
   mImage.draw(ofGetWindowWidth() / 2 - boardHalfLength,
               ofGetWindowHeight() / 2 - boardHalfLength, 
               boardLength,
               boardLength);

   const int buttonLength = boardLength * 0.4;
   const float hoveredButtonFactor = 1.04f;

   // TOP LEFT
   const ofColor OFCOLOR_TOP_LEFT = (mActiveButton == Button::TOP_LEFT and not mSequence.empty()) ?
                                    OFCOLOR_LIGHT_TOP_LEFT :
                                    OFCOLOR_DARK_TOP_LEFT;
   const int buttonLength_top_left = (mActiveButton == Button::TOP_LEFT) ?
                                     buttonLength * hoveredButtonFactor :
                                     buttonLength;
   ofSetColor(OFCOLOR_TOP_LEFT);
   mImage.draw(ofGetWindowWidth() / 2 - buttonLength_top_left,
               ofGetWindowHeight() / 2 - buttonLength_top_left,
               buttonLength_top_left,
               buttonLength_top_left);

   // TOP RIGHT
   const ofColor OFCOLOR_TOP_RIGHT = (mActiveButton == Button::TOP_RIGHT and not mSequence.empty()) ?
                                     OFCOLOR_LIGHT_TOP_RIGHT :
                                     OFCOLOR_DARK_TOP_RIGHT;
   const int buttonLength_top_right = (mActiveButton == Button::TOP_RIGHT) ?
                                      buttonLength * hoveredButtonFactor :
                                      buttonLength;
   ofSetColor(OFCOLOR_TOP_RIGHT);
   mImage.draw(ofGetWindowWidth() / 2,
               ofGetWindowHeight() / 2 - buttonLength_top_right,
               buttonLength_top_right,
               buttonLength_top_right);

   // BOTTOM LEFT
   const ofColor OFCOLOR_BOTTOM_LEFT = (mActiveButton == Button::BOTTOM_LEFT and not mSequence.empty()) ?
                                       OFCOLOR_LIGHT_BOTTOM_LEFT :
                                       OFCOLOR_DARK_BOTTOM_LEFT;
   const int buttonLength_bottom_left = (mActiveButton == Button::BOTTOM_LEFT) ?
                                        buttonLength * hoveredButtonFactor :
                                        buttonLength;
   ofSetColor(OFCOLOR_BOTTOM_LEFT);
   mImage.draw(ofGetWindowWidth() / 2 - buttonLength_bottom_left,
               ofGetWindowHeight() / 2,
               buttonLength_bottom_left,
               buttonLength_bottom_left);

   // BOTTOM RIGHT
   const ofColor OFCOLOR_BOTTOM_RIGHT = (mActiveButton == Button::BOTTOM_RIGHT and not mSequence.empty()) ?
                                        OFCOLOR_LIGHT_BOTTOM_RIGHT :
                                        OFCOLOR_DARK_BOTTOM_RIGHT;
   const int buttonLength_bottom_right = (mActiveButton == Button::BOTTOM_RIGHT) ?
                                         buttonLength * hoveredButtonFactor :
                                         buttonLength;
   ofSetColor(OFCOLOR_BOTTOM_RIGHT);
   mImage.draw(ofGetWindowWidth() / 2,
               ofGetWindowHeight() / 2,
               buttonLength_bottom_right,
               buttonLength_bottom_right);

   // Scoreboard
   std::string mScoreText{ "Score: " };
   if (mSequence.empty())
      mScoreText += "-";
   else
      mScoreText += std::to_string(mSequence.size() - 1);

   mScoreText += "\nBest:  ";
   if (mBestScore == 0)
      mScoreText += "-";
   else
      mScoreText += std::to_string(mBestScore);

   ofSetColor(ofColor::black);
   mFont.drawString(mScoreText, 25, 50);

   if (mSequence.empty())
      mFont.drawString("Click to start", ofGetWindowWidth() / 2 - 150, ofGetWindowHeight() - 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
   mHoveredButton = HoveredButton(x, y);
   if (not mIsShowingSequence)
      mActiveButton = mHoveredButton;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

   if (mIsShowingSequence) // Animating
      return;

   if (mSequence.empty()) // Start game
      {
      Next();
      return;
      }

   CheckAnswer(mHoveredButton);
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
int ofApp::BoardLength() const
{
   return std::min(ofGetWindowWidth(), ofGetWindowHeight()) * 0.75;
}

//--------------------------------------------------------------
ofApp::Button ofApp::HoveredButton(int x, int y) const
{
   const int boardLength = BoardLength();

   if (x < (ofGetWindowWidth() - boardLength) / 2  or x > (ofGetWindowWidth() - boardLength) / 2 + boardLength or
       y < (ofGetWindowHeight() - boardLength) / 2 or y > (ofGetWindowHeight() - boardLength) / 2 + boardLength)
      return Button::NONE;

   if (x <= ofGetWindowWidth() / 2)
      return (y <= ofGetWindowHeight() / 2) ? Button::TOP_LEFT : Button::BOTTOM_LEFT;
   
   return (y <= ofGetWindowHeight() / 2) ? Button::TOP_RIGHT : Button::BOTTOM_RIGHT;
}

//--------------------------------------------------------------
void ofApp::CheckAnswer(Button Answer)
{
   if (Answer == Button::NONE)
      return;

   // Wrong answer
   if (mCurAnswerIdx >= mSequence.size() or
       Answer != mSequence[mCurAnswerIdx])
      {
      GameOver();
      return;
      }

   // Full correct answer, add next button
   if (mCurAnswerIdx == mSequence.size() - 1)
      {
      if (mSequence.size() > mBestScore) // Keep track of best score
         mBestScore = mSequence.size();

      Next();
      return;
      }

   // Partial correct answer, awaiting next answer
   ++mCurAnswerIdx;
}

//--------------------------------------------------------------
void ofApp::GameOver()
{
   mSequence.clear();
}

//--------------------------------------------------------------
void ofApp::Next()
{
   constexpr static Button allButtons[4] = { Button::TOP_LEFT,
                                             Button::TOP_RIGHT,
                                             Button::BOTTOM_LEFT,
                                             Button::BOTTOM_RIGHT };

   const Button randomButton = allButtons[mRandomDistribution(mRandomGenerator)];
   mSequence.emplace_back(randomButton);

   mCurAnswerIdx = 0;
   mIsShowingSequence = true;
   ofResetElapsedTimeCounter();
}
