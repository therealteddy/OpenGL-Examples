#version 330 core 
layout (location = 0) in vec3 position; 
layout (location = 1) in vec3 color; 
layout (location = 2) in vec2 tex;

out vec2 texcord;
out vec3 col;

void main() {
    gl_Position = vec4(position, 1.0f);
    texcord = tex;
    col = color;
}
