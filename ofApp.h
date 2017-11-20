#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include <algorithm>    // std::fill


class ofApp : public ofBaseApp{

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

		ofxImGui::Gui gui;                           // single entery to ImGUI subsystem
		ofRectangle mainWindowRectangle;
		void drawMainWindow();
		void reset();
		void quit();

		bool isRunning;
		float t;
		bool animate;

		ofVec2f p1, p2;		// particle positions
		ofVec2f v1, v2;		//vel before collision
		ofVec2f u1, u2;		//vel after collision
		ofVec2f d;			//unit vector distance between particles
		float m1, m2, c, time;
		ofVec2f momentum; //vector for momentum

		float closingVel;

		const float T_MIN = -5.0f;
		const float T_MAX = 5.0f;
		const float RANGE = 5.0f;
		const float RADIUS = 0.2;

		ofRectangle demoArea;
};
