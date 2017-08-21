#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __WIN64__ ) || defined( _WIN64 )
#include <windows.h>
#endif

class ofxSCSynthServer {
public:
	ofxSCSynthServer();
	bool boot(string hostname = "127.0.0.1", unsigned int port = 57110);
#if defined(TARGET_OSX)
	void loadSynthDefsDir(string path = "../../../data/synthdefs");
#endif
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __WIN64__ ) || defined( _WIN64 )
	void loadSynthDefsDir(string path = ".\\data\\synthdefs");
#endif
	void exit();

	ofxOscSender sender;

#if defined(TARGET_OSX)
	pid_t pid;
#endif

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __WIN64__ ) || defined( _WIN64 )
	PROCESS_INFORMATION pi;
#endif
};
