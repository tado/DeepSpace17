(
SynthDef("ping", {
	arg freq = 440, mul = 0.1, detune=1.01, pan=0.0;
	var out;
	out = SinOsc.ar([freq, freq*detune], 0, mul) * EnvGen.kr(Env.perc(), doneAction:1);
	out = Pan2.ar(out, pan);
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
	signal = Limitter.ar(In.ar(0, 2), 1.0);
    ReplaceOut.ar(0, FreeVerb2.ar(signal[0], signal[1], mix, room, damp, amp));
}).store;
)

a = Synth("reverb");

e = Synth("reso", ["freq", 60]);

b = Synth("reso", ["freq", 80]);

c = Synth("reso", ["freq", 120]);

d = Synth("reso", ["freq", 180]);




a.free;
b.free;
c.free;


(
SynthDef(\test, {
	arg roomsize = 80, revtime = 5.0, damping=0.4, inputbw=0.2, spread = 15, drylevel=-3, earlylevel=-9, taillevel = -11;
    var a = Resonz.ar(
        Array.fill(4, {Dust.ar(2)}), 800 * [1, 2, 4, 8, 15, 32], 0.01).sum * 10;
//    var a = SoundIn.ar(0);
//    var a = PlayBuf.ar(1, 0);
    Out.ar(0, GVerb.ar(
        a,
        roomsize,
        revtime,
        damping,
        inputbw,
        spread,
        drylevel.dbamp,
        earlylevel.dbamp,
        taillevel.dbamp,
        roomsize, 0.3) + a)}).add
)

s.boot;
s.scope(2);

// bathroom
a = Synth(\test, [\roomsize, 5, \revtime, 0.6, \damping, 0.62, \inputbw, 0.48, \drylevel -6, \earlylevel, -11, \taillevel, -13]);
a.free;

//living room
a = Synth(\test, [\roomsize, 16, \revtime, 1.24, \damping, 0.10, \inputbw, 0.95, \drylevel -3, \earlylevel, -15, \taillevel, -17]);
a.free;

//church
a = Synth(\test, [\roomsize, 80, \revtime, 4.85, \damping, 0.41, \inputbw, 0.19, \drylevel -3, \earlylevel, -9, \taillevel, -11]);
a.free;

// cathedral
a = Synth(\test, [\roomsize, 243, \revtime, 1, \damping, 0.1, \inputbw, 0.34, \drylevel -3, \earlylevel, -11, \taillevel, -9]);
a.free

// canyon
a = Synth(\test, [\roomsize, 300, \revtime, 103, \damping, 0.43, \inputbw, 0.51, \drylevel -5, \earlylevel, -26, \taillevel, -20]);
a.free;

s.quit;

// ... whereas Pan2 is more smooth
{Pan2.ar(SinOsc.ar(440), Line.kr(-1,1,5))}.play