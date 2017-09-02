#include "PostProcess.h"
#include "ofApp.h"

PostProcess::PostProcess() {
	scale = 1.0;
	playSynth = false;
	currentFx = -1;

	fx = new ofxSCSynth("fx");
	fx->create(0, 0);

	mix = new ofxSCSynth("mix");
	mix->create(0, 0);

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

void PostProcess::addFx(int type, int id) {
	resetPostProcess();
	switch (type) {
	case 0:
		kaleido->setEnabled(true);
		break;
	case 1:
		noise->setEnabled(true);
		break;
	case 2:
		toon->setEnabled(true);
		toon->setLevel(4.0);
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

	if (id != currentFx) {
		ofxSCSynth *fx;
		switch (type) {
		case 0:
			fx = new ofxSCSynth("comb");
			fx->set("delaytime", ofRandom(0.01, 0.06));
			fx->create(0, 0);
			break;
		case 1:
			fx = new ofxSCSynth("am");
			fx->set("ringFreq", ofRandom(6.0, 10.0));
			fx->create(0, 0);
			break;
		case 2:
			fx = new ofxSCSynth("rev");
			fx->create(0, 0);
			break;
		}
		currentFx = id;
	}
}

void PostProcess::deleteFx() {
	currentFx = -1;
}

PostProcess::~PostProcess() {
}
