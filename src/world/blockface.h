#ifndef BLOCK_FACE_H
#define BLOCK_FACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../renderer/vertex.h"

#define BLOCK_FACE_VERTEX_COUNT 6

#define BLOCK_FACE_DIRT 1
#define BLOCK_FACE_STONE 2
#define BLOCK_FACE_GRASS 3
#define BLOCK_FACE_SAND 4
#define BLOCK_FACE_WOOD_PLANK 5
#define BLOCK_FACE_WOOD_OAK 6
#define BLOCK_FACE_DIRT_GRASS 7
#define BLOCK_FACE_COBBLE_STONE 8
#define BLOCK_FACE_GLASS 9
#define BLOCK_FACE_AIR 10

#define TOP 0
#define BOTTOM 1
#define LEFT 2
#define RIGHT 3
#define FRONT 4
#define BACK 5

#define TEXTURE_SIZE 256
#define ATLAS_HEIGHT 768
#define ATLAS_WIDTH 768

typedef struct {
    Vertex vertices[BLOCK_FACE_VERTEX_COUNT];
    bool shouldRender;
    uint16_t type;
    uint16_t direction;
} BlockFace;

void initBlockFace(BlockFace* blockFace, uint16_t type, uint16_t direction);
void changeBlockFaceType(BlockFace* blockFace, uint16_t type);

#endif