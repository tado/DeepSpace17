#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

class OSCReceiver {
public:
	OSCReceiver();
	void update();
	void draw();

	ofxOscReceiver receiver;
	int objectNum;
	vector<ofVec2f> objectLoc;
};

