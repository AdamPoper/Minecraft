#include "shader.h"

int shaderCompileStatus(uint32_t id)
{
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    return success;
}

char* readShaderFromFile(const char* filepath)
{
    FILE* file;
    file = fopen(filepath, "r");
    if(!file)
    {
        printf("%s %s\n", filepath, "did not load");
        return NULL;
    }
    else
    {
        char* src = malloc(sizeof(char)*2048);
        char line[64];
        while(fgets(line, 64, file) != NULL)
        {
            strcat(src, line);            
        }        
        if(src != NULL)
        {
            fclose(file);
            return src;
        }
        else
        {
            printf("%s\n", "shader did not read");
            fclose(file);
            return NULL;
        }
    }
}

Shader* createShader(uint32_t type, const char* filepath)
{
    Shader* shader = (Shader*)malloc(sizeof(Shader)*1);
    shader->renderId = glCreateShader(type);
    shader->type = type;
    shader->sourceCode = readShaderFromFile(filepath);
    if(shader->sourceCode != NULL)
    {
        glShaderSource(shader->renderId, 1, &shader->sourceCode, NULL);
        glCompileShader(shader->renderId);
        if(!shaderCompileStatus(shader->renderId))
        {
            char infoLog[512];
            glGetShaderInfoLog(shader->renderId, 512, NULL, infoLog);
            printf("shader id: %d failed\n", shader->renderId);
            printf("%s\n", infoLog);
            return NULL;
        }       
        return shader; 
    }
    else
    {
        return NULL;
    }
}

void shaderFree(Shader* shader)
{
    free(shader->sourceCode);
    glDeleteShader(shader->renderId);
}

uint32_t createShaderProgram(Shader* vertexShader, Shader* fragmentShader)
{
    uint32_t program = glCreateProgram();
    glAttachShader(program, vertexShader->renderId);
    glAttachShader(program, fragmentShader->renderId);
    glValidateProgram(program);
    glLinkProgram(program);
    int linkSuccess;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
    if(!linkSuccess)
    {
        char infoLog[512];
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        printf("shader id: %d failed\n", program);        
        printf("%s\n", infoLog);
    }
    return program;
}

void setMatrix4fv(uint32_t shaderProgram, const char* name, mat4 mat)
{
    uint32_t loc;
    loc = glGetUniformLocation(shaderProgram, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, mat[0]);
}

void setUniform1i(uint32_t shaderProgram, const char* name, uint32_t value)
{
    uint32_t loc;
    loc = glGetUniformLocation(shaderProgram, name);
    glUniform1i(loc, value);
}