#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1920, 1080, OF_FULLSCREEN);			// <-------- setup the GL context
	ofRunApp(new ofApp());
}