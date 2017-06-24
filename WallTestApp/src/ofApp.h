#pragma once

#include "ofMain.h"
#include "ISFLayer.hpp"
#include "ofxPostProcessing.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void restPostProcess();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    vector<ISFLayer *> isfLayers;

	//postprocess
    ofxPostProcessing post;
    //BloomPass::Ptr bloom;
    KaleidoscopePass::Ptr kaleido;
    NoiseWarpPass::Ptr noise;
    RGBShiftPass::Ptr rgb;
    LimbDarkeningPass::Ptr darken;
    EdgePass::Ptr edge;
    PixelatePass::Ptr pixel;
    ContrastPass::Ptr contrast;
    ConvolutionPass::Ptr conv;
    DofPass::Ptr dof;
    FakeSSSPass::Ptr sss;
    FxaaPass::Ptr fxaa;
    VerticalTiltShifPass::Ptr vtilt;
    HorizontalTiltShifPass::Ptr htilt;
    GodRaysPass::Ptr god;
    BleachBypassPass::Ptr bleach;
    //LUTPass::Ptr lut;
    ToonPass::Ptr toon;
    
    int postNum;
	float scale;
    ofxOscReceiver receiver;
    int objectNum;
    vector<ofVec2f> objectLoc;
};
