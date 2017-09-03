#pragma once

#include "ofMain.h"
#include "OSCSender.h"
#include "ObjectController.h"
#include "SkeletonView.h"
#include "DrawCode.h"
#include "ofxGui.h"

class ofApp : public ofSimpleApp {
public:
	void setup();
	void update();
	void draw();
	void keyReleased(int key);

	OSCSender *oscSender;
	ObjectController *objectController;
	SkeletonView *skeletonView;
	DrawCode *drawCode;
	ofxPanel gui;
	ofxToggle useLocal;
	bool showGui;
};
