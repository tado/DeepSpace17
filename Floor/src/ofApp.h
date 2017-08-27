#pragma once

#include "ofMain.h"
#include "OSCSender.h"
#include "SkeletonView.h"
#include "ofxGui.h"

class ofApp : public ofSimpleApp {
public:
	void setup();
	void update();
	void draw();
	void keyReleased(int key);

	OSCSender *oscSender;
	SkeletonView *skeletonView;
	ofxPanel gui;
	ofxToggle useLocal;
	bool showGui;
};
