(
SynthDef("sine", {
	arg freq = 440, mul = 0.5, detune=1.01;
	var out;
	out = SinOsc.ar([freq, freq*detune], 0, mul);
	Out.ar(0, out);
}).store;

SynthDef("moog", {
	arg base = 40, freq = 100, gain = 1.0, mul = 0.5, detune=1.01;
	var out;
	out = MoogFF.ar(Pulse.ar([base, base*3.03], [0.3, 0.7]), freq, gain);
	8.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.01),rrand(0.0, 0.01)],0.01,0.06), 2.0) });
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
	arg outbus, mix = 0.4, room = 4.0, damp = 0.5, amp = 1.0;
    var signal;
	signal = Limiter.ar(In.ar(0, 2), 1.0);
    ReplaceOut.ar(0, FreeVerb2.ar(signal[0], signal[1], mix, room, damp, amp));
}).store;
)

a = Synth("reverb");

e = Synth("moog");

b = Synth("reso", ["freq", 80]);

c = Synth("reso", ["freq", 120]);

d = Synth("reso", ["freq", 180]);

a.free;

(
x = {
	f = 40;
    MoogFF.ar(
        Pulse.ar([f, f*3.02], [0.3,0.7]),
		        MouseY.kr(50, 20000, 1),
		MouseX.kr(1.0, 3.5))}.play(s);
)

x.free;