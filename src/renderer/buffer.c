#include "buffer.h"

void vboBind(VertexBuffer* vbo) {
    glBindBuffer(vbo->type, vbo->renderID);
}

static void vboResize(VertexBuffer* vbo) {
    vbo->capacity *= 2;
    Vertex* newBuffer = (Vertex*)malloc(sizeof(Vertex) * vbo->capacity);
    if(!newBuffer)
        return;
    memcpy(newBuffer, vbo->data, sizeof(Vertex) * vbo->count);
    Vertex* doomed = vbo->data;
    vbo->data= newBuffer;
    free(doomed);
}

VertexBuffer vboCreate() {
    size_t cap = sizeof(Vertex) * 10000; // init capacity for 10000 vertices
    VertexBuffer vbo = {
        .type = GL_ARRAY_BUFFER,
        .count = 0,
        .capacity = cap,
        .data = (Vertex*)malloc(cap)
    };
    glGenBuffers(1, &vbo.renderID);  
    vboBind(&vbo);
    return vbo;
}

void vboDestroy(VertexBuffer* vbo) {
    free(vbo->data);
}

void vboPushBlock(VertexBuffer* vbo, Block* block) {
    uint32_t count = vbo->count;
    if(vbo->count + BLOCK_VERTEX_COUNT >= vbo->capacity) {
        vboResize(vbo);        
    }   
    // add the block vertex data to the vertex buffer
    uint32_t blockIndex = 0;
    for(int i = count; i < count + BLOCK_VERTEX_COUNT; i++) {
        vbo->data[i] = block->vertices[blockIndex];
        blockIndex++;
        vbo->count++;
    }
}

void vboPush(VertexBuffer* vbo, Vertex* vertices, uint32_t count) {    
    uint32_t oldCount = vbo->count;
    if(vbo->count + count >= vbo->capacity) {
        vboResize(vbo);
    }
    uint32_t vertexIndex = 0;
    for(int i = oldCount; i < oldCount + count; i++) {
        vbo->data[i] = vertices[vertexIndex];
        vertexIndex++;
        vbo->count++;
    }
}