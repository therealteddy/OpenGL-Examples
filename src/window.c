#include "../include/window.h"

void cb_resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void cb_error(int code, char* error) {
    printf("Error: %d.\n %s", code, error);
}  

GLFWwindow* window(unsigned int width, unsigned int height, char *title, unsigned int major, unsigned int minor, unsigned int profile, unsigned int resizable) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile); 
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL); 
    if (!window) /* If window creation failed */ 
    {
        fprintf(stderr, "Failed to create window!\n"); 
        glfwTerminate();
        return EXIT_FAILURE;  
    }

    /* Make our window the main context */
    glfwMakeContextCurrent(window); 
    
    /* Callbacks */
    glfwSetFramebufferSizeCallback(window, cb_resize); 
    glfwSetErrorCallback(cb_error);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to load the OpenGL functions!\n"); 
        return EXIT_FAILURE;
    }

    atexit(glfwTerminate);
    return window;
}