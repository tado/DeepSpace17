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
	12.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.01),rrand(0.0, 0.01)],0.01,0.06), 0.5) });
	out = MidEQ.ar(out, 40, 0.75, 8);
	out = Limiter.ar(out, 1.0);
	out = LeakDC.ar(out).softclip();
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

SynthDef("ratio",{
	arg lpf=8000, rq=0.2,atk=0.01,rel=1.0,
	modSpeed=6.0,modMix=0.0,fx=0.3, gain=1,amp = 0.5;
	var env, ratio, n, d, p, q, mode, z, w, pul, mod,out;

	env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
	n = 64;
	ratio = 1.5;
	pul = Impulse.ar(modSpeed);
	p = FloatArray.new(3*n);
	q = FloatArray.new(3*n);
	d = 3.0;
	//mode = [0, 4, 7, 9];
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
	//4.do({
	//	w = AllpassL.ar(out, 0.2,LFNoise2.kr([rrand(0.1, 0.2),rrand(0.1, 0.2)],0.05,0.15), 2)
	//	});
	//4.do({ w = AllpassN.ar(w, 0.1,{[0.1.rand, 0.1.rand]}.dup(4), 1.0) });
	8.do({ w = AllpassL.ar(w, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.15), 2) });
	out = (out * (fx - 1.0)) + (w * fx);
	Out.ar(3 , out);
}).store;

SynthDef("fx", {
	arg in0 = 0.0, in1 = 0.0, in2 = 0.0,
	delaytime = 0.05, ringFreq = 8.0,
	distortGain = 100.0,
	mix = 0.8, room = 12.0, damp = 0.5, amp = 1.0;
	var fx0, fx1, fx2, modulator, in, out;

	in = In.ar(3, 2);
	8.do({out = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 20.0) });
	//out = FreeVerb2.ar(in[0], in[1], mix, room, damp, amp);

	fx0 = CombL.ar(out, 1.0,  [delaytime, delaytime * 1.001], 5) * 0.5;
	modulator = SinOsc.ar([ringFreq, ringFreq * 1.01], [0, 0.5pi]) * 1.5;
	fx1 = in ring1: modulator;
	fx2 = (in * distortGain).softclip * 0.5;

	out = (fx0 * in0) + (fx1 * in1) + (fx2 * in2) + out;
	out = LeakDC.ar(out);
	out = Limiter.ar(MidEQ.ar(out, 14000, 0.8, 8)) * amp;
	Out.ar(0, out);
}).store;
)