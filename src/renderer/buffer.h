#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include "vertex.h"
#include <stdlib.h>
#include <string.h>
#include "../block.h"

typedef struct {
    uint32_t renderID;
    uint32_t type;
    Vertex* data;
    size_t count; // number of vertices;
    size_t capacity; // current vertices capactity;
} VertexBuffer;

VertexBuffer vboCreate();
void vboDestroy(VertexBuffer* buffer);
void vboBind(VertexBuffer* buffer);
void vboPush(VertexBuffer* vbo, Vertex* vertices, uint32_t count);
void vboPushBlock(VertexBuffer* vbo, Block* block);

#endif