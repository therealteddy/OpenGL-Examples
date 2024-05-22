#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Initialize glfw, set window hints, create a window, and make it the current context
    @param width      Window width 
    @param height     Window height 
    @param title      Window title 
    @param major      OpenGL's major version 
    @param minor      OpenGL's minor version 
    @param profile    OpenGL profile to use
    @param resizable  Window should resize?  
    @returns          A window
*/
GLFWwindow* window(unsigned int width, unsigned int height, char *title, unsigned int major, unsigned int minor, unsigned int profile, unsigned int resizable);

#endif //WINDOW_H