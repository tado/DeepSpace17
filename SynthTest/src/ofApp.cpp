#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	ofSetFrameRate(60);
	status = 0;

	//boot sc server
	server = new ofxSCSynthServer();
	bool succes = server->boot();
	if (succes){
		status = 1;
	}

	//start synthes
	ofxSCSynth *reverb = new ofxSCSynth("reverb");
	reverb->create(0, 0);

	ofxSCSynth *reso0 = new ofxSCSynth("reso");
	reso0->create(0, 0);
	reso0->set("freq", 80);

	ofxSCSynth *reso1 = new ofxSCSynth("reso");
	reso1->create(0, 0);
	reso1->set("freq", 120);

	ofxSCSynth *reso2 = new ofxSCSynth("reso");
	reso2->create(0, 0);
	reso2->set("freq", 180);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	switch (status){
		case 0:
			ofDrawBitmapString("wait for boot SuperCollider...", 20, 20);
			break;
		case 1:
			ofDrawBitmapString("SuperCollider server ready!!", 20, 20);
			break;
	}
}

void ofApp::exit() {
	server->exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
