#include "ISFLayer.hpp"

ISFLayer::ISFLayer(string filename){
    gain = 1.0;

	ofxISF::Shader *isf;
	isf = new ofxISF::Shader();
	isf->setup(ofGetWidth(), ofGetHeight(), GL_RGB32F);
	isf->load(filename);
	isfs.push_back(isf);
}

void ISFLayer::update(){
    for (int i = 0; i < isfs.size(); i++) {
        //if (currentISF == isfs[i]->getName()) {
            isfs[i]->update();
        //}
    }
}

void ISFLayer::draw(){
    //ofSetColor(gain * 255);
    for (int i = 0; i < isfs.size(); i++) {
        //if (currentISF == isfs[i]->getName()) {
            isfs[i]->draw(0, 0, ofGetWidth(), ofGetHeight());
        //}
    }
}
