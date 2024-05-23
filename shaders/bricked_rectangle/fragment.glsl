#version 330 core 
in vec2 texcord;
in vec3 col;

out vec3 frag;
uniform sampler2D texdata;

void main() {
    frag = texture(texdata, texcord); 
}