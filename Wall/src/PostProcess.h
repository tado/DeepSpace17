#pragma once
#include "ofMain.h"
#include "ofxPostProcessing.h"
#include "ofxSuperCollider.h"

class PostProcess{
public:
	PostProcess();
	void update();
	void draw();
	void resetPostProcess();
	void addFx(int num);
	void deleteFx();
	void updateFx(int type, ofVec2f pos);
	~PostProcess();

	//postprocess
	ofxPostProcessing post;
	KaleidoscopePass::Ptr kaleido;
	NoiseWarpPass::Ptr noise;
	RGBShiftPass::Ptr rgb;
	LimbDarkeningPass::Ptr darken;
	PixelatePass::Ptr pixel;
	ToonPass::Ptr toon;
	ConvolutionPass::Ptr conv;
	ContrastPass::Ptr contrast;
	EdgePass::Ptr edge;
	DofPass::Ptr dof;
	FakeSSSPass::Ptr sss;
	FxaaPass::Ptr fxaa;
	VerticalTiltShifPass::Ptr vtilt;
	HorizontalTiltShifPass::Ptr htilt;
	GodRaysPass::Ptr god;
	BleachBypassPass::Ptr bleach;
	//LUTPass::Ptr lut;

	float scale;

	ofxSCSynth * synth;
	ofxSCSynth *comb;
	bool playSynth;
};

