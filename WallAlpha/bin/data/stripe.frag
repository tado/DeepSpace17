uniform float time;
uniform vec2  mouse;
uniform vec2  resolution;

void main(void){
    vec2 p = gl_FragCoord.xy / resolution;
    float r = pow(sin(p.y * 6.0 + time * 40.0), 4.0);
    float g = pow(sin(p.y * 6.4 + time * 40.0), 4.0);
    float b = pow(sin(p.y * 6.6 + time * 40.0), 4.0);
    gl_FragColor = vec4(r, g, b, 1.0);
}
