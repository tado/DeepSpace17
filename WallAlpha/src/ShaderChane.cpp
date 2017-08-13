#include "ShaderChane.h"
#include "ofApp.h"

ShaderChane::ShaderChane(){

}

void ShaderChane::update() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	shaders.clear();
	for (int i = 0; i < app->oscReceiver->objectNum; i++) {
		ofShader sd; 
		sd.load("", "circle.frag");
		shaders.push_back(sd);
	}
}

void ShaderChane::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	for (int i = 0; i < app->oscReceiver->objectNum; i++) {
		shaders[i].begin();
		shaders[i].setUniform1f("time", ofGetElapsedTimef());
		shaders[i].setUniform2f("resolution", ofGetWidth(), ofGetHeight());
		ofVec2f pos;
		pos = app->oscReceiver->nodes[i].position;
		shaders[i].setUniform2f("mouse", pos.x, pos.y);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		shaders[i].end();
	}
}


