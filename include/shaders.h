#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <stdio.h> 

#define ERRORBUFFER 512

/* The most basic shaders you will need */
extern char *fragment, *vertex;

/*
    Compile a shader from its source
    @returns The id of the compiled shader on success and zero on failure
    @param shadersource The location of the source string 
    @param shadertype The type of shader 
*/
extern unsigned int shader(char *shadersource[], int shadertype);

/*
    Create a shader program
    @returns The shader program with the all the shaders from `shaderid[]` linked on success, or zero if compilation failed
    @param shaderid[] An array containing all the shaders to form a shader program
    @param nshaders The number of shaders to link
*/
extern unsigned int program(unsigned int nshaders, unsigned int shaderid[]); 

/* 
    Delete the compiled shaders 
    @returns Nothing. 
    @param nshaders The number of shaders to free
    @param shaderid[] An array containing all the shaders to free
*/
extern unsigned int shaderfree(unsigned int nshaders, unsigned int shaderid[]);

#endif