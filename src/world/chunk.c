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
        initBlock(&chunk->blocks[i], BLOCK_AIR);
    }
}

void destroyChunks(Chunk* chunks, uint32_t count) {
    for(int i = 0; i < count; i++) {
        destroyBlocks(chunks[i].blocks);
    }
}

static void createDirection(enum DIRECTION dir, vec3 dest, vec3 src) {
    memcpy(dest, src, sizeof(float) * 3);
    switch(dir) {
        case NORTH:
            dest[2] += 1.0f;
        break;
        case SOUTH:
            dest[2] -= 1.0f;
        break;
        case UP:
            dest[1] += 1.0f;
        break;
        case DOWN:
            dest[1] -= 1.0f;
        break;
        case EAST:
            dest[0] += 1.0f;
        break;
        case WEST:
            dest[0] -= 1.0f;
        break;
        default:
            printf("Invalid Direction\n");
        return;
    }
}

static int compareDirections(vec3 dest, vec3 src) {
    if( dest[0] == src[0] &&
        dest[1] == src[1] &&
        dest[2] == src[2]
    ) return 1;
    else return 0;
}

static int checkNeighboringBlocks(Block* block, Block* otherBlocks, uint32_t count) {
    vec3 north, south;
    vec3 east, west;
    vec3 up, down;    
    int addBlockToRenderer = 0;
    vec3 blockPos;
    memcpy(blockPos, block->position, sizeof(float) * 3);
    createDirection(NORTH, north, blockPos);
    createDirection(SOUTH, south, blockPos);
    createDirection(EAST, east, blockPos);
    createDirection(WEST, west, blockPos);
    createDirection(UP, up, blockPos);
    createDirection(DOWN, down, blockPos);
    int northBlockExists = 0;
    int southBlockExists = 0;
    int eastBlockExists = 0;
    int westBlockExists = 0;
    int upBlockExists = 0;
    int downBlockExists = 0;    
    for(int i = 0; i < count; i++) {       
        if(compareDirections(blockPos, otherBlocks[i].position)) {
            continue;
        }            
        if( compareDirections(north, otherBlocks[i].position) ||
            compareDirections(south, otherBlocks[i].position) ||
            compareDirections(east,  otherBlocks[i].position) ||
            compareDirections(west,  otherBlocks[i].position) ||
            compareDirections(up,    otherBlocks[i].position) ||
            compareDirections(down,  otherBlocks[i].position)
        ) {
            if(otherBlocks[i].type == BLOCK_AIR) {
                addBlockToRenderer = 1;
                break;
            }
        }
        if(compareDirections(north, otherBlocks[i].position)) {
            northBlockExists = 1;
        }
        if(compareDirections(south, otherBlocks[i].position)) {
            southBlockExists = 1;
        }
        if(compareDirections(east, otherBlocks[i].position)) {
            eastBlockExists = 1;
        }
        if(compareDirections(west, otherBlocks[i].position)) {
            westBlockExists = 1;
        }
        if(compareDirections(up, otherBlocks[i].position)) {
            upBlockExists = 1;
        }
        if(compareDirections(down, otherBlocks[i].position)) {
            downBlockExists = 1;
        }
    }    
    if(!northBlockExists || !southBlockExists || !eastBlockExists
     || !westBlockExists || !upBlockExists || !downBlockExists) {
        addBlockToRenderer = 1;
    }
    return addBlockToRenderer;
}

void optimizeChunk(Chunk* chunk, Block** blocksToRenderOut, uint32_t* numberOfBlocks) {
    Block** blocksToRender = (Block**)malloc(sizeof(Block*) * chunk->countBlocks);
    for(int i = 0; i < chunk->countBlocks; i++) {
        if(
            checkNeighboringBlocks(&chunk->blocks[i], chunk->blocks, chunk->countBlocks)
            && chunk->blocks[i].type != BLOCK_AIR
        ) {
            Block* b = &chunk->blocks[i];
            blocksToRender[(*numberOfBlocks)++] = b;
        }        
    }
    memcpy(blocksToRenderOut, blocksToRender, sizeof(Block*) * (*numberOfBlocks));
    free(blocksToRender);
}