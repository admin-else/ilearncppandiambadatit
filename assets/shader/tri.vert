#version 330

layout (location = 0) in vec3 pos;

out vec4 color;

void main() {
    gl_Position = vec4(pos.x, pos.y, pos.z, 1);
    color = vec4(pos.xy + vec2(.5,.5), 0, 1);
}
