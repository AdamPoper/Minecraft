#ifndef RENDERER_H
#define RENDERER_H

#include "vertexArray.h"
#include "buffer.h"
#include "shader.h"
#include "window.h"
#include "textureAtlas.h"
#include "block.h"

typedef struct {
    VertexArray vao;
    VertexBuffer vbo;
    TextureAtlas atlas;
    uint32_t shaderProgram;
    Window* window;
} Renderer;

void initRenderer(Renderer* renderer, Window* window);
void drawRenderer(Renderer* renderer);
void destroyRenderer(Renderer* renderer);
void rendererPushBlock(Renderer* renderer, Block* block);
void renderVertices(Window* window, VertexArray* vao, VertexBuffer* vbo, uint32_t shaderProgram);
#endif