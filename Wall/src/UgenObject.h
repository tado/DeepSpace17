#pragma once
#include "ofMain.h"

class UgenObject {
public:
	UgenObject(int id, string name);
	void update();
	void draw();

	~UgenObject();
	ofShader shader;
	int id;
};

