#include "OSCSender.h"



OSCSender::OSCSender(){
	//OSC to wall
	//sender.setup("192.168.19.190", 20000);
	sender.setup("127.0.0.1", 20000);

	//TUIO
	ofAddListener(tuio.objectAdded, this, &OSCSender::objectAdded);
	ofAddListener(tuio.objectRemoved, this, &OSCSender::objectRemoved);
	ofAddListener(tuio.objectUpdated, this, &OSCSender::objectUpdated);
	ofAddListener(tuio.cursorAdded, this, &OSCSender::tuioAdded);
	ofAddListener(tuio.cursorRemoved, this, &OSCSender::tuioRemoved);
	ofAddListener(tuio.cursorUpdated, this, &OSCSender::tuioUpdated);

	//start TUIO
	tuio.start(3333);
	log = "";
}

OSCSender::~OSCSender(){
}

void OSCSender::update() {
	tuio.getMessage();

	//get Objects and Cursors
	objectList = tuio.getTuioObjects();
	cursorList = tuio.getTuioCursors();

	//send Objects num
	ofxOscMessage mn;
	mn.setAddress("/floor/objectNum");
	mn.addIntArg(cursorList.size() + objectList.size());
	sender.sendMessage(mn, false);
}

void OSCSender::draw() {

}

void OSCSender::objectAdded(ofxTuioObject & tuioObject) {
	log = " new object: " + ofToString(tuioObject.getFiducialId()) +
		" X: " + ofToString(tuioObject.getX()) +
		" Y: " + ofToString(tuioObject.getY()) +
		" angle: " + ofToString(tuioObject.getAngleDegrees());

	ofxOscMessage m;
	m.setAddress("/floor/objectAdded");
	m.addInt32Arg(tuioObject.getFiducialId());
	sender.sendMessage(m, false);
}
void OSCSender::objectRemoved(ofxTuioObject & tuioObject) {
	log = " object removed: " + ofToString(tuioObject.getFiducialId()) +
		" X: " + ofToString(tuioObject.getX()) +
		" Y: " + ofToString(tuioObject.getY()) +
		" angle: " + ofToString(tuioObject.getAngleDegrees());
	ofxOscMessage m;
	m.setAddress("/floor/objectRemoved");
	m.addInt32Arg(tuioObject.getFiducialId());
	sender.sendMessage(m, false);
}
void OSCSender::objectUpdated(ofxTuioObject & tuioObject) {
	log = " object updated: " + ofToString(tuioObject.getFiducialId()) +
		" X: " + ofToString(tuioObject.getX()) +
		" Y: " + ofToString(tuioObject.getY()) +
		" angle: " + ofToString(tuioObject.getAngleDegrees());
	ofxOscMessage m;
	m.setAddress("/floor/objectUpdated");
	m.addInt32Arg(tuioObject.getFiducialId());
	m.addFloatArg(tuioObject.getX());
	m.addFloatArg(tuioObject.getY());
	sender.sendMessage(m, false);
}
void OSCSender::tuioAdded(ofxTuioCursor & tuioCursor) {
	log = " new cursor: " + ofToString(tuioCursor.getFingerId()) +
		" X: " + ofToString(tuioCursor.getX()) +
		" Y: " + ofToString(tuioCursor.getY());
	ofxOscMessage m;
	m.setAddress("/floor/tuioAdded");
	m.addInt32Arg(tuioCursor.getFingerId() + 64);
	sender.sendMessage(m, false);
}
void OSCSender::tuioRemoved(ofxTuioCursor & tuioCursor) {
	log = " cursor removed: " + ofToString(tuioCursor.getFingerId()) +
		" X: " + ofToString(tuioCursor.getX()) +
		" Y: " + ofToString(tuioCursor.getY());
	ofxOscMessage m;
	m.setAddress("/floor/tuioRemoved");
	m.addInt32Arg(tuioCursor.getFingerId() + 64);
	sender.sendMessage(m, false);
}
void OSCSender::tuioUpdated(ofxTuioCursor & tuioCursor) {
	log = " cursor updated: " + ofToString(tuioCursor.getFingerId()) +
		" X: " + ofToString(tuioCursor.getX()) +
		" Y: " + ofToString(tuioCursor.getY());
	ofxOscMessage m;
	m.setAddress("/floor/tuioUpdated");
	m.addInt32Arg(tuioCursor.getFingerId() + 64);
	m.addFloatArg(tuioCursor.getX());
	m.addFloatArg(tuioCursor.getY());
	sender.sendMessage(m, false);
}