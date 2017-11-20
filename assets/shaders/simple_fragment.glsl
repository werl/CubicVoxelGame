#version 410 core

uniform vec3 fragColor;

out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1);
}
