#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "../include/shaders.h"

void cb_error(int code, char string[]) {
    printf("Code: %d ", code); 
    puts(string);
}

float vertices[3*3] = {
    +0.0, +0.5, +0.0, 
    -0.5, -0.5, +0.0, 
    +0.5, -0.5, +0.0 
};

unsigned int vbo, vao; 

int main(int argc, char* argv[]) {
    if (!glfwInit()) {
        puts("Failed to init glfw!"); 
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Rectangle!", NULL, NULL); 
    if (!window) {
        puts("Failed to create window!"); 
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        puts("Failed to load opengl function pointers!"); 
    }

    glViewport(0, 0, 800, 600);
    glGenBuffers(1, &vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glGenVertexArrays(1, &vao); 
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0); 
    glEnableVertexAttribArray(0);

    unsigned int shaders[2] = {
        BASIC_VERTEX_SHADER, 
        BASIC_FRAGMENT_SHADER, 
    };  unsigned int program = shaderprogram(sizeof(shaders), shaders);
    glUseProgram(program);
    deleteshaders(sizeof(shaders), shaders) ;

    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window); 
        glfwPollEvents();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    return EXIT_SUCCESS;
}