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
}

void ofApp::update() {
	oscSender->update();
}

void ofApp::draw() {
	float circleSize = ofGetWidth() / 40.0;
	ofSetColor(255);
	ofSetCircleResolution(64);
	ofNoFill();
	ofSetLineWidth(4);
	
	//draw circle  
	for (auto it = oscSender->cursorList.begin(); it != oscSender->cursorList.end(); it++) {
		ofxTuioCursor *blob = (*it);
		ofDrawCircle(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), circleSize);
	}
	for (auto it = oscSender->objectList.begin(); it != oscSender->objectList.end(); it++) {
		ofxTuioObject *blob = (*it);
		ofDrawCircle(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), circleSize);
	}

	//draw lines
	ofSetLineWidth(3);
	for (auto i = oscSender->cursorList.begin(); i != oscSender->cursorList.end(); i++) {
		for (auto j = i; j != oscSender->cursorList.end(); j++) {
			ofxTuioCursor *blobi = (*i);
			ofxTuioCursor *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			float dist = begin.distance(end);
			ofSetColor(255, ofMap(dist, 0, ofGetWidth() / 2, 191, 0));
			ofDrawLine(begin.x, begin.y, end.x, end.y);
		}
	}
	for (auto i = oscSender->objectList.begin(); i != oscSender->objectList.end(); i++) {
		for (auto j = i; j != oscSender->objectList.end(); j++) {
			ofxTuioObject *blobi = (*i);
			ofxTuioObject *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			float dist = begin.distance(end);
			ofSetColor(255, ofMap(dist, 0, ofGetWidth() / 2, 191, 0));
			ofDrawLine(begin.x, begin.y, end.x, end.y);
		}
	}
	ofSetLineWidth(1);
	ofFill();
}

void ofApp::keyReleased(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
}



