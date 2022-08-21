#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <cglm/cglm.h>
#include <cglm/affine-mat.h>

typedef struct
{
    uint32_t renderId;
    char* sourceCode;
    const char* filepath;
    uint32_t type;
} Shader;

Shader* createShader(uint32_t type, const char* filepath);
char* readShaderFromFile(const char* filepath);
void shaderFree(Shader* shader);
uint32_t createShaderProgram(Shader* shader1, Shader* shader2);
void setMatrix4fv(uint32_t shaderProgram, const char* name, mat4 mat);
void setUniform1i(uint32_t shaderProgram, const char* name, uint32_t value);
#endif