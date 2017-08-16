#include "ShaderChane.h"
#include "ofApp.h"

ShaderChane::ShaderChane(){
	shaderNames.push_back("circle.frag");
	shaderNames.push_back("stripe.frag");
}

void ShaderChane::update() {

}

void ShaderChane::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	for (int i = 0; i < shaders.size(); i++) {
		shaders[i].shader.begin();
		shaders[i].shader.setUniform1f("time", ofGetElapsedTimef());
		shaders[i].shader.setUniform1f("num", shaders.size());
		shaders[i].shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
		ofVec2f pos;
		pos = app->oscReceiver->nodes[i].position;
		shaders[i].shader.setUniform2f("mouse", pos.x, ofMap(pos.y, 0, 1, 1, 0));
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		shaders[i].shader.end();
	}
}

void ShaderChane::addShader(int id) {
	ShaderObject so;
	so.shader.load("", shaderNames[id % shaderNames.size()]);
	so.id = id;
	shaders.push_back(so);
}


void ShaderChane::removeShader(int id) {
	for (int i = 0; i < shaders.size(); i++){
		if (shaders[i].id == id){
			shaders.erase(shaders.begin() + i);
		}
	}
}