#version 330

out vec4 fragColor;

void main() {
    float b = (sin(20 * gl_FragCoord.x / 1920) + 1.0) / 2.0;
    fragColor = vec4(0.5, 0.0, b/2, 1.0);
}
