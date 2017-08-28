#include "DrawCode.h"
#include "ofApp.h"

DrawCode::DrawCode() {
	font.load("SFMono-Regular.otf", 8);

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

	string s0 =
		R"SC(
arg freq = 440, density = 0.1, gate=1;
var out, env;
env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
out = Resonz.ar(Array.fill(64, {Dust.ar(density)}),
freq * [1, 2, 4, 8, 16], 0.01).sum * 35 * env;
4.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.01),rrand(0.0, 0.01)],0.01,0.06), 0.15) });
out = Limiter.ar(Pan2.ar(out, LFNoise0.ar(2)), 0.8)* EnvGen.kr(Env.asr, gate, doneAction:2);
Out.ar(3, out);
)SC";
	synth.push_back(s0);

	string s1 =
		R"SC(
arg base = 40, freq = 100, gain = 1.0, mul = 1.0, detune=1.01, gate=1;
var env, sig1, sig2, sig3, out;
env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
sig1 = MoogFF.ar(Pulse.ar([base, base*detune], 0.3), freq, gain, 0, mul);
sig2 = MoogFF.ar(Pulse.ar([base * 3.0, base * 3.0 * detune], 0.7), freq, gain, 0, mul);
out = (sig1 + sig2) * env;
12.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.01),rrand(0.0, 0.01)],0.01,0.06), 0.5) });
out = MidEQ.ar(out, 40, 0.75, 8);
out = Limiter.ar(out, 1.0);
out = LeakDC.ar(out)* EnvGen.kr(Env.asr, gate, doneAction:2);
Out.ar(3, out);
)SC";
	synth.push_back(s1);

	string s2 =
		R"SC(
arg lpf=8000, rq=0.2,atk=0.01,rel=1.0,
modSpeed=6.0,modMix=0.0,fx=0.3, gain=1,amp = 0.5, gate=1;
var env, ratio, n, d, p, q, mode, z, w, pul, mod,out;
env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
n = 64;
ratio = 1.5;
p = FloatArray.new(3*n);
q = FloatArray.new(3*n);
d = 3.0;
mode = 12;
n.do({ arg i; var freq;
	freq = mode.midicps * (ratio ** (i%n));
	p.add(freq);
	p.add(freq + d.rand2);
	p.add(freq + d.rand2);
});
n.do({ arg i;
	var freq;
	freq = p.at(3*i);
	q.add(freq + d.rand2);
	q.add(freq + d.rand2);
	q.add(freq + d.rand2);
});
z = [`[p, nil, FloatArray.rand(3*n, 0, 2pi)],`[q, nil, FloatArray.rand(3*n, 0, 2pi)]];
out = Klang.ar(z, 1, 0)*(0.5/n);
out = RLPF.ar(out, lpf, rq);
out = (out*gain*env).softclip*amp;
Out.ar(3 , out);
)SC";
	synth.push_back(s2);


}

void DrawCode::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	int margin = 20;
	//draw code
	ofSetColor(255);
	int n = 0;
	int s = 0;
	for (auto it = app->oscSender->cursorList.begin(); it != app->oscSender->cursorList.end(); it++) {
		ofxTuioCursor *blob = (*it);
		font.drawString(code[n], blob->getX()*ofGetWidth() + margin, blob->getY()*ofGetHeight() + margin);
		n = (n + 1) % code.size();
		ofPushMatrix();
		ofTranslate(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight());
		ofRotateZ(180);
		font.drawString(synth[s], margin, margin);
		ofPopMatrix();
		s = (s + 1) % code.size();
	}
	n = 0;
	s = 0;
	for (auto it = app->oscSender->objectList.begin(); it != app->oscSender->objectList.end(); it++) {
		ofxTuioObject *blob = (*it);
		font.drawString(code[n], blob->getX()*ofGetWidth() + margin, blob->getY()*ofGetHeight() + margin);
		n = (n + 1) % code.size();
		ofPushMatrix();
		ofTranslate(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight());
		ofRotateZ(180);
		font.drawString(synth[s], margin, margin);
		ofPopMatrix();
		s = (s + 1) % code.size();
	}
}


DrawCode::~DrawCode()
{
}
