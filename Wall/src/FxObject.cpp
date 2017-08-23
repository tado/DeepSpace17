#include "FxObject.h"
#include "ofApp.h"

FxObject::FxObject(int id) {
	this->id = id;
	this->type = int(ofRandom(8));
}

void FxObject::update() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	for (int i = 0; i < app->oscReceiver->nodes.size(); i++) {
		if (id == app->oscReceiver->nodes[i].id) {
			pos = app->oscReceiver->nodes[i].position;
		}
	}
}

FxObject::~FxObject(){
}
