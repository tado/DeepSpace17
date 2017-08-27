#include "ofApp.h"

void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofEnableSmoothing();
	glEnable(GL_POINT_SMOOTH);

	//window loc
	ofSetWindowPosition(0, 40);

	//OSC
	oscSender = new OSCSender();

	//View
	skeletonView = new SkeletonView();

	//GUI
	gui.setup();
	gui.add(useLocal.setup("Use Localhost", true));
	gui.loadFromFile("settings.xml");
	showGui = false;
}

void ofApp::update() {
	oscSender->update();
}

void ofApp::draw() {
	skeletonView->draw();
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
