#ifndef RENDERER_H
#define RENDERER_H

#include "vertexArray.h"
#include "buffer.h"
#include "shader.h"
#include "window.h"
#include "textureAtlas.h"
#include "../world/block.h"
#include "../world/chunk.h"

typedef struct {
    VertexArray vao;
    VertexBuffer vbo;
    TextureAtlas atlas;
    uint32_t shaderProgram;
    Window* window;
} Renderer;

void initRenderer(Renderer* renderer, Window* window);
void drawRenderer(Renderer* renderer);
void rendererPushBlock(Renderer* renderer, Block* block);
void rendererPushChunk(Renderer* renderer, Chunk* chunk);
void renderVertices(Window* window, VertexArray* vao, VertexBuffer* vbo, uint32_t shaderProgram);
#endif