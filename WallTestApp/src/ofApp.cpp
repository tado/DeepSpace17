#include "ofApp.h"

void ofApp::setup(){
    //OSC receiver
    receiver.setup(20000);

    //Shader resolution
	scale = 1.0;
    
    //init ISF list
	//ISFLayer *il;
    //il = new ISFLayer("ISF/swirl.fs");
	//isfLayers.push_back(il);
	//il = new ISFLayer("ISF/stripe.fs");
	//isfLayers.push_back(il);
    //il = new ISFLayer("ISF/ripple.fs");
    //isfLayers.push_back(il);

	simplex.freqR.set(1, 1);
	simplex.freqG.set(1.2, 1.2);
	simplex.freqB.set(1.5, 1.5);
	simplex.mul.set(10.0, 10.0, 10.0);
	simplex.speed.set(0.3, 0.4, 0.5);

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

	/*
    for (int i = 0; i < isfLayers.size(); i++) {
        isfLayers[i]->update();
    }
	*/
    
    int div = int(ofRandom(30)) + 1;
    if (ofGetFrameNum() % div == 0) {
        restPostProcess();
        for (int i = 0; i < 1; i++) {
            postNum = int(ofRandom(7));
            if (postNum == 0) kaleido->setEnabled(true);
            if (postNum == 1) noise->setEnabled(true);
            if (postNum == 2) rgb->setEnabled(true);
			if (postNum == 3) darken->setEnabled(true);
            if (postNum == 4) pixel->setEnabled(true);
			if (postNum == 5) toon->setEnabled(true);
			if (postNum == 6) conv->setEnabled(true);
			if (postNum == 7) contrast->setEnabled(true);
			/*
			if (postNum == 3) edge->setEnabled(true);
            if (postNum == 6) contrast->setEnabled(true);
            if (postNum == 7) conv->setEnabled(true);
            if (postNum == 8) dof->setEnabled(true);
            if (postNum == 9) sss->setEnabled(true);
            if (postNum == 10) fxaa->setEnabled(true);
            if (postNum == 11) vtilt->setEnabled(true);
            if (postNum == 12) htilt->setEnabled(true);
            if (postNum == 13) god->setEnabled(true);
            if (postNum == 14) bleach->setEnabled(true);
			*/
        }
    }
}

void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofBackground(0);
	ofPushMatrix();
	ofScale(scale, scale);
    post.begin();
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255);
	/*
    for (int i = 0; i < isfLayers.size(); i++) {
        isfLayers[i]->draw();
    }
	*/
	simplex.draw();
    post.end();
	ofPopMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofDrawBitmapStringHighlight("Post num = " + ofToString(postNum), 40, 60);
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()) + " fps", 40, 40);
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
    rgb->setEnabled(false);
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
