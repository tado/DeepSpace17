#version 150

uniform float time;
uniform vec2  mouse;
uniform vec2  resolution;
uniform float num;

void main(void){
    vec2 m = vec2(mouse.x * (resolution.x / resolution.y), mouse.y);
    vec2 p = gl_FragCoord.xy / min(resolution.x, resolution.y);
    float speed =  length(vec2(0.5, 0.5) - mouse) * 10.0 + 0.001;
    float br = 1.2 / num;
    float r = pow(sin(length(m - p) * 6.0 * speed - time * 32.), 2.5);
    float g = pow(sin(length(m - p) * 6.1 * speed - time * 32.), 2.5);
    float b = pow(sin(length(m - p) * 6.2 * speed - time * 32.), 2.5);
    gl_FragColor = vec4(r * br, g * br, b * br, 1.0);
}
