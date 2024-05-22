#include "../include/window.h"
#include "../include/shaders.h"

char *vrtx = "#version 330 core\n" 
             "layout (location = 0) in vec3 pos;\n" 
             "void main() {\n" 
                "gl_Position = vec4(pos, 1.0f);\n" 
            "}\n"; 
        
char* frag = "#version 330 core\n" 
             "out vec4 color;\n"
             "uniform vec4 timegrad;\n"
             "void main() {\n" 
                "color = timegrad;\n"
            "}\n";

unsigned int vbo, ebo, vao, sp, ul;
unsigned int gradientcolor;

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

int main(int argc, char **agrv) {
    GLFWwindow *win = window(800, 600, "Fadeout Rectangle!", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);

    glGenBuffers(1, &vbo); 
    glGenBuffers(1, &ebo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
    glEnableVertexAttribArray(0);

    unsigned int shaders[2] = {
        shader(&vrtx, GL_VERTEX_SHADER), 
        shader(&frag, GL_FRAGMENT_SHADER),
    };  glUseProgram((sp = program(2, shaders)));

    ul = glGetUniformLocation(sp, "timegrad");

    while(!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT); 
        glUniform4f(ul, 0.0f, _abs_(sin(glfwGetTime())), 0.0f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) 0);
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    return EXIT_SUCCESS;
}