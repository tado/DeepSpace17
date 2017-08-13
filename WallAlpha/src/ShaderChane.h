#pragma once
#include "ofMain.h"

class ShaderChane{
public:
	ShaderChane();
	void update();
	void draw();

	vector<ofShader> shaders;
};

