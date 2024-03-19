// fragment shader
uniform sampler2D texture;
varying vec2 texcoord;
void main() {
    vec4 color = texture2D(texture, texcoord);
    vec4 glowColor = vec4(1.0, 1.0, 0.0, 0.5); // Цвет свечения (желтый, например)
    gl_FragColor = color + glowColor * 0.5; // Настройте интенсивность свечения
}