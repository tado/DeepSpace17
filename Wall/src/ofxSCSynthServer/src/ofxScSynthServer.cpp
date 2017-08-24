#include "ofxSCSynthServer.h"

ofxSCSynthServer::ofxSCSynthServer() {
}

bool ofxSCSynthServer::boot(string hostname, unsigned int port) {
    
#if defined(TARGET_OSX)
    string command = "../../../../../../../addons/ofxSCSynthServer/libs/server/mac/scsynth";
    string arg = "-u " + ofToString(port);
    pid_t parent = getpid();
    pid_t child = fork();
    int status;
    if (child == -1){
        cout << "error, failed to boot scsynth" << endl;
    } else if (child > 0) {
        pid = child;
        waitpid(child, &status, 1);
    } else {
        execlp(command.c_str(), "scsynth", "-u", ofToString(port).c_str(), NULL);
    }
    ofSleepMillis(4000);
#endif
    
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __WIN64__ ) || defined( _WIN64 )
    // start scsynth
    STARTUPINFOA si;
    GetStartupInfoA(&si);
	string strCmd = ".\\libs\\server\\win\\scsynth.exe -D 0 -u " + ofToString(port);
	LPSTR command = LPSTR(strCmd.c_str());
	bool bSucess = false;
	if (!CreateProcessA(NULL, command, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi)) {
		cout << "Error: CreateProcess for boot scsynth" << endl;
	} else {
		WaitForSingleObject(pi.hProcess, 2000);
	}
	//OSC setup
    sender.setup(hostname, port);
	//load synthdefs
	loadSynthDefsDir(".\\data\\synthdefs");
	ofSleepMillis(2000);
#endif

	return true;
}

void ofxSCSynthServer::loadSynthDefsDir(string path) {
    //load syntdef
    ofxOscMessage m;
    m.setAddress("/d_loadDir");
    m.addStringArg(path);
    sender.sendMessage(m);
}

void ofxSCSynthServer::exit() {
#if defined(TARGET_OSX)
    kill(pid, SIGKILL);
#endif
    
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __WIN64__ ) || defined( _WIN64 )
    TerminateProcess(pi.hProcess, 0);
#endif
}