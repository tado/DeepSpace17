#include "OSCReceiver.h"
#include "ofApp.h"

OSCReceiver::OSCReceiver() {
	receiver.setup(20000);
	objectNum = 0;
}

void OSCReceiver::update() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	//receiver OSC messages
	while (receiver.hasWaitingMessages()) {
		//nodes.clear();
		ofxOscMessage m;
		receiver.getNextMessage(m);
		if (m.getAddress() == "/floor/objectNum") {
			objectNum = m.getArgAsInt32(0);
		}
		else if (m.getAddress() == "/floor/objectAdded" || m.getAddress() == "/floor/tuioAdded") {
			NodeObject n;
			n.id = m.getArgAsInt(0);
			nodes.push_back(n);
			//app->shaders->addShader(m.getArgAsInt(0));
			app->objectController->addObject(m.getArgAsInt(0));
		}
		else if (m.getAddress() == "/floor/objectRemoved" || m.getAddress() == "/floor/tuioRemoved") {
			for (int i = 0; i < nodes.size(); i++) {
				if (m.getArgAsInt(0) == nodes[i].id) {
					nodes.erase(nodes.begin() + i);
				}
			}
			//app->shaders->removeShader(m.getArgAsInt(0));
			app->objectController->removeObject(m.getArgAsInt(0));
		}
		else if (m.getAddress() == "/floor/objectUpdated" || m.getAddress() == "/floor/tuioUpdated") {
			for (int i = 0; i < nodes.size(); i++) {
				if (m.getArgAsInt(0) == nodes[i].id) {
					nodes[i].position = ofVec2f(m.getArgAsFloat(1), m.getArgAsFloat(2));
				}
			}
		}
	}
}

void OSCReceiver::draw() {
	//draw objects
	ofSetColor(255);
	int size = ofGetWidth() / 80;
	for (int i = 0; i < nodes.size(); i++) {
		ofDrawCircle(nodes[i].position.x * ofGetWidth(), nodes[i].position.y * ofGetHeight(), size);
		ofDrawBitmapString(ofToString(nodes[i].id), nodes[i].position.x * ofGetWidth() + 100, nodes[i].position.y * ofGetHeight());
	}
}
