#include "ofApp.h"

void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofEnableSmoothing();
	glEnable(GL_POINT_SMOOTH);
	ofHideCursor();

	//window loc
	//ofSetWindowPosition(0, 40);

	//GUI
	gui.setup();
	gui.add(useLocal.setup("Use Localhost", true));
	gui.loadFromFile("settings.xml");
	showGui = false;

	//object controller
	objectController = new ObjectController();

	//View
	skeletonView = new SkeletonView();
	drawCode = new DrawCode();

	//OSC
	oscSender = new OSCSender();
}

void ofApp::update() {
	oscSender->update();
}

void ofApp::draw() {
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	skeletonView->draw();
	drawCode->draw();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	if (showGui){
		gui.draw();
	}
}

void ofApp::keyReleased(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
	if (key == 'g'){
		if (showGui){
			showGui = false;
		} else {
			showGui = true;
		}
	}
}
