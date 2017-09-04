(
SynthDef("moog", {
    arg base = 40, freq = 100, gain = 1.0, mul = 1.0, detune=1.01, gate=1, pan = 0;
    var env, sig1, sig2, sig3, out;
    env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
    sig1 = MoogFF.ar(Pulse.ar([base, base*detune], 0.3), freq, gain, 0, mul);
    sig2 = MoogFF.ar(Pulse.ar([base * 3.0, base * 3.0 * detune], 0.7), freq, gain, 0, mul);
    out = (sig1 + sig2) * env;
    12.do({ out = AllpassL.ar(out, 0.1, LFNoise2.kr([rrand(0.0, 0.01),rrand(0.0, 0.01)],0.01,0.06), 1.0) });
    out = MidEQ.ar(out, 50, 0.75, 8);
    out[0] = out[0] * (pan/2.0 - 0.5);
    out[1] = out[1] * (pan/2.0 + 0.5);
    out = LeakDC.ar(out)* EnvGen.kr(Env.asr, gate, doneAction:2);
    Out.ar(3, out);
}).store;

SynthDef("reso", {
    arg freq = 440, density = 0.1, gate=1, pan=0;
    var out, env;

    env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
    out = Resonz.ar(Array.fill(64, {Dust.ar(density)}),freq * [1, 2, 4, 8, 16], 0.01).sum * 10 * env;
    out = Pan2.ar(out, pan);
    out = out * EnvGen.kr(Env.asr, gate, doneAction:2);
    Out.ar(3, out);
}).store;

SynthDef("ratio",{
    arg lpf=8000, rq=0.2,atk=0.01,rel=1.0,
    modSpeed=6.0,modMix=0.0,fx=0.3, gain=1,amp = 0.5, gate=1, pan=0;
    var env, ratio, n, d, p, q, mode, z, w, pul, mod,out;

    env = EnvGen.kr(Env.new([0,1], [2], 'sine'));
    n = 64;
    ratio = 1.5;
    pul = Impulse.ar(modSpeed);
    p = FloatArray.new(3*n);
    q = FloatArray.new(3*n);
    d = 3.0;
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
    8.do({ w = AllpassL.ar(w, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.15), 2) });
    out[0] = out[0] * (pan/2.0 - 0.5);
    out[1] = out[1] * (pan/2.0 + 0.5);
    out = (out * (fx - 1.0)) + (w * fx) * EnvGen.kr(Env.asr, gate, doneAction:2);
    Out.ar(3 , out);
}).store;

SynthDef("fx", {
    var in, out;
    in = InFeedback.ar(3, 2);
    //8.do({out = AllpassL.ar(in, 0.1, LFNoise2.kr([rrand(0.0, 0.1),rrand(0.0, 0.1)],0.01,0.06), 2.0) });
    out = FreeVerb2.ar(in[0], in[1], 0.25, 2.0, 0.5, 1.0);
    Out.ar(10, out);
}).store;

SynthDef("comb", {
    arg delaytime = 0.05;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 1.2), doneAction:2);
    out = CombL.ar(out, 1.0,  [delaytime, delaytime * 1.5], 5) * env;
    out = out.dup;
    Out.ar(12, out);
}).store;

SynthDef("am", {
    arg ringFreq = 8.0;
    var modulator, env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 0.9), doneAction:2);
    modulator = SinOsc.ar([ringFreq, ringFreq * 1.01], [0, 0.5pi]);
    out = out ring1: modulator * env;
    out = out.dup;
    Out.ar(12, out);
}).store;

SynthDef("rev", {
    arg mix = 1.0, room = 20.0, damp = 0.0, amp = 1.0;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 1.5), doneAction:2);
    out = FreeVerb2.ar(out[0], out[1], mix, room, damp, amp) * env;
    Out.ar(12, out);
}).store;

SynthDef("bpf", {
    arg freq=440, rq=0.4, amp = 1.0;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 1.2), doneAction:2);
    out = RLPF.ar(out, freq, rq).dup() * env;
    Out.ar(12, out);
}).store;

SynthDef("distort", {
    arg gain=128, amp = 1.0;
    var env, out;
    out = InFeedback.ar(3, 2);
    env = EnvGen.ar(Env.perc(0.01, 2.0, 0.1), doneAction:2);
    out = (out*gain).softclip().dup() * env;
    Out.ar(12, out);
}).store;

SynthDef("mix", {
    arg amp = 0.75, gate=1;
    var in0, in1, out;
    in0 = InFeedback.ar(10, 2); //* gate;
    in1 = InFeedback.ar(12, 2); //* (1 - gate);
    out = (in0 + in1) * amp;
    out = Compander.ar(out);
    Out.ar(0, out);
}).store;

)
