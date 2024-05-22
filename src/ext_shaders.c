#include "../include/ext_shaders.h" 

int code; 
char errorbuffer[ERRORBUFFER];

void shader(char *path, char **dest) {
    FILE* file; 
    unsigned int size;
    if (!(file = fopen(path, "r"))) {
        printf("Failed to open %s\n", path);
        return;
    }

    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fclose(file);
    file = fopen(path, "r"); 
    
    *dest = malloc(size);
    if (!fread(*dest, sizeof(char), size, file)) {
        printf("Failed to read %s!\n", path);
        free(*dest);
        return;
    }
}

unsigned int program(char *vertexshader, char *fragmentshader) {
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vs, 1, vertexshader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &code);
    if (!code) {
        glGetShaderInfoLog(vs, ERRORBUFFER, NULL, errorbuffer);
        printf("Failed to compile vertex shader!\n"); 
        puts(errorbuffer);
        return 0;
    }

    unsigned int fs = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(fs, 1, fragmentshader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &code);
    if (!code) {
        glGetShaderInfoLog(fs, ERRORBUFFER, NULL, errorbuffer);
        printf("Failed to compile fragment shader!\n"); 
        puts(errorbuffer);
        return 0;
    }

    unsigned int sp = glCreateProgram(); 
    glAttachShader(sp, vs);
    glAttachShader(sp, fs);
    glLinkProgram(sp);
    glGetProgramiv(sp, GL_LINK_STATUS, &code); 
    if (!code) {
        glGetProgramInfoLog(sp, ERRORBUFFER, NULL, errorbuffer);
        printf("Failed to link shader program!\n");
        puts(errorbuffer);
        return 0;
    }

    return sp; // The program returns sp if nothing went wrong.
}

unsigned int uniform_bool(unsigned int prog, char* name, bool value) {
    glUniform1i(glGetUniformLocation(prog, name), value);
}

unsigned int uniform_int(unsigned int prog, char* name, int value) {
    glUniform1i(glGetUniformLocation(prog, name), value);
}

unsigned int uniform_float(unsigned int prog, char* name, float value) {
    glUniform1f(glGetUniformLocation(prog, name), value);
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
