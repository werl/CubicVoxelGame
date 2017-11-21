#version 410 core

layout(location = 0) in vec3 vertex;

// offset from origin
uniform vec3 position;

// where to render according to camera location
uniform mat4 MVP;

void main() {
    gl_Position = MVP * (vec4(vertex, 1) + vec4(position, 1));
}
