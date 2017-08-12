#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofShader sd0; sd0.load("", "stripe.frag");
	shaders.push_back(sd0);
	ofShader sd1; sd1.load("", "circle.frag");
	shaders.push_back(sd1);
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	for (int i = 0; i < shaders.size(); i++) {
		shaders[i].begin();
		shaders[i].setUniform1f("time", ofGetElapsedTimef());
		shaders[i].setUniform2f("resolution", ofGetWidth(), ofGetHeight());
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		shaders[i].end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
