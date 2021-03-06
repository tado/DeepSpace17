#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	ofHideCursor();
	showDebug = false;

	//boot sc server
	server = new ofxSCSynthServer();
	server->boot();

	//OSC Receiver
	oscReceiver = new OSCReceiver();

	//Object Controller
	objectController = new ObjectController();

	//window loc
	//ofSetWindowPosition(0, 40);
}

void ofApp::update(){
	oscReceiver->update();
	objectController->update();
}

void ofApp::draw(){
	//oscReceiver->draw();
	objectController->draw();
	if (showDebug){
		ofDrawBitmapStringHighlight("fps = " + ofToString(ofGetFrameRate()), 40, 40);
	}
}

void ofApp::exit() {
	server->exit();
}


void ofApp::keyPressed(int key){

}


void ofApp::keyReleased(int key) {
	if (key == 'f') {
		ofToggleFullscreen();
	}
	if (key == 'd'){
		if (showDebug){
			showDebug = false;
		} else {
			showDebug = true;
		}
	}
}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::mouseEntered(int x, int y){

}


void ofApp::mouseExited(int x, int y){

}


void ofApp::windowResized(int w, int h){

}


void ofApp::gotMessage(ofMessage msg){

}


void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
