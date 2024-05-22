/*
    Author: Ted Jerin
    Date: 21-05-24
    Desc. Draw two triangles using two different vaos and vbos
*/

#include "../include/window.h"
#include "../include/shaders.h"

float left[3 * 3] = {
    -0.5f, +0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f, 
    +0.5f, +0.5f, 0.0f, 
};

float right[3 * 3] = {
    +0.5f, +0.5f, 0.0f, 
    +0.5f, -0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f, 
};

unsigned int rvbo, rvao, rsp, lsp, lvbo, lvao;

int main(int argc, char *argv[]) {
    GLFWwindow* win = window(800, 600, "Exercise 2 - Rectangles with different VBOs", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    glClearColor(0.1f, 0.65f, 0.43f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenBuffers(1, &rvbo); 
    glGenVertexArrays(1, &rvao);
    glBindVertexArray(rvao);

    glBindBuffer(GL_ARRAY_BUFFER, rvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(left), (float*) left, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
    glEnableVertexAttribArray(0);

    unsigned int lshaders[2] = {
        shader(&vertex, GL_VERTEX_SHADER), 
        shader(&fragment, GL_FRAGMENT_SHADER), 
    };  lsp = program(2, lshaders);

    glGenBuffers(1, &lvbo); 
    glGenVertexArrays(1, &lvao);
    glBindVertexArray(lvao);

    glBindBuffer(GL_ARRAY_BUFFER, lvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(right), (float*) right, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
    glEnableVertexAttribArray(0);

    unsigned int rshaders[2] = {
        shader(&vertex, GL_VERTEX_SHADER), 
        shader(&fragment, GL_FRAGMENT_SHADER),
    }; rsp = program(2, rshaders);


    while (!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the left triangle
        glUseProgram(lsp);
        glBindVertexArray(lvao);
        glDrawArrays(GL_TRIANGLES, 0, 3); 

        // Draw the right triangle
        glUseProgram(rsp);
        glBindVertexArray(rvao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win); 
        glfwPollEvents();
    }

    rmshaders(2, lshaders); 
    glDeleteProgram(lsp);
    glfwTerminate();
    return 0;
}