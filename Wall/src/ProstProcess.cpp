#include "PostProcess.h"
#include "ofApp.h"

PostProcess::PostProcess() {
	scale = 1.0;

	//Postprocessing
	post.init(ofGetWidth() / scale, ofGetHeight() / scale);

	kaleido = post.createPass<KaleidoscopePass>();
	noise = post.createPass<NoiseWarpPass>();
	pixel = post.createPass<PixelatePass>();
	darken = post.createPass<LimbDarkeningPass>();
	toon = post.createPass<ToonPass>();
	contrast = post.createPass<ContrastPass>();
	edge = post.createPass<EdgePass>();

	/*
	god = post.createPass<GodRaysPass>();
	conv = post.createPass<ConvolutionPass>();
	edge = post.createPass<EdgePass>();
	dof = post.createPass<DofPass>();
	sss = post.createPass<FakeSSSPass>();
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
	darken->setEnabled(false);
	toon->setEnabled(false);	
	contrast->setEnabled(false);
	edge->setEnabled(false);

	/*
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

void PostProcess::addFx(int num) {
	resetPostProcess();
	int n = num;
	switch (n) {
	case 0:
		kaleido->setEnabled(true);
		break;
	case 1:
		noise->setEnabled(true);
		break;
	case 2:
		pixel->setEnabled(true);
		break;
	case 3:
		darken->setEnabled(true);
		break;
	case 4:
		toon->setEnabled(true);
		break;
	case 5:
		contrast->setEnabled(true);
		break;
	case 6:
		edge->setEnabled(true);
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

PostProcess::~PostProcess() {
}
