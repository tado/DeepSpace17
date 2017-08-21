uniform float time;
uniform float num;
uniform vec2  mouse;
uniform vec2  resolution;

void main(void){
    vec2 p = gl_FragCoord.xy / resolution;
    float speed = mouse.y * 80.0 + 20.0;
    float freq = mouse.x * 0.2 + 1.0;
    float r = pow(sin(p.x * 12.0 * freq + time * speed * 1.00), 1.5);
    float g = pow(sin(p.x * 12.0 * freq + time * speed * 1.01), 1.5);
    float b = pow(sin(p.x * 12.0 * freq + time * speed * 1.02), 1.5);
    float br = 0.7 / num + num * 0.01;
    gl_FragColor = vec4(r * br, g * br, b * br, 1.0);
}
