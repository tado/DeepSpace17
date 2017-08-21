#include "UgenObject.h"
#include "ofApp.h"

UgenObject::UgenObject(int id, string name) {
	shader.load("", "shaders/" + name + ".frag");
	this->id = id;
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
			shader.setUniform2f("mouse", pos.x, ofMap(pos.y, 0, 1, 1, 0));
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
