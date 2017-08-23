#include "UgenObject.h"
#include "ofApp.h"

UgenObject::UgenObject(int id) {
	ofApp *app = ((ofApp*)ofGetAppPtr());

	this->id = id;
	int num = app->objectController->ugenObjects.size();
	initTime = ofGetElapsedTimef();

	switch (id % 2){
	case 0:
		shader.load("shaders/noise");
		break;
	case 1:
	default:
		shader.load("shaders/circle");
		break;
	}
}

void UgenObject::update() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	for (int i = 0; i < app->oscReceiver->nodes.size(); i++) {
		if (id == app->oscReceiver->nodes[i].id) {
			pos = app->oscReceiver->nodes[i].position;
		}
	}
}

void UgenObject::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	shader.begin();
	shader.setUniform1f("time", ofGetElapsedTimef() - initTime);
	shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	shader.setUniform2f("mouse", pos.x, pos.y);
	int num = app->objectController->ugenObjects.size();
	shader.setUniform1f("num", num);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
}

UgenObject::~UgenObject()
{
}
