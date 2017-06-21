#pragma once

#include "ofMain.h"
#include "ofxTuio.h"

class ofApp : public ofSimpleApp{
public:
    void setup();
    void update();
    void draw();
    
    void objectAdded(ofxTuioObject & tuioObject);
    void objectRemoved(ofxTuioObject & tuioObject);
    void objectUpdated(ofxTuioObject & tuioObject);
    
    void tuioAdded(ofxTuioCursor & tuioCursor);
    void tuioRemoved(ofxTuioCursor & tuioCursor);
    void tuioUpdated(ofxTuioCursor & tuioCursor);
    
    ofxTuioClient tuio;
    string log;
};
