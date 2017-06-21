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
    
    tuio.start(3333);
    log="";
    myImage.loadImage("images/photo.png");
}

void ofApp::update(){
    tuio.getMessage();
}

void ofApp::draw(){
    list<ofxTuioObject*> objectList = tuio.getTuioObjects();
    list<ofxTuioObject*>::iterator it;
    for (it=objectList.begin(); it != objectList.end(); it++) {
        ofxTuioObject *blob = (*it);
        glPushMatrix();
        glTranslatef(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), 0.0);
        ofDrawBitmapString("id = " + ofToString(blob->getFiducialId(), 0), -64, 80);
        glRotatef(blob->getAngleDegrees(), 0.0, 0.0, 1.0);
        ofSetColor(255, 255, 255);
        myImage.draw(-64, -64);
        glPopMatrix();
    }
    
    ofSetColor(0xffffff);
    ofDrawBitmapString(log, 20, 20);
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