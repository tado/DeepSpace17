(
SynthDef("sine", {
	arg freq = 440, mul = 0.5, detune=1.01;
	var out;
	out = SinOsc.ar([freq, freq*detune], 0, mul);
	Out.ar(0, out);
}).store;

SynthDef("reso", {
	arg freq = 440, density = 0.1;
    var a = Resonz.ar(Array.fill(64, {Dust.ar(density)}),
		freq * [1, 2, 4, 8, 16, 32, 64], 0.01).sum * 60;
	a = Limiter.ar(Pan2.ar(a, LFNoise0.kr(2)), 0.8);
	Out.ar(0, a);
}).store;

SynthDef("reverb", {
	arg outbus, mix = 0.25, room = 2.0, damp = 0.5, amp = 1.0;
    var signal;
	signal = Limiter.ar(In.ar(0, 2), 1.0);
    ReplaceOut.ar(0, FreeVerb2.ar(signal[0], signal[1], mix, room, damp, amp));
}).store;
)

a = Synth("reverb");

e = Synth("reso", ["freq", 60]);

b = Synth("reso", ["freq", 80]);

c = Synth("reso", ["freq", 120]);

d = Synth("reso", ["freq", 180]);

a.free;