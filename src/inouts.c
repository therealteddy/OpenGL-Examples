#include "../include/shaders.h"
#include "../include/window.h"

char *frag, *vrtx;
unsigned int prog;

float vertexdata[4 * 3] = {
    -0.5f, +0.5f, 0.0f, 
    +0.5f, +0.5f, 0.5f, 
    +0.5f, -0.5f, 0.5f, 
    -0.5f, -0.5f, 0.5f
};

unsigned int indices[6] = {
    0, 1, 2, 
    2, 3, 0
};

unsigned int vbo, ebo, vao;

int main(int argc, char* argv[]) {
    GLFWwindow* win = window(800, 600, "Color out vs!", 3, 3, GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
    glClearColor(0.5f, 0.1f, 0.2f, 1.0f);

    unsigned int shaders[2] = {
        shader(&frag, GL_FRAGMENT_SHADER),
        shader(&vrtx, GL_VERTEX_SHADER),
    };  glUseProgram((prog = program(2, shaders)));

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) 0);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    return EXIT_SUCCESS;
}

char *frag =  "#version 330 core\n" 
        "in vec4 vscolor;\n" 
        "out vec4 fragcolor; //The color spit out by the fs\n" 
        "void main() {"
        "   fragcolor = vec4(vscolor.rgb, 1.0f);\n"
        "}\n";

char *vrtx =    "#version 330 core\n" 
                "layout (location = 0) in vec3 position;\n" 
                "out vec4 vscolor;"
                "void main() {\n"
                    "gl_Position = vec4(position.xyz, 1.0f);\n"
                    "vscolor = vec4(1.0f, 0.5f, 0.25f, 1.0f);\n"
                "}\n";