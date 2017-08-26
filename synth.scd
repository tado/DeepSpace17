(
SynthDef("sine", {
	arg freq = 440, mul = 0.5, detune=1.01, lfo=4.0;
	var out, mod;
	mod = SinOsc.ar(lfo, 0, 0.4, 0.5);
	out = SinOsc.ar([freq, freq*detune], 0, mul * mod);
	Out.ar(3, out);
}).store;

SynthDef("moog", {
	arg base = 40, freq = 100, gain = 1.0, mul = 1.0, detune=1.01;
	var sig1, sig2, sig3, out;
	sig1 = MoogFF.ar(Pulse.ar([base, base*detune], 0.3), freq, gain, 0, mul);
	sig2 = MoogFF.ar(Pulse.ar([base * 3.0, base * 3.0 * detune], 0.7), freq, gain, 0, mul);
	out = sig1 + sig2;
	out = LeakDC.ar(out);
	//12.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.01),rrand(0.0, 0.01)],0.01,0.06), 0.5) });
	//out = Limiter.ar(out, 0.8);
	//out = out.softclip();
	Out.ar(3, out);
}).store;

SynthDef("reso", {
	arg freq = 440, density = 0.1;
	var a = Resonz.ar(Array.fill(64, {Dust.ar(density)}),
		freq * [1, 2, 4, 8, 16, 32, 64], 0.01).sum * 60;
	a = Limiter.ar(Pan2.ar(a, LFNoise0.kr(2)), 0.8);
	Out.ar(3, a);
}).store;

SynthDef("reverb", {
	arg outbus, mix = 0.8, room = 8.0, damp = 0.5, amp = 1.0;
	var signal, out;
	signal = Limiter.ar(In.ar(3, 2), 1.0);
	//ReplaceOut.ar(0, FreeVerb2.ar(signal[0], signal[1], mix, room, damp, amp));
	out = FreeVerb2.ar(signal[0], signal[1], mix, room, damp, amp);
	out = LeakDC.ar(out);
	/*
	out = Compander.ar(out, out,
		thresh:0.1,
		slopeBelow: 1,
		slopeAbove: 0.5,
		clampTime: 0.01,
		relaxTime: 0.01,
		mul: 1.0);
	*/
	out = Limiter.ar(MidEQ.ar(out, 14000, 0.7, 8));
	Out.ar(5, out);
}).store;

SynthDef("comb", {
	arg inamp = 0.0, amp = 0.5, delaytime = 0.05;
	var out;
	out = In.ar(5, 2) * inamp;
	out = CombL.ar(out, 1.0,  delaytime, 5);
	//in = Pan2.ar(in, LFNoise0.kr(1));
	//out = out * amp;
	out = Limiter.ar(MidEQ.ar(out, 14000, 0.7, 8)) * amp;
	Out.ar(0, out);
}).store;
)