#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* Vertex and Fragment Shaders - Defined later */ 
char* vertex_shader_source; 
char vertex_shader_errmsg_buffer[512]; 
int vertex_shader_success; 

char* fragment_shader_source; 
char fragment_shader_errmsg_buffer[512]; 
int fragment_shader_success; 

/* Shader Program metadata */ 
char shader_program_errmsg_buffer[512]; 
int shader_program_success; 

/* A function callback to resize the frame buffer when the window is resized */
void resize_viewport(GLFWwindow* window, int window_width, int window_height); 

/* A function to keyboard/mouse events */
void process_input(GLFWwindow* window); 

int main(int argc, char** argv) {

    glfwInit(); /* Initial GLFW - Must be called before other calls to the library */

    /* Use OpenGL 3.3 and the core profile - removes all the deprecated functions */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle!", NULL, NULL); 
    if (!window) /* If window creation failed */ 
    {
        fprintf(stderr, "Failed to create window!\n"); 
        glfwTerminate();
        return EXIT_FAILURE;  
    }

    /* Make our window the main context */
    glfwMakeContextCurrent(window); 

    /* Load all the OpenGL functions */
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to load the OpenGL functions!\n"); 
        return EXIT_FAILURE;
    }

    /* Set a callbeck to resize the viewport when the window is resized */
    glfwSetFramebufferSizeCallback(window, resize_viewport);

    /* Define and copy the vertex data to the GPU */
    float triangle_vertices[3 * 3] = {
         0.0f,  1.0f,  0.0f, /* Top */ 
        -1.0f, -1.0f,  0.0f, /* Bottom Left*/
         1.0f, -1.0f,  0.0f /* Bottom Right*/
    }; 
    unsigned int triangle_vbo; 
    glGenBuffers(1, &triangle_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    /* Compile the shaders and load it into the gpu */
    unsigned int vertex_shader_object; 
    vertex_shader_object = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vertex_shader_object, 1, &vertex_shader_source, NULL); 
    glCompileShader(vertex_shader_object);
    glGetShaderiv(vertex_shader_object, GL_COMPILE_STATUS, &vertex_shader_success); 
    if (!vertex_shader_success) {
        glGetShaderInfoLog(vertex_shader_object, sizeof(vertex_shader_errmsg_buffer), NULL, vertex_shader_errmsg_buffer); 
        fprintf(stderr, "Failed to compile vertex shader!\n");
        fprintf(stderr, "%s\n", vertex_shader_errmsg_buffer); 
    }

    unsigned int fragment_shader_object; 
    fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER); 
    glShaderSource(fragment_shader_object, 1, &fragment_shader_source, NULL); 
    glCompileShader(fragment_shader_object);
    glGetShaderiv(fragment_shader_object, GL_COMPILE_STATUS, &fragment_shader_success); 
    if (!fragment_shader_success) {
        glGetShaderInfoLog(fragment_shader_object, sizeof(fragment_shader_errmsg_buffer), NULL, fragment_shader_errmsg_buffer); 
        fprintf(stderr, "Failed to compile fragment shader!\n"); 
        fprintf(stderr, "%s\n", fragment_shader_errmsg_buffer);
    } 

    /* Create a shader program */
    unsigned int shader_program; 
    shader_program = glCreateProgram(); 
    glAttachShader(shader_program, vertex_shader_object);
    glAttachShader(shader_program, fragment_shader_object); 
    glLinkProgram(shader_program);  
    glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_program_success); 
    if (!shader_program_success) {
        glGetProgramInfoLog(shader_program, sizeof(shader_program_errmsg_buffer), NULL, shader_program_errmsg_buffer); 
        fprintf(stderr, "Failed to link shaders into a shader program!\n"); 
        fprintf(stderr, "%s\n", shader_program_errmsg_buffer);
    } else {
        glDeleteShader(vertex_shader_object); 
        glDeleteShader(fragment_shader_object);
    }

    /* Create a VAO */
    unsigned int triangle_vao;
    glGenVertexArrays(1, &triangle_vao);
    glBindVertexArray(triangle_vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0); 
    glEnableVertexAttribArray(0);

    /* Bind all the necessary objects for rendering */ 
    glBindBuffer(GL_ARRAY_BUFFER, 0); /* Unbind a buffer to see its effects */
    glBindVertexArray(triangle_vao); /* No need to re-bind if previously bound */
    glUseProgram(shader_program); /* Bind the shader program to use */

    /* The render loop */
    while (!glfwWindowShouldClose(window)) {
        
        /* Clear the screen's color*/ 
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Draw the triangle */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); /* Swap the front and back buffers */
        glfwPollEvents(); /* Process all the pending events in the event queue */
        process_input(window); /* Do something when user inputs something */
    }

    /* Cleanup and exit */
    glfwTerminate();
    return EXIT_SUCCESS; 
}

void resize_viewport(GLFWwindow* window, int window_width, int window_height) {
    glViewport(0, 0, window_width, window_height); /* Set the position of the rendering area to the bottom left of the window and its dimensions to that of the window as well */ 
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true); /* Close the windwo when esc is pressed */
}

char* vertex_shader_source = "#version 330 core\n"
                             "layout (location = 0) in vec3 vertex;\n"
                             "void main() {\n"
                             "    gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0f);\n"
                             "}\n";

char* fragment_shader_source = "#version 330 core\n" 
                               "out vec4 color;\n"
                               "void main() {\n"
                               "    color = vec4(0.53f, 0.81f, 0.98f, 1.0f);\n"
                               "}\n"; 
