#include "ObjectController.h"

ObjectController::ObjectController() {

}

void ObjectController::update() {
	for (int i = 0; i < ugenObjects.size(); i++) {
		ugenObjects[i]->update();
	}
	for (int i = 0; i < fxObjects.size(); i++) {
		fxObjects[i]->update();
	}
}

void ObjectController::draw() {
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(255);
	for (int i = 0; i < ugenObjects.size(); i++) {
		ugenObjects[i]->draw();
	}
	for (int i = 0; i < fxObjects.size(); i++) {
		fxObjects[i]->draw();
	}
}

void ObjectController::addObject(int id) {
	UgenObject *o = new UgenObject(id, "circle");
	ugenObjects.push_back(o);
}

void ObjectController::removeObject(int id) {
	for (int i = 0; i < ugenObjects.size(); i++) {
		if (ugenObjects[i]->id == id) {
			ugenObjects.erase(ugenObjects.begin() + i);
		}
	}
}

ObjectController::~ObjectController(){
}
