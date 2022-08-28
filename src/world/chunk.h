#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "world.h"

#define CHUNK_HEIGHT 128
#define CHUNK_LENGTH 16
#define CHUNK_WIDTH 16

typedef struct {
    Block* blocks;
    vec3 position;
    World* world;
    size_t count;
} Chunk;

Chunk* createChunk();
void destroyChunk(Chunk* chunk);

#endif