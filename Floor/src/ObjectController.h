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
};

class ObjectController{
public:
	ObjectController();
	void addObject(int id);
	void removeObject(int id);

	vector<FloorObject *> floorObjects;
	int ugenMax;
};

