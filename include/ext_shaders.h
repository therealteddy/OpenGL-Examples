/*
    A header that handles basic operations on shaders. This was an extension on shaders.h; hence, its called ext_shaders.h.
    This implementation aligns as closely to the learnopengl book as possible.
*/

#ifndef EXT_SHADERS_H
#define EXT_SHADERS_H

#include <glad/glad.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>

#define ERRORBUFFER 512

#define _abs_(x) (x < 0) ? -x : x 
#define _min_(x, y) (x < y) ? x : y 
#define _max_(x, y) (x > y) ? x : y 

/* The most basic shaders you will need */
extern char *fragment, *vertex;

/*
    Read a shader source code and return a string.
    @param path  The file path to the text file containing the glsl source code.
    @param dest  The destination character array to which the contents of the file at `path` is copied to  
*/
void shader(char *path, char *dest[]);

/*
    Compile shaders, and link them into a shader program.
    @param vertexshader     The character array containg the vertex shader source. 
    @param fragmentshader   The character array containing the fragment shader source. 
    @return                 The program containing the linked shaders for use with `glUseProgram()`
*/
unsigned int program(char **vertexshader, char **fragmentshader);

/* 
    Set the value of a uniform
    @param  name Name of uniform 
    @param  value The value to set of type bool
    @param  prog  The shader program the uniform rests on
*/
void uniform_bool (unsigned int prog, char* name, bool  value);

/* 
    Set the value of a uniform
    @param  name Name of uniform 
    @param  value The value to set of type int
    @param  prog  The shader program the uniform rests on
*/
void uniform_int  (unsigned int prog, char* name, int   value);

/* 
    Set the value of a uniform
    @param  name  Name of uniform 
    @param  value The value to set of type float
    @param  prog  The shader program the uniform rests on
*/
void uniform_float(unsigned int prog, char* name, float value); 

/* 
    Set the value of a uniform
    @param  name  Name of uniform 
    @param  value_x The x value to set of type float
    @param  value_y The y value to set of type float
    @param  prog  The shader program the uniform rests on
*/
void uniform_2f(unsigned int prog, char* name, float value_x, float value_y);

#endif