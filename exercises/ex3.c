/*
    Author: Ted Jerin 
    Date: 21-05-24
    Desc. Render two triangles with different shader programs
*/

#include "../include/window.h"
#include "../include/shaders.h"

float triangles[3 * 6] = {
    -0.5f, +0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f, 
    +0.5f, +0.5f, 0.0f, 
    +0.5f, +0.5f, 0.0f, 
    +0.5f, -0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f, 
};

unsigned int vbo, vao;
unsigned int lsp, rsp;
char *yellow;

int main(int argc, char *argv[]) {
    GLFWwindow* win = window(800, 600, "Exercise 3 - Rectangle with different colors", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    glClearColor(0.0f, 0.25f, 0.25f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glGenVertexArrays(1, &vao); 
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao); 
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); 
    glEnableVertexAttribArray(0);

    // Spit out white
    unsigned int rshaders[2] = {
        shader(&vertex, GL_VERTEX_SHADER), 
        shader(&fragment, GL_FRAGMENT_SHADER),
    }; lsp = program(2, rshaders);

     unsigned int lshaders[2] = {
        shader(&vertex, GL_VERTEX_SHADER), 
        shader(&yellow, GL_FRAGMENT_SHADER),
    }; rsp = program(2, lshaders);
    

    while (!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Left Triangle 
        glUseProgram(lsp);
        glDrawArrays(GL_TRIANGLES, 0, 3); 
        // Right Triangle 
        glUseProgram(rsp);
        glDrawArrays(GL_TRIANGLES, 3, 5); 

        glfwSwapBuffers(win); 
        glfwPollEvents();
    }

    rmshaders(2, lshaders); 
    rmshaders(2, rshaders);
    glDeleteProgram(lsp);
    glDeleteProgram(rsp);
    glfwTerminate();
    return 0;
}

char *yellow          = "#version 330 core\n" 
                      "out vec4 color;\n" 
                      "void main() {\n"
                          "color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                      "}\n";
