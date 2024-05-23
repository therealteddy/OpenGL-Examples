#include "../include/ext_shaders.h"
#include "../include/window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

unsigned int vbo, ebo, vao, sp, texture;
unsigned int imagew, imageh, imagec;
char *imagedata, *vertexsource, *fragmentsource;

float vertexdata[8 * 4] = {
    /*   Vertices   */      /*    Color    */     /* Texture */
    -0.5f, +0.5f, 0.0f,     1.0f, 1.0f, 0.0f,     0.0f, 1.0f, /* 0.Top Left */      
    +0.5f, +0.5f, 0.0f,     0.0f, 1.0f, 1.0f,     0.0f, 1.0f, /* 1.Top Right */  
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f,     0.0f, 1.0f, /* 2.Bottom Left */ 
    +0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f, /* 3.Bottom Right */
};

float indices[6] = {
    /* Left/Top Rectangle */
    0, 1, 2, 
    /* Right/Bottom Rectangle */
    2, 3, 0,
};

int main(int argc, char **argv) {
    GLFWwindow* win = window(800, 600, "Bricked Wall!", 3, 3, GLFW_OPENGL_CORE_PROFILE, GLFW_FALSE);
    glClearColor(0.4, 0.8, 0.6, 1.0);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo); 
    glGenVertexArrays(1, &vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), vertexdata, GL_STATIC_DRAW);

    // Vao stores the vbo by calls to glVertexAttribPointer(); this function takes data from the vbo bound before its call. 
    // Thus, Vao can be bound after binding the vbo as long as glVertexAttribPointer() is called after the vbo is bound
    glBindVertexArray(vao);

    // Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void* ) 0);
    glEnableVertexAttribArray(0);

    // Colors 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3);
    glEnableVertexAttribArray(1);

    // Texture Coords 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);
    glEnableVertexAttribArray(2);

    // On the other hand, the vao stores the last ebo bound after the vao is bound. Thus it ebos must always be bound after the vao
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    imagedata = stbi_load("../textures/bricks.jpg", &imagew, &imageh, &imagec, 0);
    glGenTextures(1, &texture); 
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (imagedata) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagew, imageh, 0, GL_RGB, GL_UNSIGNED_BYTE, imagedata);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(imagedata);
    }
    else puts("Failed to read image!");

    shader("../shaders/bricked_rectangle/vertex.glsl", &vertexsource); 
    shader("../shaders/bricked_rectangle/fragment.glsl", &fragmentsource);
    // todo 
    while(!glfwWindowShouldClose(win)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(win);
    }
    return 0;
}