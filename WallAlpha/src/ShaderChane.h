#pragma once
#include "ofMain.h"

class ShaderObject {
public:
	ofShader shader;
	int id;
};

class ShaderChane{
public:
	ShaderChane();
	void update();
	void draw();
	void addShader(int id);
	void removeShader(int id);

	vector<ShaderObject> shaders;
};

