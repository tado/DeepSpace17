#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

class NodeObject {
public:
	int id;
	ofVec2f position;
	string shaderName;
};

class OSCReceiver {
public:
	OSCReceiver();
	void update();
	void draw();

	ofxOscReceiver receiver;
	int objectNum;
	vector<NodeObject> nodes;
	//vector<int> nodeIds;
};

