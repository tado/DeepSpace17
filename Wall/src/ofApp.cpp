#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);

	//OSC Receiver
	oscReceiver = new OSCReceiver();

	//Object Controller
	objectController = new ObjectController();

	//boot sc server
	server = new ofxSCSynthServer();
	server->boot();

	//window loc
	ofSetWindowPosition(0, 20);
}

void ofApp::update(){
	oscReceiver->update();
	objectController->update();
}

void ofApp::draw(){
	//oscReceiver->draw();
	objectController->draw();
}

void ofApp::exit() {
	server->exit();
}


void ofApp::keyPressed(int key){

}


void ofApp::keyReleased(int key){
	if (key == 'f')	{
		ofToggleFullscreen();
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
