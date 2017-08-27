#include "UgenObject.h"
#include "ofApp.h"

UgenObject::UgenObject(int id, int type) {
	ofApp *app = ((ofApp*)ofGetAppPtr());

	this->id = id;
	this->type = type;
	int num = app->objectController->ugenObjects.size();
	initTime = ofGetElapsedTimef();

	switch (type){
	case 0:
		app->objectController->noiseNum++;
		shader.load("shaders/noise");
		synth = new ofxSCSynth("moog");
		synth->create(0, 0);
		synth->set("mul", 0.4);
		synth->set("base", 20.0 * powf(1.5, app->objectController->noiseNum));
		break;
	case 1:
	default:
		app->objectController->circleNum++;
		shader.load("shaders/circle");
		synth = new ofxSCSynth("ratio");
		synth->create(0, 0);
		synth->set("amp", 0.07);
		synth->set("modMix", 1.0);
		break;
	}
}

void UgenObject::update() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	for (int i = 0; i < app->oscReceiver->nodes.size(); i++) {
		if (id == app->oscReceiver->nodes[i].id) {
			pos = app->oscReceiver->nodes[i].position;
		}
	}
	float length = pos.distance(ofVec2f(0.5, 0.5));
	float lenX = abs(0.5 - pos.x);
	float lenY = abs(0.5 - pos.y);
	switch (type){
	case 0:
		synth->set("freq", ofMap(lenX, 0, 0.5, 600, 0));
		synth->set("gain", ofMap(lenY, 0, 0.5, 3.0, 0));
		break;
	case 1:
		synth->set("lpf", ofMap(lenX, 0, 0.5, 18000, 0));
		synth->set("rq", ofMap(lenY, 0, 0.5, 0.1, 0.7));
		synth->set("modSpeed", ofMap(lenY, 0, 0.5, 12.0, 4.0));
		break;
	}
	
}

void UgenObject::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	shader.begin();
	shader.setUniform1f("time", ofGetElapsedTimef() - initTime);
	shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	shader.setUniform2f("mouse", pos.x, pos.y);
	int num = app->objectController->ugenObjects.size();
	shader.setUniform1f("num", num);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
}

UgenObject::~UgenObject() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	switch (type) {
	case 0:
		app->objectController->noiseNum--;
		break;
	case 1:
		app->objectController->circleNum--;
		break;
	}
	synth->free();
}