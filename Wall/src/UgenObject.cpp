#include "UgenObject.h"
#include "ofApp.h"

UgenObject::UgenObject(int id) {
	ofApp *app = ((ofApp*)ofGetAppPtr());

	this->id = id;
	int num = app->objectController->ugenObjects.size();
	initTime = ofGetElapsedTimef();

	switch (id % 2){
	case 0:
		shader.load("shaders/noise");
		synth = new ofxSCSynth("sine");
		synth->create(0, 0);
		baseFreq = ofRandom(110, 220);
		synth->set("freq", baseFreq);
		synth->set("mul", 0.4);
		break;
	case 1:
	default:
		shader.load("shaders/circle");
		synth = new ofxSCSynth("sine");
		synth->create(0, 0);
		baseFreq = ofRandom(2200, 4400);
		synth->set("freq", baseFreq);
		synth->set("mul", 0.1);
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
	synth->set("freq", baseFreq - (baseFreq * length * 0.2));
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

UgenObject::~UgenObject(){
	synth->free();
}
