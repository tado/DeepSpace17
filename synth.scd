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
	var env, sig1, sig2, sig3, out;

	env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
	sig1 = MoogFF.ar(Pulse.ar([base, base*detune], 0.3), freq, gain, 0, mul);
	sig2 = MoogFF.ar(Pulse.ar([base * 3.0, base * 3.0 * detune], 0.7), freq, gain, 0, mul);
	out = (sig1 + sig2) * env;
	out = MidEQ.ar(out, 50, 0.8, 12);
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

SynthDef("fx", {
	arg in0 = 0.0, in1 = 0.0, in2 = 0.0,
	delaytime = 0.05,
	mix = 0.8, room = 12.0, damp = 0.5, amp = 1.0;
	var fx0, fx1, fx2, in, out;

	in = In.ar(3, 2);
	8.do({out = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 20.0) });
	//out = FreeVerb2.ar(in[0], in[1], mix, room, damp, amp);

	fx0 = CombL.ar(out, 1.0,  [delaytime, delaytime * 1.001], 5) * 0.35;
	fx1 = out * SinOsc.ar([8.0, 8.1], 0, 0.49, 0.5) * 1.5;

	out = (fx0 * in0) + (fx1 * in1) + out;
	out = LeakDC.ar(out);
	out = Limiter.ar(MidEQ.ar(out, 14000, 0.8, 8)) * amp;
	Out.ar(0, out);
}).store;
)