#version 330 core
in vec2 vTex;
uniform sampler2D uTexture;
uniform vec3 uAmbientScene; // e.g., vec3(0.2)
out vec4 FragColor;
void main() {
    vec3 texColor = texture(uTexture, vTex).rgb;
    FragColor = vec4(texColor * uAmbientScene, 1.0);
}
