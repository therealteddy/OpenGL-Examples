#version 330 core 
layout (location = 0) in vec2 pos;
uniform vec2 offset;
void main() {
    gl_Position = vec4(pos.x + offset.x, pos.y + offset.y, 0.0f, 1.0f);
}