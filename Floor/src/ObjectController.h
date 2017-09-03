#pragma once
#include "ofMain.h"

class FloorObject {
public:
	string code;
	int id;
};

class ObjectController{
public:
	ObjectController();
	void addObject();

	vector<FloorObject> objects;
};

