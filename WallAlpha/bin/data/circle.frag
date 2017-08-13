uniform float time;
uniform vec2  mouse;
uniform vec2  resolution;

void main(void){
    vec2 m = vec2(mouse.x, mouse.y);
    vec2 p = (gl_FragCoord.xy * 2. - resolution) / min(resolution.x, resolution.y);
    float speed = abs(sin(time / 1000.)) + 1.0;
    float r = pow(sin(length(m - p) * 6.0 - time * 50.), 3.0);
    float g = pow(sin(length(m - p) * 6.4 - time * 50.), 3.0);
    float b = pow(sin(length(m - p) * 6.8 - time * 50.), 3.0);
    gl_FragColor = vec4(r, g, b, 1.0);
}
