uniform float time;
uniform vec2  mouse;
uniform vec2  resolution;

void main(void){
    vec2 m = vec2(mouse.x * (resolution.x / resolution.y), mouse.y);
    //vec2 p = (gl_FragCoord.xy * 2. - resolution) / min(resolution.x, resolution.y);
    vec2 p = gl_FragCoord.xy / min(resolution.x, resolution.y);
    //vec2 p = gl_FragCoord.xy/ resolution.xy;
    float speed =  length(vec2(0.5, 0.5) - mouse) * 12.0 + 2.0;
    float br = (1.0 - length(vec2(0.5, 0.5) - mouse)) * 0.3;
    float r = pow(sin(length(m - p) * 6.0 * speed - time * 50.), 2.0);
    float g = pow(sin(length(m - p) * 6.4 * speed - time * 50.), 2.0);
    float b = pow(sin(length(m - p) * 6.8 * speed - time * 50.), 2.0);
    gl_FragColor = vec4(r * br, g * br, b * br, 1.0);
}
