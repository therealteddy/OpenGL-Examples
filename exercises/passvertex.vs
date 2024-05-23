#version 330 core 
layout (location = 0) in vec2 pos; 
out vec2 col;
void main() {
    gl_Position = vec4(pos, 0.0f, 1.0f);
    col = pos;
}