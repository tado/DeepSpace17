#pragma once
#include "ofMain.h"

class FloorObject {
public:
	FloorObject(int id, int type) {
		this->type = type;
		this->id = id;
	}
	int type;
	int id;
	ofVec2f pos;
};

class ObjectController{
public:
	ObjectController();
	void update();
	void addObject(int id);
	void removeObject(int id);

	vector<FloorObject *> ugenObjects;
	vector<FloorObject *> fxObjects;
	int ugenMax;
};

