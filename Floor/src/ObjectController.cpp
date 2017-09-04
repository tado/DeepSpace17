#include "ObjectController.h"
#include "ofApp.h"

ObjectController::ObjectController() {
	ugenMax = 6;
}

void ObjectController::update() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	for (auto it = app->oscSender->cursorList.begin(); it != app->oscSender->cursorList.end(); it++) {
		ofxTuioCursor *blob = (*it);
		for (int i = 0; i < ugenObjects.size(); i++) {
			if (ugenObjects[i]->id == blob->getFingerId()) {
				ugenObjects[i]->pos.x = blob->getX();
				ugenObjects[i]->pos.y = blob->getY();
			}
		}
		for (int i = 0; i < fxObjects.size(); i++) {
			if (fxObjects[i]->id == blob->getFingerId()) {
				fxObjects[i]->pos.x = blob->getX();
				fxObjects[i]->pos.y = blob->getY();
			}
		}
	}
	for (auto it = app->oscSender->objectList.begin(); it != app->oscSender->objectList.end(); it++) {
		ofxTuioObject *blob = (*it);
		for (int i = 0; i < ugenObjects.size(); i++) {
			if (ugenObjects[i]->id == blob->getFiducialId()) {
				ugenObjects[i]->pos.x = blob->getX();
				ugenObjects[i]->pos.y = blob->getY();
			}
		}
		for (int i = 0; i < fxObjects.size(); i++) {
			if (fxObjects[i]->id == blob->getFiducialId()) {
				fxObjects[i]->pos.x = blob->getX();
				fxObjects[i]->pos.y = blob->getY();
			}
		}
	}
}

void ObjectController::addObject(int id) {
	if (ugenObjects.size() < ugenMax) {
		int type;
		int typeNum[3] = { 0, 0, 0 };
		//set ugen type
		for (int i = 0; i < ugenObjects.size(); i++) {
			typeNum[ugenObjects[i]->type]++;
		}
		if (typeNum[0] < typeNum[1]) {
			type = 0;
		}
		else if (typeNum[1] < typeNum[2]) {
			type = 1;
		}
		else {
			type = 2;
		}

		FloorObject *o = new FloorObject(id, type);
		ugenObjects.push_back(o);
	} else {
		int type = fxObjects.size() % 5 + 3;
		FloorObject *o = new FloorObject(id, type);
		fxObjects.push_back(o);
	}
}

void ObjectController::removeObject(int id) {
	for (int i = 0; i < ugenObjects.size(); i++) {
		if (ugenObjects[i]->id == id) {
			ugenObjects.erase(ugenObjects.begin() + i);
		}
	}
	for (int i = 0; i < fxObjects.size(); i++) {
		if (fxObjects[i]->id == id) {
			fxObjects.erase(fxObjects.begin() + i);
		}
	}
}

