#version 410 core

layout(location = 0) in vec3 vertex;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertex, 1);
}
