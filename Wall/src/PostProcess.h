#pragma once
#include "ofMain.h"
#include "ofxPostProcessing.h"

class PostProcess{
public:
	PostProcess();
	void update();
	void draw();
	void resetPostProcess();
	void addObject(int id);
	void removeObject(int id);
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

	float scale;

	/*
	EdgePass::Ptr edge;
	DofPass::Ptr dof;
	FakeSSSPass::Ptr sss;
	FxaaPass::Ptr fxaa;
	VerticalTiltShifPass::Ptr vtilt;
	HorizontalTiltShifPass::Ptr htilt;
	GodRaysPass::Ptr god;
	BleachBypassPass::Ptr bleach;
    */
	//LUTPass::Ptr lut;

};

