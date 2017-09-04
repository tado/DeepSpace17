#include "DrawCode.h"
#include "ofApp.h"

DrawCode::DrawCode() {
	font.load("SFMono-Regular.otf", 8);

	string c0 =
		R"GLSL(
//GLSL: Circle
void main() {
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
}
)GLSL";
	code.push_back(c0);

	string c1 =
		R"GLSL(
//GLSL: Noise
void main() {
    vec2 m = vec2(mouse.x * (resolution.x / resolution.y), mouse.y);
    vec2 p = gl_FragCoord.xy / min(resolution.x, resolution.y);
    float speed =  length(vec2(0.5, 0.5) - mouse) * 5.0 + 0.001;
    float br = 1.2 / num;
    float gain = 1.2;
    float r = pow(sin(length(m - p) * 6.0 * speed - time * 32.) * gain, 4.0);
    float g = pow(sin(length(m - p) * 6.5 * speed - time * 32.) * gain, 4.0);
    float b = pow(sin(length(m - p) * 7.0 * speed - time * 32.) * gain, 4.0);
    gl_FragColor = vec4(r * br, g * br, b * br, 1.0);
}
)GLSL";
	code.push_back(c1);

	string c2 =
		R"GLSL(
//GLSL: Blink
void main() {
    vec2 st = gl_FragCoord.xy/resolution.x;
    float dist = length(vec2(0.5, 0.5) - mouse);
    float br = pow(rand(time), 50.0 + (dist * 50.0)) * 1.0;
    gl_FragColor = vec4(vec3(br), 1.0);
}
)GLSL";
	code.push_back(c2);

	string c3 =
		R"GLSL(
//PostProcess: Kaleidoscope
uniform sampler2D tex;
uniform float segments;
void main() {
    vec2 uv = gl_TexCoord[0].st;
    vec2 normed = 2.0 * uv - 1.0;
    float r = length(normed);
    float theta = atan(normed.y / abs(normed.x));
    theta *= segments;
    vec2 newUv = (vec2(r * cos(theta), r * sin(theta)) + 1.0) / 2.0;
    gl_FragColor = texture2D(tex, newUv);
}
)GLSL";
	code.push_back(c3);

	string c4 =
		R"GLSL(
//PostProcess: NoiseWrap
void main() {
    vec2 texCoords = gl_TexCoord[0].st + vec2(
        amplitude * (snoise(vec3(frequency * gl_TexCoord[0].s, frequency * gl_TexCoord[0].t, speed * time))),
        amplitude * (snoise(vec3(frequency * gl_TexCoord[0].s + 17.0, frequency * gl_TexCoord[0].t, speed * time)))
    );
    gl_FragColor = texture2D(tex, texCoords);
}
)GLSL";
	code.push_back(c4);

	string c5 =
		R"GLSL(
//PostProcess: Toon
void main(void){
    float dxtex = 1.0 / textureSizeX;
    float dytex = 1.0 / textureSizeY;
    vec2 st = gl_TexCoord[0].st;
    vec3 center = getNormal(st).rgb;
    vec3 left = getNormal(st + vec2(dxtex, 0.0)).rgb;
    vec3 right = getNormal(st + vec2(-dxtex, 0.0)).rgb;
    vec3 up = getNormal(st + vec2(0.0, -dytex)).rgb;
    vec3 down = getNormal(st + vec2(0.0, dytex)).rgb;
    vec3 laplace = abs(-4.0*center + left + right + up + down);
    vec4 line = texture2D(normalImage, st);
    if(laplace.r > normalEdgeThreshold || laplace.g > normalEdgeThreshold || laplace.b > normalEdgeThreshold){
        line = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        line = vec4(1.0, 1.0, 1.0, 1.0);
    }
    vec3 lightPosition = gl_LightSource[0].position.xyz;
    vec3 L = normalize(lightPosition - v);
    vec3 E = normalize(-v);
    vec3 R = normalize(-reflect(L,N));
    vec4 Iamb = ambient;
    vec4 Idiff = texture2D( normalImage, gl_TexCoord[0].st) * diffuse;
    Idiff *= max(dot(N,L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);
    vec4 Ispec = specular;
    Ispec *= pow(max(dot(R,E),0.0), shinyness);
    Ispec = clamp(Ispec, 0.0, 1.0); 
    vec4 color = Iamb + Idiff;
    if ( bSpecular == 1 ) color += Ispec;
    float alpha = color.a;
    color = floor(0.5 + (qLevel * color)) / qLevel;
    color.a = alpha;
    gl_FragColor = color * line;
}
)GLSL";
	code.push_back(c5);

	string c6 =
		R"GLSL(
//PostProcess: Pixelate
void main() {
    vec2 texCoords = vec2(floor(gl_TexCoord[0].s * xPixels) / xPixels, floor(gl_TexCoord[0].t * yPixels) / yPixels);
    gl_FragColor = texture2D(tex, texCoords);
}
)GLSL";
	code.push_back(c6);

	string c7 =
		R"GLSL(
//PostProcess: SSS
void main() {
    vec2 vUv = gl_TexCoord[0].st;
    vec2 noise = rand( vUv );
    float depth = readDepth( vUv );
    float tt = clamp( depth, aoClamp, 1.0 );
    float w = ( 1.0 / width )  / tt + ( noise.x * ( 1.0 - noise.x ) );
    float h = ( 1.0 / height ) / tt + ( noise.y * ( 1.0 - noise.y ) );
    float pw;
    float ph;
    float ao;
    float dz = 1.0 / float( samples );
    float z = 1.0 - dz / 2.0;
    float l = 0.0;
    for ( int i = 0; i <= samples; i ++ ) {
        float r = sqrt( 1.0 - z );
        pw = cos( l ) * r;
        ph = sin( l ) * r;
        ao += calcAO( depth, pw * w, ph * h );
        z = z - dz;
        l = l + DL;
    }
    ao /= float( samples );
    ao = 1.0 - ao;
    if ( fogEnabled ) {
        ao = mix( ao, 1.0, doFog() );
    }
    vec3 color = texture2D( tDiffuse, vUv ).rgb;
    vec3 lumcoeff = vec3( 0.299, 0.587, 0.114 );
    float lum = dot( color.rgb, lumcoeff );
    vec3 luminance = vec3( lum );
    vec3 final = vec3( color * mix( vec3( ao ), vec3( 1.0 ), luminance * lumInfluence ) );
    if ( onlyAO ) {
        final = onlyAOColor * vec3( mix( vec3( ao ), vec3( 1.0 ), luminance * lumInfluence ) );
    }
    gl_FragColor = vec4( final, 1.0 );
}
)GLSL";
	code.push_back(c7);

	string s0 =
		R"SC(
//SuperCollider: Ratio
SynthDef("ratio",{
    arg lpf=8000, rq=0.2,atk=0.01,rel=1.0,
    modSpeed=6.0,modMix=0.0,fx=0.3, gain=1,amp = 0.5, gate=1, pan=0;
    var env, ratio, n, d, p, q, mode, z, w, pul, mod,out;

    env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
    n = 64;
    ratio = 1.5;
    pul = Impulse.ar(modSpeed);
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
    z = [`[p, nil, FloatArray.rand(3*n, 0, 2pi)],
        `[q, nil, FloatArray.rand(3*n, 0, 2pi)]];
    out = Klang.ar(z, 1, 0)*(0.5/n);
    out = RLPF.ar(out, lpf, rq);
    out = (out*gain*env).softclip*amp;
    w = out;
    mod = out * Decay2.ar(pul, atk, rel);
    out = (mod * modMix) + (out * (1-modMix));
    8.do({ w = AllpassL.ar(w, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.15), 2) });
    out[0] = out[0] * (pan/2.0 - 0.5);
    out[1] = out[1] * (pan/2.0 + 0.5);
    out = (out * (fx - 1.0)) + (w * fx) * EnvGen.kr(Env.asr, gate, doneAction:2);
    Out.ar(3 , out);
}).store;
)SC";
	synth.push_back(s0);

	string s1 =
		R"SC(
//SuperCollider: Moog
SynthDef("moog", {
    arg base = 40, freq = 100, gain = 1.0, mul = 1.0, detune=1.01, gate=1, pan = 0;
    var env, sig1, sig2, sig3, out;
    env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
    sig1 = MoogFF.ar(Pulse.ar([base, base*detune], 0.3), freq, gain, 0, mul);
    sig2 = MoogFF.ar(Pulse.ar([base * 3.0, base * 3.0 * detune], 0.7), freq, gain, 0, mul);
    out = (sig1 + sig2) * env;
    12.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.01),rrand(0.0, 0.01)],0.01,0.06), 1.0) });
    out = MidEQ.ar(out, 50, 0.75, 8);
    out[0] = out[0] * (pan/2.0 - 0.5);
    out[1] = out[1] * (pan/2.0 + 0.5);
    out = LeakDC.ar(out)* EnvGen.kr(Env.asr, gate, doneAction:2);
    Out.ar(3, out);
}).store;
)SC";
	synth.push_back(s1);

	string s2 =
		R"SC(
//SuperCollider: Blink
SynthDef("reso", {
    arg freq = 440, density = 0.1, gate=1, pan=0;
    var out, env;
    env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
    out = Resonz.ar(Array.fill(64, {Dust.ar(density)}),freq * [1, 2, 4, 8, 16], 0.01).sum * 10 * env;
    out = Pan2.ar(out, pan);
    out = out * EnvGen.kr(Env.asr, gate, doneAction:2);
    Out.ar(3, out);
}).store;
)SC";
	synth.push_back(s2);

	string s3 =
		R"SC(
//SuperCollider Fx: Comb
SynthDef("comb", {
    arg delaytime = 0.05;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 1.2), doneAction:2);
    out = CombL.ar(out, 1.0,  [delaytime, delaytime * 1.5], 5) * env;
    out = out.dup;
    Out.ar(12, out);
}).store;
)SC";
	synth.push_back(s3);

	string s4 =
		R"SC(
//SuperCollider Fx: Modulation
SynthDef("am", {
    arg ringFreq = 8.0;
    var modulator, env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 0.9), doneAction:2);
    modulator = SinOsc.ar([ringFreq, ringFreq * 1.01], [0, 0.5pi]);
    out = out ring1: modulator * env;
    out = out.dup;
    Out.ar(12, out);
}).store;
)SC";
	synth.push_back(s4);

	string s5 =
		R"SC(
//SuperCollider Fx: Distortion
SynthDef("distort", {
    arg gain=128, amp = 1.0;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 0.1), doneAction:2);
    out = (out*gain).softclip().dup() * env;
    Out.ar(12, out);
}).store;
)SC";
	synth.push_back(s5);

	string s6 =
		R"SC(
//SuperCollider Fx: Filter
SynthDef("distort", {
    arg gain=128, amp = 1.0;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 0.1), doneAction:2);
    out = (out*gain).softclip().dup() * env;
    Out.ar(12, out);
}).store;
)SC";
	synth.push_back(s6);

	string s7 =
		R"SC(
//SuperCollider Fx: Reverb
SynthDef("rev", {
    arg mix = 1.0, room = 20.0, damp = 0.0, amp = 1.0;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 1.5), doneAction:2);
    out = FreeVerb2.ar(out[0], out[1], mix, room, damp, amp) * env;
    Out.ar(12, out);
}).store;
)SC";
	synth.push_back(s7);

}

void DrawCode::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	int margin = ofGetWidth() / 30;
	//draw code
	ofSetColor(255);
	int n = 0;
	int s = 0;
	int i = 0;
	for (auto it = app->oscSender->cursorList.begin(); it != app->oscSender->cursorList.end(); it++) {
		n = app->objectController->floorObjects[i]->type;
		//Draw GLSL code
		ofxTuioCursor *blob = (*it);
		font.drawString(code[n], blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight() + margin);
		//n = (n + 1) % code.size();
		//Draw SuperCollider code
		ofPushMatrix();
		ofTranslate(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight());
		ofRotateZ(180);
		font.drawString(synth[n], 0, margin);
		ofPopMatrix();
		//s = (s + 1) % code.size();
		//Draw x, y pos
		font.drawString(ofToString(blob->getX()*ofGetWidth()), blob->getX()*ofGetWidth() + margin * 1.2, blob->getY()*ofGetHeight());
		font.drawString(", " + ofToString(blob->getX()*ofGetHeight()), blob->getX()*ofGetWidth() + margin*1.6, blob->getY()*ofGetHeight());
		i++;
	}
	i = 0;
	for (auto it = app->oscSender->objectList.begin(); it != app->oscSender->objectList.end(); it++) {
		n = app->objectController->floorObjects[i]->type;
		//Draw GLSL code
		ofxTuioObject *blob = (*it);
		font.drawString(code[n], blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight() + margin);
		//n = (n + 1) % code.size();
		//Draw SuperCollider code
		ofPushMatrix();
		ofTranslate(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight());
		ofRotateZ(180);
		font.drawString(synth[n], 0, margin);
		ofPopMatrix();
		//s = (s + 1) % code.size();
		//Draw x, y pos
		font.drawString(ofToString(blob->getX()*ofGetWidth()), blob->getX()*ofGetWidth() + margin * 1.2, blob->getY()*ofGetHeight());
		font.drawString(", " + ofToString(blob->getX()*ofGetHeight()), blob->getX()*ofGetWidth() + margin*1.6, blob->getY()*ofGetHeight());
		i++;
	}

	//draw length
	for (auto i = app->oscSender->cursorList.begin(); i != app->oscSender->cursorList.end(); i++) {
		for (auto j = i; j != app->oscSender->cursorList.end(); j++) {
			ofxTuioCursor *blobi = (*i);
			ofxTuioCursor *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			if (begin.distance(end) > 0) {
				ofVec2f middle = (begin + end) / 2.0;
				ofDrawCircle(middle, ofGetWidth() / 1000.0);
				font.drawString(ofToString(begin.distance(end)), middle.x + margin / 16.0, middle.y);
			}
		}
	}
	for (auto i = app->oscSender->objectList.begin(); i != app->oscSender->objectList.end(); i++) {
		for (auto j = i; j != app->oscSender->objectList.end(); j++) {
			ofxTuioObject *blobi = (*i);
			ofxTuioObject *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			if (begin.distance(end) > 0) {
				ofVec2f middle = (begin + end) / 2.0;
				ofDrawCircle(middle, ofGetWidth() / 1000.0);
				font.drawString(ofToString(begin.distance(end)), middle.x + margin / 16.0, middle.y);
			}
		}
	}
}


DrawCode::~DrawCode()
{
}
