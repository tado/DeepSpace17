#include "PostProcess.h"
#include "ofApp.h"

PostProcess::PostProcess() {
	scale = 1.0;
	playSynth = false;

	synth = new ofxSCSynth("fx");
	synth->create(0, 0);

	//Postprocessing
	post.init(ofGetWidth() / scale, ofGetHeight() / scale);

	kaleido = post.createPass<KaleidoscopePass>();
	noise = post.createPass<NoiseWarpPass>();
	pixel = post.createPass<PixelatePass>();
	darken = post.createPass<LimbDarkeningPass>();
	toon = post.createPass<ToonPass>();
	contrast = post.createPass<ContrastPass>();
	sss = post.createPass<FakeSSSPass>();

	/*
	edge = post.createPass<EdgePass>();
	god = post.createPass<GodRaysPass>();
	conv = post.createPass<ConvolutionPass>();
	edge = post.createPass<EdgePass>();
	dof = post.createPass<DofPass>();
	vtilt = post.createPass<VerticalTiltShifPass>();
	htilt = post.createPass<HorizontalTiltShifPass>();
	fxaa = post.createPass<FxaaPass>();
	rgb = post.createPass<RGBShiftPass>();
	god = post.createPass<GodRaysPass>();
	bleach = post.createPass<BleachBypassPass>();
	*/

	resetPostProcess();
}

void PostProcess::update() {

}

void PostProcess::draw() {

}

void PostProcess::resetPostProcess() {
	kaleido->setEnabled(false);
	noise->setEnabled(false);
	pixel->setEnabled(false);
	toon->setEnabled(false);	
	contrast->setEnabled(false);
	sss->setEnabled(false);

	darken->setEnabled(true);

	/*
	edge->setEnabled(false);
	conv->setEnabled(false);
	dof->setEnabled(false);
	sss->setEnabled(false);
	fxaa->setEnabled(false);
	vtilt->setEnabled(false);
	htilt->setEnabled(false);
	god->setEnabled(false);
	bleach->setEnabled(false);
	fxaa->setEnabled(false);
	rgb->setEnabled(false);
	*/
	//lut->setEnabled(false);

}
void PostProcess::updateFx(int type, ofVec2f pos) {
	float length = pos.distance(ofVec2f(0.5, 0.5));
	switch (type) {
	case 0:
		kaleido->setSegments(length * 10.0);
		break;
	case 1:
		noise->setAmplitude(length * 0.5);
		break;
	case 2:
		//toon->setLevel(length * 10.0);
		break;
	case 3:
		darken->setBrightness(length*10.0);
		break;
	case 4:
		pixel->resolution = ofVec2f((1.0 - pos.x) * 40.0, (1.0 - pos.y) * 40.0);
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
}

void PostProcess::addFx(int num) {
	resetPostProcess();
	int n = num;
	switch (n) {
	case 0:
		kaleido->setEnabled(true);
		if (!playSynth) {
			//deleteFx();
			ofxSCSynth *fx = new ofxSCSynth("comb");
			fx->create(0, 0);
			fx->set("delaytime", ofRandom(0.01, 0.06));
			playSynth = true;
		}
		break;
	case 1:
		noise->setEnabled(true);
		if (!playSynth) {
			ofxSCSynth *fx = new ofxSCSynth("am");
			fx->create(0, 0);
			playSynth = true;
		}
		break;
	case 2:
		toon->setEnabled(true);
		toon->setLevel(4.0);
		if (!playSynth) {
			ofxSCSynth *fx = new ofxSCSynth("rev");
			fx->create(0, 0);
			playSynth = true;
		}
		break;
	case 3:
		darken->setEnabled(true);
		break;
	case 4:
		pixel->setEnabled(true);
		break;
	case 5:
		contrast->setEnabled(true);
		break;
	case 6:
		sss->setEnabled(true);
		break;
	/*
	case 7:
		contrast->setEnabled(true);
		break;
	case 8:
		edge->setEnabled(true);
		break;
	case 10:
		sss->setEnabled(true);
		break;
	case 11:
		fxaa->setEnabled(true);
		break;
	case 12:
		vtilt->setEnabled(true);
		break;
	case 13:
		htilt->setEnabled(true);
		break;
	case 14:
		god->setEnabled(true);
		break;
	case 15:
		bleach->setEnabled(true);
		break;
	 */
	}
}

void PostProcess::deleteFx() {
	if (playSynth) {
		synth->set("in0", 0.0);
		synth->set("in1", 0.0);
		synth->set("in2", 0.0);
		playSynth = false;
	}
}

PostProcess::~PostProcess() {
}
