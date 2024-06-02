#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"

#define CHUNK_HEIGHT 32
#define CHUNK_LENGTH 16
#define CHUNK_WIDTH  16

typedef struct {
    Block* blocks;
    vec3 position;
    uint32_t countBlocks;
} Chunk;

typedef struct {
    Block** blocks;
    uint32_t count;
} RenderBlocks;

Chunk* createChunks(uint32_t count);
void initChunk(Chunk* chunk);
void destroyChunks(Chunk* chunks, uint32_t count);
void optimizeChunk(Chunk* chunk, Block** blocks, uint32_t* count);

#endif