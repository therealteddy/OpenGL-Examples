#include "../include/window.h" 
#include "../include/shaders.h"

char *vrtx = "#version 330 core\n"
             "layout (location = 0) in vec3 pos;\n"
             "layout (location = 1) in vec3 col;\n"
             "out vec3 frag;\n"
             "void main() {\n"  
                "gl_Position = vec4(pos, 1.0f);\n"
                "frag = col;\n"
            "}\n"; 

char *frag = "#version 330 core\n"
             "in vec3 frag;\n" 
             "out vec3 outcol;"
             "void main() {\n" 
                "outcol = frag;\n"
            "}\n";
 
float vertexdata[6 * 3] = {
    +0.0f, +0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
    +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int vbo, vao, sp;

int main(int argc, char** argv) {
    GLFWwindow* win = window(800, 600, "Rainbow Triangle", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    glClearColor(0, 0, 0, 1.0f);

    glGenBuffers(1, &vbo); 
    glGenVertexArrays(1, &vao); 
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3);
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1);

    unsigned int shaders[2] = {
        shader(&vrtx, GL_VERTEX_SHADER), 
        shader(&frag, GL_FRAGMENT_SHADER),
    };  glUseProgram((sp = program(2, shaders)));

    while(!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(win); 
        glfwPollEvents();
    }
    return EXIT_SUCCESS;
}