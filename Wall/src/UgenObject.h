#pragma once
#include "ofMain.h"

class UgenObject {
public:
	UgenObject(int id);
	void update();
	void draw();

	~UgenObject();
	ofShader shader;
	int id;
	int type; //0 = circle, 1 = noise
	ofVec2f pos;
};

