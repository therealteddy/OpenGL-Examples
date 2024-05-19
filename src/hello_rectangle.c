#include "../include/window.h" 
#include "../include/shaders.h" 

int main(int argc, char** argv) {
    GLFWwindow* Window = window(800, 600, "Hello Rectangle!", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    glClearColor(0.33f, 0.25f, 0.75f, 1.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float vertices[4 * 3] = {
        -0.5f, +0.5f, +0.0f, // 0 tl
        +0.5f, +0.5f, +0.0f, // 1 tr
        -0.5f, -0.5f, +0.0f, // 2 br
        +0.5f, -0.5f, +0.0f, // 3 bl
    };

    unsigned int indices[2 * 3] = {
        0, 1, 2, // Left Rectangle 
        1, 3, 2, // Right Rectangle
    };

    unsigned int vbo, vao, ebo; 
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
    glEnableVertexAttribArray(0);
    
    unsigned int shaders[2] = {
        shader(&vertex, GL_VERTEX_SHADER),
        shader(&fragment, GL_FRAGMENT_SHADER), 
    };  glUseProgram(program(2, shaders));

    while(!glfwWindowShouldClose(Window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
}