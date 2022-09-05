#include "chunk.h"

Chunk* createChunks(uint32_t count) {
    Chunk* chunks = (Chunk*)malloc(sizeof(Chunk) * count);
    for(int i = 0; i < count; i++) {
        initChunk(&chunks[i]);
    }
    return chunks;
}

void initChunk(Chunk* chunk) {
    chunk->countBlocks = CHUNK_HEIGHT * CHUNK_LENGTH * CHUNK_WIDTH;
    chunk->blocks = (Block*)malloc(sizeof(Block) * chunk->countBlocks);
    for(int i = 0; i < chunk->countBlocks; i++) {
        initBlock(&chunk->blocks[i], BLOCK_DIRT);
    }
}

void destroyChunks(Chunk* chunks, uint32_t count) {
    for(int i = 0; i < count; i++) {
        destroyBlocks(chunks[i].blocks);
    }
}