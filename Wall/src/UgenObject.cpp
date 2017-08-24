#include "UgenObject.h"
#include "ofApp.h"

UgenObject::UgenObject(int id) {
	ofApp *app = ((ofApp*)ofGetAppPtr());

	this->id = id;
	int num = app->objectController->ugenObjects.size();
	initTime = ofGetElapsedTimef();

	switch (num % 2){
	case 0:
		shader.load("shaders/noise");
		synth = new ofxSCSynth("moog");
		synth->create(0, 0);
		synth->set("mul", 0.6);
		synth->set("base", 40.0 * ofRandom(1.0, 1.01));
		break;
	case 1:
	default:
		shader.load("shaders/circle");
		synth = new ofxSCSynth("sine");
		synth->create(0, 0);
		baseFreq = ofRandom(2200, 4400);
		synth->set("freq", baseFreq);
		synth->set("mul", 0.001);
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
	switch (id%2){
	case 0:
		synth->set("freq", ofMap(lenX, 0, 1, 600, 5));
		synth->set("gain", ofMap(lenY, 0, 1, 4, 0));
		break;
	case 1:
		synth->set("freq", baseFreq - (baseFreq * length * 0.2));
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

UgenObject::~UgenObject(){
	synth->free();
}
