#include "chunk.h"

Chunk* createChunk() {

    Chunk* chunk = (Chunk*)malloc(sizeof(chunk) * 1);
    chunk->blocks = (Block*)malloc(
        sizeof(Block) * CHUNK_HEIGHT * CHUNK_LENGTH * CHUNK_WIDTH
    );

}

void destroyChunk(Chunk* chunk) {
    destroyBlocks(chunk->blocks);
    free(chunk);
}