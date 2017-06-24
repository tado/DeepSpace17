#include "ofApp.h"

void ofApp::setup(){
    //OSC receiver
    receiver.setup(20000);

    //Shader resolution
	scale = 4.0;
    
    //init ISF list
	ISFLayer *il;
	il = new ISFLayer("ISF/swirl.fs");
	isfLayers.push_back(il);
	il = new ISFLayer("ISF/stripe.fs");
	isfLayers.push_back(il);

    //Postprocessing
    post.init(ofGetWidth()/scale, ofGetHeight()/scale);
    //bloom = post.createPass<BloomPass>();
    kaleido = post.createPass<KaleidoscopePass>();
    noise = post.createPass<NoiseWarpPass>();
    rgb = post.createPass<RGBShiftPass>();
    edge = post.createPass<EdgePass>();
    pixel = post.createPass<PixelatePass>();
    //pixel->resolution = ofVec2f(40.0, 40.0);
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
    //lut = post.createPass<LUTPass>();
    toon = post.createPass<ToonPass>();
    restPostProcess();
    
    ofHideCursor();
}

void ofApp::update(){
    objectLoc.clear();
    
    //receiver OSC messages
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        if(m.getAddress() == "/floor/objectNum"){
            objectNum = m.getArgAsInt32(0);
        }
        else if(m.getAddress() == "/floor/objectLoc"){
            for(int i = 0; i < m.getNumArgs(); i+=2){
                ofVec2f loc = ofVec2f(m.getArgAsInt32(i), m.getArgAsInt32(i+1));
                objectLoc.push_back(loc);
            }
        }
    }

    for (int i = 0; i < isfLayers.size(); i++) {
        isfLayers[i]->update();
    }
    
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
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofBackground(0);
	ofPushMatrix();
	ofScale(scale, scale);
    post.begin();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255);
    for (int i = 0; i < isfLayers.size(); i++) {
        isfLayers[i]->draw();
    }
    post.end();
	ofPopMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) + " fps", 40, 40);
    //ofDrawBitmapStringHighlight("Post num = " + ofToString(postNum), 40, 60);
    ofDrawBitmapStringHighlight("Object num = " + ofToString(objectNum), 40, 60);
    
    //draw objects
    ofSetColor(0, 255, 255);
    int size = ofGetWidth()/150;
    for (int i = 0; i < objectLoc.size(); i++) {
        ofDrawCircle(objectLoc[i], size);
    }
}


void ofApp::restPostProcess(){
    //bloom->setEnabled(false);
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
    //lut->setEnabled(false);
    toon->setEnabled(false);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
