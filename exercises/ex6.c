#include "../include/ext_shaders.h"
#include "../include/window.h"

unsigned int vbo, vao, sp;

float vertexdata[2 * 3] = {
    +0.0f, +0.5f, 
    -0.5f, -0.5f, 
    +0.5f, -0.5f, 
};

char *vertexsource = "#version 330 core\n" 
                     "layout (location = 0) in vec2 pos;\n" 
                     "out vec4 col;\n"
                     "void main() {\n" 
                        "gl_Position = vec4(pos, 0.0f, 1.0f);\n"
                        "col = vec4(pos, 0.0f, 1.0f);\n"
                    "}\n";
char *fragmentsource = "#version 330 core\n" 
                       "in vec4 col;\n"
                       "out vec4 frag;\n"
                       "void main() {\n"
                            "frag = col;\n"
                        "}\n";

char* vrtx; 
char* frag;

int main(int argc, char** argv) {
    GLFWwindow* win = window(800, 600, "Vertex Color", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE); 
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *) 0);
    glEnableVertexAttribArray(0);

    shader("./passvertex.vs", &vrtx);
    shader("./colorvertex.fs", &frag);
    sp = program(&vrtx, &frag);
    glUseProgram(sp);

    while(!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT); 
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        glfwSwapBuffers(win);
    }
}

/* Once you managed to do this; try to answer the following
 question: why is the bottom-left side of our triangle black? */ 
// Its black because all the negative values output from the fragment shader is taken as 0 i think.