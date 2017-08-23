#include "UgenObject.h"
#include "ofApp.h"

UgenObject::UgenObject(int id) {
	this->id = id;
	type = int(ofRandom(2));
	switch (type){
	case 0:
		shader.load("shaders/circle");
		break;
	case 1:
	default:
		shader.load("shaders/noise");
		break;
	}
}

void UgenObject::update() {

}

void UgenObject::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	shader.begin();
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	ofVec2f pos;
	for (int i = 0; i < app->oscReceiver->nodes.size(); i++) {
		if (id == app->oscReceiver->nodes[i].id) {
			pos = app->oscReceiver->nodes[i].position;
			shader.setUniform2f("mouse", pos.x, pos.y);
		}
	}
	int num = app->objectController->ugenObjects.size();
	shader.setUniform1f("num", num);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
}

UgenObject::~UgenObject()
{
}
