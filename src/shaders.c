#include "../include/shaders.h" 

int code; 
char errorbuffer[ERRORBUFFER];

unsigned int shader(char **source, int type) {
    int shader = glCreateShader(type); 
    glShaderSource(shader, 1, source, NULL);
    glCompileShader(shader); 
    glGetShaderiv(shader, GL_COMPILE_STATUS, &code);

    if (!code) {
        glGetShaderInfoLog(shader, ERRORBUFFER, NULL, errorbuffer);

        puts(errorbuffer);
        return 0;
    }   else return shader;
}


unsigned int program(unsigned int nshaders, unsigned int shaders[]) {
    unsigned int program = glCreateProgram();
    for (int i = 0; i < nshaders; i++) {
        glAttachShader(program, shaders[i]);
    }   glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &code);
    if (!code) {
        glGetProgramInfoLog(program, ERRORBUFFER, NULL, errorbuffer);

        puts(errorbuffer);
        return 0;
    }   else return program;
}

/* Default shaders - the most basic */
char *vertex        = "#version 330 core\n" 
                      "layout (location = 0) in vec3 vertex;\n" 
                      "void main() {\n"
                           "gl_Position = vec4(vertex, 1.0f);\n"
                       "}\n";

char *fragment      = "#version 330 core\n" 
                      "out vec4 color;\n" 
                      "void main() {\n"
                          "color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                      "}\n";
