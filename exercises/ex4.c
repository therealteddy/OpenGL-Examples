#include "../include/ext_shaders.h"
#include "../include/window.h"

float vertexdata[2 * 3] = {
    0.0f, +0.5f, 
    -0.5f, -0.5f, 
    +0.5f, -0.5f, 
};

unsigned int vbo, vao, sp;
char *vertexsource;

int main(int argc, char** argv) {
    GLFWwindow* win = window(800, 600, "Inverted triangle!", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    glClearColor(0.1, 0.6, 0.4, 1.0f);

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *) 0);
    glEnableVertexAttribArray(0);

    shader("./invert.vs", &vertexsource);
    sp = program(&vertexsource, &fragment);

    glUseProgram(sp);
    while(!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        glfwSwapBuffers(win);
    }
}