#pragma once
#include "ofMain.h"
#include "ofxSuperCollider.h"

class UgenObject {
public:
	UgenObject(int id, int type);
	void update();
	void draw();

	~UgenObject();
	ofShader shader;
	int id;
	int type; //0 = circle, 1 = noise
	ofVec2f pos;
	float initTime;
	ofxSCSynth *synth;
	float baseFreq;
};

