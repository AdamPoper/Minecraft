#ifndef RENDERER_H
#define RENDERER_H

#include "vertexArray.h"
#include "buffer.h"
#include "shader.h"
#include "window.h"

void renderVertices(Window* window, VertexArray* vao, VertexBuffer* vbo, uint32_t shaderProgram);
#endif