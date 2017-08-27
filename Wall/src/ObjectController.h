#pragma once
#include "ofMain.h"
#include "UgenObject.h"
#include "FxObject.h"
#include "PostProcess.h"
#include "ofxSuperCollider.h"

class ObjectController{
public:
	ObjectController();
	void update();
	void draw();
	void addObject(int id);
	void removeObject(int id);
	~ObjectController();

	vector<UgenObject *> ugenObjects;
	vector<FxObject *> fxObjects;
	PostProcess postProcess;
	ofFbo fbo;
	float thresh;
	ofxSCSynth *reverb;
	int ugenMax;
	int noiseNum;
	int circleNum;
	int blinkNum;
};

