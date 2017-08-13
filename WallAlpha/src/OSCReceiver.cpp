#include "OSCReceiver.h"

OSCReceiver::OSCReceiver(){
	receiver.setup(20000);
	objectNum = 0;
}

void OSCReceiver::update() {
	objectLoc.clear();

	//receiver OSC messages
	while (receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(m);
		if (m.getAddress() == "/floor/objectNum") {
			objectNum = m.getArgAsInt32(0);
		}
		else if (m.getAddress() == "/floor/objectLoc") {
			for (int i = 0; i < m.getNumArgs(); i += 2) {
				ofVec2f loc = ofVec2f(m.getArgAsFloat(i), m.getArgAsFloat(i + 1));
				objectLoc.push_back(loc);
			}
		}
	}

	cout << "Object Num = " << objectNum << endl;
}


void OSCReceiver::draw(){
	//draw objects
	ofSetColor(255);
	int size = ofGetWidth() / 80;
	for (int i = 0; i < objectLoc.size(); i++) {
		ofDrawCircle(objectLoc[i].x * ofGetWidth(), objectLoc[i].y * ofGetHeight(), size);
	}
}
