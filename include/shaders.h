#ifndef SHADERS_H
#define SHADERS_H

#define BUFFERSIZE 512
#define BASIC_VERTEX_SHADER_SOURCE &vshader_basic 
#define BASIC_FRAGEMNT_SHADER_SOURCE &fshader_basic
#define BASIC_VERTEX_SHADER shader(BASIC_VERTEX_SHADER_SOURCE, GL_VERTEX_SHADER)
#define BASIC_FRAGMENT_SHADER shader(BASIC_FRAGEMNT_SHADER_SOURCE, GL_FRAGMENT_SHADER) 

/* The most basic shaders you will need */
extern char *fshader_basic, *vshader_basic;

/*
    Compile a shader from its source
    @returns The id of the compiled shader on success and zero on failure
    @param shadersource The location of the source string 
    @param shadertype The type of shader on success
*/
extern unsigned int shader(char *shadersource[], int shadertype);

/*
    Create a shader program
    @returns The shader program with the all the shaders from `shaderid[]` linked on success, or zero if failure
    @param shaderid[] An array containing all the shaders to form a shader program
    @param nshaders The number of shaders to link
*/
extern unsigned int shaderprogram(unsigned int nshaders, unsigned int shaderid[]); 

/* 
    Delete the compiled shaders 
    @returns Nothing. 
    @param nshaders The number of shaders to destroy
    @param shaderid[] An array containing all the shaders to destroy
*/
extern void deleteshaders(unsigned int nshaders, unsigned int shaderid[]);

#endif