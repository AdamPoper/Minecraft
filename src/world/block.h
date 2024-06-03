#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../renderer/vertex.h"
#include "blockFace.h"

// #define BLOCK_VERTEX_COUNT 36
#define BLOCK_FACE_COUNT 6

#define ATLAS_WIDTH 768
#define ATLAS_HEIGHT 768

#define BLOCK_TEX_SIZE 256

#define BLOCK_DIRT 1
#define BLOCK_STONE 2
#define BLOCK_GRASS 3
#define BLOCK_SAND 4
#define BLOCK_WOOD_PLANK 5
#define BLOCK_WOOD_OAK 6
#define BLOCK_DIRT_GRASS 7
#define BLOCK_COBBLE_STONE 8
#define BLOCK_GLASS 9
#define BLOCK_AIR 10

#define BLOCK_TYPE_COUNT 10

typedef struct {
    uint16_t type;
    BlockFace blockFaces[BLOCK_FACE_COUNT];
    vec3 position;
} Block;

enum DIRECTION {
    NORTH, SOUTH,
    EAST, WEST,
    UP, DOWN
};

Block* createBlock(uint16_t type);
void initBlock(Block* block, uint16_t type);
void destroyBlocksByCount(Block** blocks, size_t count);
void destroyBlocks(Block* blocks);
// void translateBlock(Block* block);
void translateBlockByVectorTransform(Block* block, vec3 transform);
void changeBlockType(Block* block, uint16_t type);
void printBlockContents(Block* block);
#endif