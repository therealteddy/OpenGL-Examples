#version 330 core 
in vec2 col;
out vec4 fragcol;
void main() {
    fragcol = vec4(col, 0.0f, 1.0f);
}