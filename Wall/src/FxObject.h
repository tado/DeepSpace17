#pragma once
#include "ofMain.h"

class FxObject {
public:
	FxObject(int id);
	void update();

	~FxObject();

	int id;
	int type; //0: kaleido, 1: noise, 2: toon
	ofVec2f pos;
};

