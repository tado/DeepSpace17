#include "DrawCode.h"
#include "ofApp.h"

DrawCode::DrawCode() {
	string c0 =
		R"GLSL(
vec2 st = gl_FragCoord.xy/resolution.x;
float dist = length(vec2(0.5, 0.5) - mouse);
float br = pow(rand(time), 50.0 + (dist * 50.0)) * 1.0;
gl_FragColor = vec4(vec3(br), 1.0);
)GLSL";
	code.push_back(c0);

	string c1 =
		R"GLSL(
vec2 m = vec2(mouse.x * (resolution.x / resolution.y), mouse.y);
vec2 p = gl_FragCoord.xy / min(resolution.x, resolution.y);
float speed =  length(vec2(0.5, 0.5) - mouse) * 5.0 + 0.001;
float br = 1.2 / num;
float gain = 1.2;
float r = pow(sin(length(m - p) * 6.0 * speed - time * 32.) * gain, 4.0);
float g = pow(sin(length(m - p) * 6.5 * speed - time * 32.) * gain, 4.0);
float b = pow(sin(length(m - p) * 7.0 * speed - time * 32.) * gain, 4.0);
gl_FragColor = vec4(r * br, g * br, b * br, 1.0);
)GLSL";
	code.push_back(c1);

	string c2 =
		R"GLSL(
vec2 st = gl_FragCoord.xy / resolution.x;
float freq = 1.5 - length(vec2(0.5, 0.5) - mouse) * 2.0;
vec2 pos = vec2(st) * freq;
float br = 0.8 / num;
float speed = 1.75;
float gain = 12.1 - (length(vec2(0.5, 0.5) - mouse) * 12.0);
float r = mod(snoise(vec3(pos.x, pos.y, time * speed + 0.0)) * gain, 2.0);
float g = mod(snoise(vec3(pos.x, pos.y, time * speed + 1.0)) * gain, 2.0);
float b = mod(snoise(vec3(pos.x, pos.y, time * speed + 2.0)) * gain, 2.0);
gl_FragColor = vec4(vec3(r * br, g * br, b * br), 1.0);
)GLSL";
	code.push_back(c2);
}

void DrawCode::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	//draw code
	ofSetColor(255);
	int n = 0;
	for (auto it = app->oscSender->cursorList.begin(); it != app->oscSender->cursorList.end(); it++) {
		ofxTuioCursor *blob = (*it);
		ofDrawBitmapString(code[n], blob->getX()*ofGetWidth() + 50, blob->getY()*ofGetHeight());
		n = (n + 1) % code.size();
	}
	n = 0;
	for (auto it = app->oscSender->objectList.begin(); it != app->oscSender->objectList.end(); it++) {
		ofxTuioObject *blob = (*it);
		ofDrawBitmapString(code[n], blob->getX()*ofGetWidth() + 50, blob->getY()*ofGetHeight());
		n = (n + 1) % code.size();
	}
}


DrawCode::~DrawCode()
{
}
