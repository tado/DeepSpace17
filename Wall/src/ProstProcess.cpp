#include "PostProcess.h"
#include "ofApp.h"

PostProcess::PostProcess() {
	scale = 1.0;

	//Postprocessing
	post.init(ofGetWidth() / scale, ofGetHeight() / scale);
	kaleido = post.createPass<KaleidoscopePass>();
	noise = post.createPass<NoiseWarpPass>();
	rgb = post.createPass<RGBShiftPass>();
	pixel = post.createPass<PixelatePass>();
	darken = post.createPass<LimbDarkeningPass>();
	contrast = post.createPass<ContrastPass>();
	conv = post.createPass<ConvolutionPass>();
	toon = post.createPass<ToonPass>();

	resetPostProcess();

	/*
	edge = post.createPass<EdgePass>();
	dof = post.createPass<DofPass>();
	sss = post.createPass<FakeSSSPass>();
	fxaa = post.createPass<FxaaPass>();
	vtilt = post.createPass<VerticalTiltShifPass>();
	htilt = post.createPass<HorizontalTiltShifPass>();
	god = post.createPass<GodRaysPass>();
	bleach = post.createPass<BleachBypassPass>();
	*/
}

void PostProcess::update() {

}

void PostProcess::draw() {

}

void PostProcess::resetPostProcess() {
	kaleido->setEnabled(false);
	noise->setEnabled(false);
	rgb->setEnabled(false);
	pixel->setEnabled(false);
	darken->setEnabled(false);
	contrast->setEnabled(false);
	conv->setEnabled(false);
	toon->setEnabled(false);

	/*
	edge->setEnabled(false);
	dof->setEnabled(false);
	sss->setEnabled(false);
	fxaa->setEnabled(false);
	vtilt->setEnabled(false);
	htilt->setEnabled(false);
	god->setEnabled(false);
	bleach->setEnabled(false);
	//lut->setEnabled(false);
	*/
}

void PostProcess::addFx(int num) {
	int n = num;
	switch (n) {
	case 0:
		kaleido->setEnabled(true);
		break;
	case 1:
		noise->setEnabled(true);
		break;
	case 2:
		rgb->setEnabled(true);
		break;
	case 3:
		pixel->setEnabled(true);
		break;
	case 4:
		darken->setEnabled(true);
		break;
	case 5:
		contrast->setEnabled(true);
		break;
	case 6:
		conv->setEnabled(true);
		break;
	case 7:
		toon->setEnabled(true);
		break;
	}
}

void PostProcess::removeFx(int num) {
	int n = (num / 2) % 8;
	switch (n) {
	case 0:
		kaleido->setEnabled(false);
		break;
	case 1:
		noise->setEnabled(false);
		break;
	case 2:
		rgb->setEnabled(false);
		break;
	case 3:
		pixel->setEnabled(false);
		break;
	case 4:
		darken->setEnabled(false);
		break;
	case 5:
		contrast->setEnabled(false);
		break;
	case 6:
		conv->setEnabled(false);
		break;
	case 7:
		toon->setEnabled(false);
		break;
	}
}

PostProcess::~PostProcess() {
}
