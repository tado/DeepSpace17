#include "ofApp.h"

void ofApp::setup() {
	ofBackground(0);
	ofSetFrameRate(60);

	//boot sc server
	server = new ofxSCSynthServer();
	server->boot();
	server->loadSynthDefsDir();

	//start FX
	col_fx = new ofxSCSynth("col_closefx");
	col_fx->create(0, 0);
	
	oscReceiver = new OSCReceiver();
	shaders = new ShaderChane();
	postProcess = new PostProcess();
}

void ofApp::update() {
	oscReceiver->update();
	shaders->update();
}

void ofApp::draw() {
	shaders->draw();
	//oscReceiver->draw();
}

void ofApp::keyPressed(int key) {

}


void ofApp::keyReleased(int key) {
	if (key == 'f'){
		ofToggleFullscreen();
	}
}


void ofApp::mouseMoved(int x, int y) {

}


void ofApp::mouseDragged(int x, int y, int button) {

}


void ofApp::mousePressed(int x, int y, int button) {

}


void ofApp::mouseReleased(int x, int y, int button) {

}


void ofApp::mouseEntered(int x, int y) {

}


void ofApp::mouseExited(int x, int y) {

}


void ofApp::windowResized(int w, int h) {

}


void ofApp::gotMessage(ofMessage msg) {

}


void ofApp::dragEvent(ofDragInfo dragInfo) {

}
