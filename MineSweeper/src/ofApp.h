// Copyright (c) 2018 Philippe Julien
// Email    : pjulien21@gmail.com
// LinkedIn : https://www.linkedin.com/in/philippe-julien-a80b2442/
// License  : MIT
//            https://opensource.org/licenses/MIT

#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"

#include "MineSweeperGrid.h"

class ofApp : public ofBaseApp{

	public:
      ofApp();

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
      bool GetGLTextureToDisplay(const MineSweeperCell& cell,
                                       GLuint&          glTextureId,
                                       ofColor&         color);

      MineSweeperGrid mGrid;

      GLuint mGLTextureDigit1;
      GLuint mGLTextureDigit2;
      GLuint mGLTextureDigit3;
      GLuint mGLTextureDigit4;
      GLuint mGLTextureDigit5;
      GLuint mGLTextureDigit6;
      GLuint mGLTextureDigit7;
      GLuint mGLTextureDigit8;
      GLuint mGLTextureFlag;
      GLuint mGLTextureMine;
};

#endif