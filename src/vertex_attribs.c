/* 
    Query the number of vertex attributes available
*/

#include "../include/window.h"

unsigned int attribno; // >= 16
int main() {
    GLFWwindow *win = window(1, 1, " ", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    unsigned int attribno;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attribno);
    printf("%d\n", attribno);
    return 0;
}