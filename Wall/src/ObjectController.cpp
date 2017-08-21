#include "ObjectController.h"

ObjectController::ObjectController() {
	//init FBO
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0, 0, 0);
	fbo.end();
}

void ObjectController::update() {
	for (int i = 0; i < ugenObjects.size(); i++) {
		ugenObjects[i]->update();
	}
}

void ObjectController::draw() {
	ofSetColor(255);
	fbo.begin();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofClear(0, 0, 0);
	for (int i = 0; i < ugenObjects.size(); i++) {
		ugenObjects[i]->draw();
	}
	fbo.end();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	fxObject.post.begin();
	fbo.draw(0, 0);
	fxObject.post.end();
}

void ObjectController::addObject(int id) {
	if (id % 2 == 0) {
		fxObject.addObject(id);
	} else {
		UgenObject *o = new UgenObject(id, "circle");
		ugenObjects.push_back(o);
	}
}

void ObjectController::removeObject(int id) {
	if (id % 2 == 0){
		fxObject.removeObject(id);
	} else {
		for (int i = 0; i < ugenObjects.size(); i++) {
			if (ugenObjects[i]->id == id) {
				ugenObjects.erase(ugenObjects.begin() + i);
			}
		}
	}
}

ObjectController::~ObjectController(){
}
