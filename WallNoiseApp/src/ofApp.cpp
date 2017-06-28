#include "ofApp.h"

void ofApp::setup(){
    //Shader resolution
    scale = 1.0;
    
    ofSetFrameRate(60);
    ofBackground(0);
    float freq;
    freq = ofRandom(2.0, 4.0);
    simplex.freqR.set(freq, freq);
    freq = ofRandom(2.0, 4.0);
    simplex.freqG.set(freq, freq);
    freq = ofRandom(2.0, 4.0);
    simplex.freqB.set(freq, freq);
    simplex.mul.set(3.0, 3.0, 3.0);
    simplex.speed.set(ofRandom(2.0), ofRandom(2.0), ofRandom(2.0));
    
    //Postprocessing
    post.init(ofGetWidth()/scale, ofGetHeight()/scale);
    kaleido = post.createPass<KaleidoscopePass>();
    noise = post.createPass<NoiseWarpPass>();
    rgb = post.createPass<RGBShiftPass>();
    edge = post.createPass<EdgePass>();
    pixel = post.createPass<PixelatePass>();
    darken = post.createPass<LimbDarkeningPass>();
    contrast = post.createPass<ContrastPass>();
    conv = post.createPass<ConvolutionPass>();
    dof = post.createPass<DofPass>();
    sss = post.createPass<FakeSSSPass>();
    fxaa = post.createPass<FxaaPass>();
    vtilt = post.createPass<VerticalTiltShifPass>();
    htilt = post.createPass<HorizontalTiltShifPass>();
    god = post.createPass<GodRaysPass>();
    bleach = post.createPass<BleachBypassPass>();
    toon = post.createPass<ToonPass>();
    restPostProcess();
    
    ofHideCursor();
}


void ofApp::update(){
    int div = int(ofRandom(30)) + 1;
    if (ofGetFrameNum() % div == 0) {
        restPostProcess();
        for (int i = 0; i < 2; i++) {
            postNum = int(ofRandom(15));
            //if (postNum == 0) bloom->setEnabled(true);
            if (postNum == 0) kaleido->setEnabled(true);
            if (postNum == 1) noise->setEnabled(true);
            if (postNum == 2) rgb->setEnabled(true);
            if (postNum == 3) edge->setEnabled(true);
            if (postNum == 4) pixel->setEnabled(true);
            if (postNum == 5) darken->setEnabled(true);
            if (postNum == 6) contrast->setEnabled(true);
            if (postNum == 7) conv->setEnabled(true);
            if (postNum == 8) dof->setEnabled(true);
            if (postNum == 9) sss->setEnabled(true);
            if (postNum == 10) fxaa->setEnabled(true);
            if (postNum == 11) vtilt->setEnabled(true);
            if (postNum == 12) htilt->setEnabled(true);
            if (postNum == 13) god->setEnabled(true);
            if (postNum == 14) bleach->setEnabled(true);
            //if (postNum == 16) lut->setEnabled(true);
            if (postNum == 15) toon->setEnabled(true);
        }
    }
}


void ofApp::draw(){
    ofBackground(0);
    ofPushMatrix();
    ofScale(scale, scale);
    post.begin();
    simplex.draw();
    post.end();
    ofPopMatrix();
}

void ofApp::restPostProcess(){
    kaleido->setEnabled(false);
    noise->setEnabled(false);
    rgb->setEnabled(true);
    edge->setEnabled(false);
    pixel->setEnabled(false);
    darken->setEnabled(false);
    contrast->setEnabled(false);
    conv->setEnabled(false);
    dof->setEnabled(false);
    sss->setEnabled(false);
    fxaa->setEnabled(false);
    vtilt->setEnabled(false);
    htilt->setEnabled(false);
    god->setEnabled(false);
    bleach->setEnabled(false);
    toon->setEnabled(false);
}


void ofApp::keyPressed(int key){

}


void ofApp::keyReleased(int key){

}


void ofApp::mouseMoved(int x, int y ){

}


void ofApp::mouseDragged(int x, int y, int button){

}


void ofApp::mousePressed(int x, int y, int button){

}


void ofApp::mouseReleased(int x, int y, int button){

}


void ofApp::mouseEntered(int x, int y){

}


void ofApp::mouseExited(int x, int y){

}


void ofApp::windowResized(int w, int h){

}


void ofApp::gotMessage(ofMessage msg){

}


void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
