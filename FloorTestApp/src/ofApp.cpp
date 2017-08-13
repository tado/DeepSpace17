#include "ofApp.h"

void ofApp::setup() {
    //OSC to wall
	//sender.setup("192.168.19.190", 20000);
	sender.setup("127.0.0.1", 20000);

    //TUIO
	ofAddListener(tuio.objectAdded, this, &ofApp::objectAdded);
	ofAddListener(tuio.objectRemoved, this, &ofApp::objectRemoved);
	ofAddListener(tuio.objectUpdated, this, &ofApp::objectUpdated);
	ofAddListener(tuio.cursorAdded, this, &ofApp::tuioAdded);
	ofAddListener(tuio.cursorRemoved, this, &ofApp::tuioRemoved);
	ofAddListener(tuio.cursorUpdated, this, &ofApp::tuioUpdated);
	ofSetFrameRate(60);
	ofBackground(0);
	ofEnableSmoothing();
	glEnable(GL_POINT_SMOOTH);
	ofHideCursor();
	tuio.start(3333);
	log = "";
}

void ofApp::update() {
	tuio.getMessage();
}

void ofApp::draw() {
	//list<ofxTuioObject*> objectList = tuio.getTuioObjects();
	list<ofxTuioCursor*> cursorList = tuio.getTuioCursors();
	float circleSize = ofGetWidth() / 40.0;
	ofSetColor(255);
	ofSetCircleResolution(64);
	ofNoFill();
	ofSetLineWidth(4);

    //send OSC message
    ofxOscMessage mn;
    mn.setAddress("/floor/objectNum");
    mn.addIntArg(cursorList.size());
    sender.sendMessage(mn, false);
    ofxOscMessage ml;
    ml.setAddress("/floor/objectLoc");
    for (auto it = cursorList.begin(); it != cursorList.end(); it++) {
		ofxTuioCursor *blob = (*it);
        ofDrawCircle(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), circleSize);
        ml.addFloatArg(blob->getX());
        ml.addFloatArg(blob->getY());
    }
    sender.sendMessage(ml, false);

	//draw circle  
	for (auto it = cursorList.begin(); it != cursorList.end(); it++) {
		ofxTuioCursor *blob = (*it);
		ofDrawCircle(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), circleSize);
	}

	//draw lines
	ofSetLineWidth(3);
	for (auto i = cursorList.begin(); i != cursorList.end(); i++) {
		for (auto j = i; j != cursorList.end(); j++) {
			ofxTuioCursor *blobi = (*i);
			ofxTuioCursor *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			float dist = begin.distance(end);
			ofSetColor(255, ofMap(dist, 0, ofGetWidth() / 2, 191, 0));
			ofDrawLine(begin.x, begin.y, end.x, end.y);
		}
	}
	ofSetLineWidth(1);
	ofFill();

	ofDrawBitmapStringHighlight(log, 40, 40);
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) + " fps", 40, 60);
}

void ofApp::objectAdded(ofxTuioObject & tuioObject) {
	log = " new object: " + ofToString(tuioObject.getFiducialId()) +
		" X: " + ofToString(tuioObject.getX()) +
		" Y: " + ofToString(tuioObject.getY()) +
		" angle: " + ofToString(tuioObject.getAngleDegrees());
}
void ofApp::objectRemoved(ofxTuioObject & tuioObject) {
	log = " object removed: " + ofToString(tuioObject.getFiducialId()) +
		" X: " + ofToString(tuioObject.getX()) +
		" Y: " + ofToString(tuioObject.getY()) +
		" angle: " + ofToString(tuioObject.getAngleDegrees());
}
void ofApp::objectUpdated(ofxTuioObject & tuioObject) {
	log = " object updated: " + ofToString(tuioObject.getFiducialId()) +
		" X: " + ofToString(tuioObject.getX()) +
		" Y: " + ofToString(tuioObject.getY()) +
		" angle: " + ofToString(tuioObject.getAngleDegrees());
}
void ofApp::tuioAdded(ofxTuioCursor & tuioCursor) {
	log = " new cursor: " + ofToString(tuioCursor.getFingerId()) +
		" X: " + ofToString(tuioCursor.getX()) +
		" Y: " + ofToString(tuioCursor.getY());
}
void ofApp::tuioRemoved(ofxTuioCursor & tuioCursor) {
	log = " cursor removed: " + ofToString(tuioCursor.getFingerId()) +
		" X: " + ofToString(tuioCursor.getX()) +
		" Y: " + ofToString(tuioCursor.getY());
}
void ofApp::tuioUpdated(ofxTuioCursor & tuioCursor) {
	log = " cursor updated: " + ofToString(tuioCursor.getFingerId()) +
		" X: " + ofToString(tuioCursor.getX()) +
		" Y: " + ofToString(tuioCursor.getY());
}
