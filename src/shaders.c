#include "../include/shaders.h" 
#include <glad/glad.h>
#include <stdio.h> 

int  code; 
char errorbuffer[BUFFERSIZE];

unsigned int shader(char *shadersource[], int type) {
    unsigned int shaderid = glCreateShader((GLenum) type);
    glShaderSource(shaderid, 1, shadersource, NULL);
    glCompileShader(shaderid);
    glGetShaderiv(shaderid, GL_COMPILE_STATUS, &code); 
    if (!code) {
        glGetShaderInfoLog(shaderid, BUFFERSIZE, NULL, errorbuffer);
        printf("Errorcode = %d\n",code);
        puts(errorbuffer);
    } else {
        return shaderid;
    }
    return 0; // We assume the program never gets here
}

unsigned int shaderprogram(unsigned int nshaders, unsigned int shaderid[]) {
    unsigned int program = glCreateProgram();
    for (int i = 0; i < nshaders; ++i) {
        glAttachShader(program, shaderid[i]);
    }
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &code);
    if (!code) {
        glGetProgramInfoLog(program, BUFFERSIZE, NULL, errorbuffer);
        printf("Errorcode = %d\n", code);
        puts(errorbuffer);
    } else {
        return program;
    }
    return 0; // We assume the program never gets here
}

void deleteshaders(unsigned int nshaders, unsigned int shaderid[]) {
    for (int i = 0; i < nshaders; ++i) {
        glDeleteShader(shaderid[i]);
    }
}

/* Default shaders - the most basic */
char *vshader_basic = "#version 330 core\n" 
                      "layout (location = 0) in vec3 vertex;\n" 
                      "void main() {\n"
                           "gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0f);\n"
                       "}\n";

char *fshader_basic = "#version 330 core\n" 
                      "out vec4 color;\n" 
                      "void main() {\n"
                          "color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
                      "}\n";
