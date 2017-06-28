#pragma once

#include "ofMain.h"
#include "ofxGLSLSimplexNoise.h"
#include "ofxPostProcessing.h"

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
    
    ofxGLSLSimplexNoise simplex;

    //postprocess
    ofxPostProcessing post;
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
    ToonPass::Ptr toon;
    
    float scale;
    int postNum;
};
