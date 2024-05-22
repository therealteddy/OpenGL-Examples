/*
    Author: Ted Jerin 
    Date: 21-05-24
    Desc. Render two triangles using the same vbo by calling glDrawArrays() twice
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

unsigned int sp, vbo, vao;

int main(int argc, char *argv[]) {
    GLFWwindow* win = window(800, 600, "Exercise 1 - Rectangles with one VBOs", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    glClearColor(0.1f, 0.65f, 0.43f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glGenVertexArrays(1, &vao); 
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao); 
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); 
    glEnableVertexAttribArray(0);

    unsigned int rshaders[2] = {
        shader(&vertex, GL_VERTEX_SHADER), 
        shader(&fragment, GL_FRAGMENT_SHADER),
    }; sp = program(2, rshaders);


    while (!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3); // Left Triangle 
        glDrawArrays(GL_TRIANGLES, 3, 5); // Right Triangle 
        glfwSwapBuffers(win); 
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}