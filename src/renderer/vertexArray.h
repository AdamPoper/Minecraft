#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    uint32_t renderId;
    uint32_t stride;
    uint32_t numAttribs;
    uint32_t* counts;
} VertexArray;

VertexArray vaoCreate();
void vaoDestroy(VertexArray* vao);
void vaoBind(VertexArray* vao);
void pushVertexAttrib(VertexArray* vao, uint32_t count);
void enableAttribs(VertexArray vao);

#endif