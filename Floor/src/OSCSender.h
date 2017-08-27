#pragma once
#include "ofMain.h"
#include "ofxTuio.h"

class OSCSender{
public:
	OSCSender();
	~OSCSender();

	void update();
	void draw();

	void objectAdded(ofxTuioObject & tuioObject);
	void objectRemoved(ofxTuioObject & tuioObject);
	void objectUpdated(ofxTuioObject & tuioObject);
	void tuioAdded(ofxTuioCursor & tuioCursor);
	void tuioRemoved(ofxTuioCursor & tuioCursor);
	void tuioUpdated(ofxTuioCursor & tuioCursor);

	ofxTuioClient tuio;
	ofxOscSender sender;
	string log;

	list<ofxTuioObject*> objectList;
	list<ofxTuioCursor*> cursorList;
};

