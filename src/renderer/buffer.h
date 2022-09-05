#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include "vertex.h"
#include <stdlib.h>
#include <string.h>
#include "../world/block.h"

typedef struct {
    uint32_t renderID;
    uint32_t type;
    Vertex* data;
    uint32_t count; // number of vertices;
    uint32_t capacity; // current vertices capactity;
} VertexBuffer;

VertexBuffer vboCreate();
void vboInit(VertexBuffer* vbo);
void vboDestroy(VertexBuffer* vbo);
void vboBind(VertexBuffer* vbo);
void vboPush(VertexBuffer* vbo, Vertex* vertices, uint32_t count);
void vboPushBlock(VertexBuffer* vbo, Block* block);
void dumpRawBufferContents(VertexBuffer* vbo);

#endif