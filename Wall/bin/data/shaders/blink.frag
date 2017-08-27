#version 120

uniform vec2 resolution;
uniform vec2 mouse;
uniform float time;
uniform float num = 1.0;

float rand(float n){
  return fract(sin(n) * 43758.5453123);
}

void main() {
    vec2 st = gl_FragCoord.xy/resolution.x;
    float dist = length(vec2(0.5, 0.5) - mouse);
    float br = pow(rand(time), 50.0 + (dist * 50.0)) * 1.0;
    gl_FragColor = vec4(vec3(br), 1.0);
}
