#include "buffer.h"

void vboBind(VertexBuffer* vbo) {
    glBindBuffer(vbo->type, vbo->renderID);
}

static void vboResize(VertexBuffer* vbo) {
    vbo->capacity *= 2;
    Vertex* newBuffer = (Vertex*)malloc(sizeof(Vertex) * vbo->capacity);
    if(!newBuffer) {
        printf("VBO Resize Allocation Failed\n");
        return;
    }
    memcpy(newBuffer, vbo->data, sizeof(Vertex) * vbo->count);
    Vertex* doomed = vbo->data;
    vbo->data = newBuffer;
    free(doomed);
}

VertexBuffer vboCreate() {
    uint32_t cap = BLOCK_VERTEX_COUNT * 32; // init capacity for 32 blocks
    VertexBuffer vbo = {
        .type = GL_ARRAY_BUFFER,
        .count = 0,
        .capacity = cap,
        .data = (Vertex*)malloc(sizeof(Vertex) * cap)
    };
    glGenBuffers(1, &vbo.renderID);  
    vboBind(&vbo);
    return vbo;
}
 
void vboInit(VertexBuffer* vbo) {
    uint32_t cap = BLOCK_VERTEX_COUNT * 32; // init capacity for 32 blocks
    vbo->type = GL_ARRAY_BUFFER;
    vbo->count = 0;
    vbo->data = (Vertex*)malloc(sizeof(Vertex) * cap);
    glGenBuffers(1, &vbo->renderID);
    vboBind(vbo);    
}

void vboDestroy(VertexBuffer* vbo) {
    free(vbo->data);
}

void vboPushBlock(VertexBuffer* vbo, Block* block) {
    // printf("pushing block [Vertex Count: %d]\n", vbo->count);
    if(!block) {
        printf("no block\n");
        return;
    }
    uint32_t count = vbo->count;
    if(vbo->count + BLOCK_VERTEX_COUNT >= vbo->capacity) {
        printf("resizing\n");
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
    printf("VBO old count: %d\n", vbo->count);
    uint32_t oldCount = vbo->count;
    if(oldCount + count >= vbo->capacity) {
        vboResize(vbo);
    }
    uint32_t vertexIndex = 0;
    for(int i = oldCount; i < oldCount + count; i++) {
        vbo->data[i] = vertices[vertexIndex];
        vertexIndex++;
        vbo->count++;
    }
    printf("VBO new count: %d\n", vbo->count);
}

void dumpRawBufferContents(VertexBuffer* vbo) {
    for(int i = 0; i < vbo->count; i++) {
        printf("Vertex # %d Block # %d ", i, (i / BLOCK_VERTEX_COUNT) + 1);
        printVertex(&vbo->data[i]);
    }
}