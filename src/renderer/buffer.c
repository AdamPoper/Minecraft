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
    if (!block) {
        printf("no block\n");
        return;
    }
    
    uint32_t count = vbo->count;
    if (vbo->count + BLOCK_VERTEX_COUNT >= vbo->capacity) {
        vboResize(vbo);        
    }

    uint32_t running_count = count;
    for (int i = 0; i < BLOCK_FACE_COUNT; i++) {
        for (int j = 0; j < BLOCK_FACE_VERTEX_COUNT; j++) {
            vbo->data[running_count] = block->blockFaces[i].vertices[j];
            running_count++;
            vbo->count++;
        }
    }
}

void vboPush(VertexBuffer* vbo, Vertex* vertices, uint32_t count) {
    uint32_t oldCount = vbo->count;
    if (oldCount + count >= vbo->capacity) {
        vboResize(vbo);
    }
    uint32_t vertexIndex = 0;
    for (int i = oldCount; i < oldCount + count; i++) {
        vbo->data[i] = vertices[vertexIndex];
        vertexIndex++;
        vbo->count++;
    }
}

void dumpRawBufferContents(VertexBuffer* vbo) {
    for (int i = 0; i < vbo->count; i++) {
        printf("Vertex # %d Block # %d ", i, (i / BLOCK_VERTEX_COUNT) + 1);
        printVertex(&vbo->data[i]);
    }
}