#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../renderer/vertex.h"

#define BLOCK_VERTEX_COUNT 36

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

#define BLOCK_TYPE_COUNT 9

typedef struct {
    uint32_t type;
    Vertex vertices[BLOCK_VERTEX_COUNT];
    vec3 position;
} Block;

Block* createBlock(uint32_t type);
void destroyBlocks(Block** blocks, size_t count);
void translateBlock(Block* block);

#endif