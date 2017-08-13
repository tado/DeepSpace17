#include "OSCReceiver.h"

OSCReceiver::OSCReceiver(){
	receiver.setup(20000);
	objectNum = 0;
}

void OSCReceiver::update() {
	objectLoc.clear();
	objectId.clear();

	//receiver OSC messages
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		if (m.getAddress() == "/floor/objectNum") {
			objectNum = m.getArgAsInt32(0);
		}
		else if (m.getAddress() == "/floor/objectLoc") {
			for (int i = 0; i < m.getNumArgs(); i += 3) {
				ofVec2f loc = ofVec2f(m.getArgAsFloat(i), m.getArgAsFloat(i + 1));
				objectLoc.push_back(loc);
				objectId.push_back(m.getArgAsInt(i));
			}
		}
	}

	//cout << "Object Num = " << objectNum << endl;
}


void OSCReceiver::draw(){
	//draw objects
	ofSetColor(255);
	int size = ofGetWidth() / 80;
	for (int i = 0; i < objectLoc.size(); i++) {
		ofDrawCircle(objectLoc[i].x * ofGetWidth(), objectLoc[i].y * ofGetHeight(), size);
		ofDrawBitmapString(ofToString(objectId[i]), objectLoc[i].x * ofGetWidth() + 100, objectLoc[i].y * ofGetHeight());
	}
}
