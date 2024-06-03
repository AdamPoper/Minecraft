#include "block.h"

static void setTexCoord(Vertex* vertex, vec2 texCoord) {
    vertex->texCoord[0] = texCoord[0];
    vertex->texCoord[1] = texCoord[1];
}

static int getBlockFaceCaseByBlockType(uint16_t blockType) {
    switch (blockType) {
        case BLOCK_COBBLE_STONE: return BLOCK_FACE_COBBLE_STONE;
        case BLOCK_STONE: return BLOCK_FACE_STONE;
        case BLOCK_DIRT: return BLOCK_FACE_DIRT;
        case BLOCK_DIRT_GRASS: return -1;
        case BLOCK_SAND: return BLOCK_FACE_SAND;
        case BLOCK_WOOD_PLANK: return BLOCK_FACE_WOOD_PLANK;
        case BLOCK_WOOD_OAK: return BLOCK_FACE_WOOD_OAK;
        case BLOCK_GLASS: return BLOCK_FACE_GLASS;
        case BLOCK_FACE_AIR: return BLOCK_FACE_AIR;
    }
}

static void initBlockFaces(Block* block) {
    int blockFaceCase = getBlockFaceCaseByBlockType(block->type);
    if (blockFaceCase == -1) {
        initBlockFace(&block->blockFaces[0], BLOCK_FACE_GRASS, TOP);
        initBlockFace(&block->blockFaces[1], BLOCK_FACE_DIRT, BOTTOM);
        initBlockFace(&block->blockFaces[2], BLOCK_FACE_DIRT_GRASS, LEFT);
        initBlockFace(&block->blockFaces[3], BLOCK_FACE_DIRT_GRASS, RIGHT);
        initBlockFace(&block->blockFaces[4], BLOCK_FACE_DIRT_GRASS, FRONT);
        initBlockFace(&block->blockFaces[5], BLOCK_FACE_DIRT_GRASS, BACK);
        return;
    }

    for (int i = 0; i < BLOCK_FACE_COUNT; i++) {
        // the directions are equal to each value of i
        initBlockFace(&block->blockFaces[i], blockFaceCase, i);
    }
}

Block* createBlock(uint16_t type) {
    Block* block = (Block*) malloc(sizeof(Block) * 1);
    block->type = type;
    initBlockFaces(block);
    return block;
}

void initBlock(Block* block, uint16_t type) {
    block->type = type;
    initBlockFaces(block);
}

void destroyBlocksByCount(Block** blocks, size_t count) {
    for(int i = 0; i < count; i++) {
        free(blocks[i]);        
    }
}

static void translateBlock(Block* block) {
    for (int i = 0; i < BLOCK_FACE_COUNT; i++) {
        for (int j = 0; j < BLOCK_FACE_VERTEX_COUNT; j++) {
            block->blockFaces[i].vertices[j].position[0] += block->position[0];
            block->blockFaces[i].vertices[j].position[1] += block->position[1];
            block->blockFaces[i].vertices[j].position[2] += block->position[2];
        }
    }
}

void destroyBlocks(Block* blocks) {
    free(blocks);
}

void translateBlockByVectorTransform(Block* block, vec3 transform) {
    memcpy(block->position, transform, sizeof(float) * 3);
    translateBlock(block);
}

void printBlockContents(Block* block) {
    
}

void changeBlockType(Block* block, uint16_t type) {
    block->type = type;
    int blockFaceCase = getBlockFaceCaseByBlockType(type);
    if (blockFaceCase == -1) {
        changeBlockFaceType(&block->blockFaces[0], BLOCK_FACE_GRASS);      // top
        changeBlockFaceType(&block->blockFaces[1], BLOCK_FACE_DIRT);       // bottom
        changeBlockFaceType(&block->blockFaces[2], BLOCK_FACE_DIRT_GRASS); // left
        changeBlockFaceType(&block->blockFaces[3], BLOCK_FACE_DIRT_GRASS); // right
        changeBlockFaceType(&block->blockFaces[4], BLOCK_FACE_DIRT_GRASS); // front
        changeBlockFaceType(&block->blockFaces[5], BLOCK_FACE_DIRT_GRASS); // back
        return;
    }

    for (int i = 0; i < BLOCK_FACE_COUNT; i++) {
        changeBlockFaceType(&block->blockFaces[i], blockFaceCase);
    }
}