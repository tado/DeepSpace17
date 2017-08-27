#pragma once

#include "ofMain.h"
#include "OSCSender.h"

class ofApp : public ofSimpleApp {
public:
	void setup();
	void update();
	void draw();
	void keyReleased(int key);

	OSCSender *oscSender;
};
