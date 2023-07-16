// Copyright (c) 2023 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"

#include "ofImage.h"

#include <random>
#include <vector>

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
private:

	enum class Button {
		NONE,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

	int BoardLength() const;
	Button HoveredButton(int x, int y) const;

	void CheckAnswer(Button Answer);
	void GameOver();
	void Next();

	const ofColor OFCOLOR_LIGHT_TOP_RIGHT = ofColor::blue;
	const ofColor OFCOLOR_LIGHT_BOTTOM_RIGHT = ofColor::green;
	const ofColor OFCOLOR_LIGHT_BOTTOM_LEFT = ofColor::red;
	const ofColor OFCOLOR_LIGHT_TOP_LEFT = ofColor::yellow;

	static constexpr float OFCOLOR_DARK_MULTIPLIER = 0.70f;

	const ofColor OFCOLOR_DARK_TOP_RIGHT = OFCOLOR_LIGHT_TOP_RIGHT * OFCOLOR_DARK_MULTIPLIER;
	const ofColor OFCOLOR_DARK_BOTTOM_RIGHT = OFCOLOR_LIGHT_BOTTOM_RIGHT * OFCOLOR_DARK_MULTIPLIER;
	const ofColor OFCOLOR_DARK_BOTTOM_LEFT = OFCOLOR_LIGHT_BOTTOM_LEFT * OFCOLOR_DARK_MULTIPLIER;
	const ofColor OFCOLOR_DARK_TOP_LEFT = OFCOLOR_LIGHT_TOP_LEFT * OFCOLOR_DARK_MULTIPLIER;

	ofTrueTypeFont mFont;
	ofImage mImage;
	Button mActiveButton = Button::NONE;
	Button mHoveredButton = Button::NONE;
	std::vector<Button> mSequence;
	int mBestScore = 0;
	int mCurAnswerIdx = 0;
	bool mIsShowingSequence = false;

	std::mt19937 mRandomGenerator{ std::random_device{}() };
	std::uniform_int_distribution<int> mRandomDistribution{ 0, 3 };
};

#endif
