#pragma once
#include "ofMain.h"
#include "UgenObject.h"
#include "PostProcess.h"

class ObjectController{
public:
	ObjectController();
	void update();
	void draw();
	void addObject(int id);
	void removeObject(int id);
	~ObjectController();

	vector<UgenObject *> ugenObjects;
	PostProcess postProcess;
	ofFbo fbo;
};

