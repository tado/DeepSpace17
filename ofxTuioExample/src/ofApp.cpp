#include "ofApp.h"

void ofApp::setup(){
    ofAddListener(tuio.objectAdded,this,&ofApp::objectAdded);
    ofAddListener(tuio.objectRemoved,this,&ofApp::objectRemoved);
    ofAddListener(tuio.objectUpdated,this,&ofApp::objectUpdated);
    ofAddListener(tuio.cursorAdded,this,&ofApp::tuioAdded);
    ofAddListener(tuio.cursorRemoved,this,&ofApp::tuioRemoved);
    ofAddListener(tuio.cursorUpdated,this,&ofApp::tuioUpdated);
    ofSetFrameRate(60);
    ofBackground(0,0,0);
	ofEnableSmoothing();
	ofHideCursor();
    
    tuio.start(3333);
    log="";
}

void ofApp::update(){
    tuio.getMessage();
}

void ofApp::draw(){
    list<ofxTuioObject*> objectList = tuio.getTuioObjects();
	float circleSize = ofGetWidth() / 80;
	ofSetColor(255);
	ofSetCircleResolution(64);
	ofNoFill();
	ofSetLineWidth(4);
	
	//draw circle
    for (auto it=objectList.begin(); it != objectList.end(); it++) {
        ofxTuioObject *blob = (*it);
		ofPushMatrix();
        ofTranslate(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight());
		ofDrawCircle(0, 0, circleSize, circleSize);
        ofPopMatrix();
    }

	//draw lines
	ofSetLineWidth(3);
	for (auto i = objectList.begin(); i != objectList.end(); i++) {
		for (auto j = i; j != objectList.end(); j++) {
			ofxTuioObject *blobi = (*i);
			ofxTuioObject *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			float dist = begin.distance(end);
			ofSetColor(255, ofMap(dist, 0, ofGetWidth()/2, 191, 0));
			ofDrawLine(begin.x, begin.y, end.x, end.y);
		}
	}
	ofSetLineWidth(1);
	ofFill();

	ofDrawBitmapStringHighlight(log, 40, 40);
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) + " fps", 40, 60);
}

void ofApp::objectAdded(ofxTuioObject & tuioObject){
    log = " new object: " + ofToString(tuioObject.getFiducialId())+
    " X: "+ofToString(tuioObject.getX())+
    " Y: "+ofToString(tuioObject.getY())+
    " angle: "+ofToString(tuioObject.getAngleDegrees());
}
void ofApp::objectRemoved(ofxTuioObject & tuioObject){
    log = " object removed: " + ofToString(tuioObject.getFiducialId())+
    " X: "+ofToString(tuioObject.getX())+
    " Y: "+ofToString(tuioObject.getY())+
    " angle: "+ofToString(tuioObject.getAngleDegrees());
}
void ofApp::objectUpdated(ofxTuioObject & tuioObject){
    log = " object updated: " + ofToString(tuioObject.getFiducialId())+
    " X: "+ofToString(tuioObject.getX())+
    " Y: "+ofToString(tuioObject.getY())+
    " angle: "+ofToString(tuioObject.getAngleDegrees());
}
void ofApp::tuioAdded(ofxTuioCursor & tuioCursor){
    log = " new cursor: " + ofToString(tuioCursor.getFingerId())+
    " X: "+ofToString(tuioCursor.getX())+
    " Y: "+ofToString(tuioCursor.getY());
}
void ofApp::tuioRemoved(ofxTuioCursor & tuioCursor){
    log =  " cursor removed: " + ofToString(tuioCursor.getFingerId())+
    " X: "+ofToString(tuioCursor.getX())+
    " Y: "+ofToString(tuioCursor.getY());
}
void ofApp::tuioUpdated(ofxTuioCursor & tuioCursor){
    log =  " cursor updated: " + ofToString(tuioCursor.getFingerId())+
    " X: "+ofToString(tuioCursor.getX())+
    " Y: "+ofToString(tuioCursor.getY());
}