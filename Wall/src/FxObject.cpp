#include "FxObject.h"
#include "ofApp.h"

FxObject::FxObject(int id) {
	ofApp *app = ((ofApp*)ofGetAppPtr());

	this->id = id;
	this->type = app->objectController->fxObjects.size() % 7;
}

void FxObject::update() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	for (int i = 0; i < app->oscReceiver->nodes.size(); i++) {
		if (id == app->oscReceiver->nodes[i].id) {
			pos = app->oscReceiver->nodes[i].position;
		}
	}
	app->objectController->postProcess.updateFx(type, pos);
}

FxObject::~FxObject(){
}
