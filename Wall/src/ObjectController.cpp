#include "ObjectController.h"

ObjectController::ObjectController() {
	//init FBO
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0, 0, 0);
	fbo.end();

	thresh = 0.1;
	ugenMax = 4;
	noiseNum = 0;
	circleNum = 0;

	//Global reverb
	//reverb = new ofxSCSynth("reverb");
	//reverb->create(0, 0);
}

void ObjectController::update() {
	postProcess.update();
	for (int i = 0; i < ugenObjects.size(); i++) {
		ugenObjects[i]->update();
	}
	for (int i = 0; i < fxObjects.size(); i++) {
		fxObjects[i]->update();
	}

	//select postprocess
	float min = FLT_MAX;
	int minType;
	for (int i = 0; i < fxObjects.size(); i++) {
		for (int j = 0; j < ugenObjects.size(); j++) {
			float length = ugenObjects[j]->pos.distance(fxObjects[i]->pos);
			if (length < min) {
				min = length;
				minType = fxObjects[i]->type;
			}
		}
	}
	if (min < thresh) {
		postProcess.addFx(minType);
	}
	else {
		postProcess.resetPostProcess();
		postProcess.deleteFx();
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
	postProcess.post.begin();
	fbo.draw(0, 0);
	postProcess.post.end();
}

void ObjectController::addObject(int id) {
	if (ugenObjects.size() < ugenMax) {
		UgenObject *o = new UgenObject(id);
		ugenObjects.push_back(o);
	} else {
		FxObject *o = new FxObject(id);
		fxObjects.push_back(o);
		//postProcess.addObject(id);
	}
}

void ObjectController::removeObject(int id) {
	for (int i = 0; i < ugenObjects.size(); i++) {
		if (ugenObjects[i]->id == id) {
			delete ugenObjects[i];
			ugenObjects.erase(ugenObjects.begin() + i);
		}
	}
	for (int i = 0; i < fxObjects.size(); i++) {
		if (fxObjects[i]->id == id) {
			fxObjects.erase(fxObjects.begin() + i);
		}
	}
}

ObjectController::~ObjectController() {
}
