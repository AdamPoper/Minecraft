#include "blockface.h"

static void setTexCoord(Vertex* vertex, vec2 texCoord) {
    vertex->texCoord[0] = texCoord[0];
    vertex->texCoord[1] = texCoord[1];
}

static void genTextureCoords(BlockFace* blockFace) {
    vec2 coords[4];
    float x, y;

    switch(blockFace->type) {
        case BLOCK_FACE_DIRT:
            x = 1;
            y = 2; 
        break;

        case BLOCK_FACE_STONE:
            x = 2;
            y = 1;
        break;

        case BLOCK_FACE_GRASS:
            x = 0;
            y = 2;
        break;

        case BLOCK_FACE_SAND:
            x = 1;
            y = 0;
        break;

        case BLOCK_FACE_WOOD_PLANK:
            x = 1;
            y = 1;
        break;

        case BLOCK_FACE_WOOD_OAK:
            x = 0;
            y = 1;
        break;

        case BLOCK_FACE_DIRT_GRASS:
            x = 2;
            y = 2;
        break;

        case BLOCK_FACE_COBBLE_STONE:
            x = 0;
            y = 0;
        break;

        case BLOCK_FACE_GLASS:
            x = 2;
            y = 0;
        break;

        case BLOCK_FACE_AIR:
            x = -1;
            y = -1;
        break;
    }
    
    coords[0][0] = (x * TEXTURE_SIZE) / ATLAS_WIDTH;       // 0, 0
    coords[0][1] = (y * TEXTURE_SIZE) / ATLAS_HEIGHT;      // 0, 0
    coords[1][0] = ((x + 1) * TEXTURE_SIZE) / ATLAS_WIDTH; // 1, 0
    coords[1][1] = (y * TEXTURE_SIZE) / ATLAS_HEIGHT;      // 1, 0
    coords[2][0] = ((x + 1) * TEXTURE_SIZE) / ATLAS_WIDTH; // 1, 1
    coords[2][1] = ((y + 1) * TEXTURE_SIZE) / ATLAS_HEIGHT;// 1, 1
    coords[3][0] = (x * TEXTURE_SIZE) / ATLAS_WIDTH;       // 0, 1
    coords[3][1] = ((y + 1) * TEXTURE_SIZE) / ATLAS_HEIGHT;// 0, 1

    switch(blockFace->direction) {
        case TOP:
            setTexCoord(&blockFace->vertices[0], coords[1]);
            setTexCoord(&blockFace->vertices[1], coords[2]);
            setTexCoord(&blockFace->vertices[2], coords[3]);  // top
            setTexCoord(&blockFace->vertices[3], coords[1]);
            setTexCoord(&blockFace->vertices[4], coords[3]);
            setTexCoord(&blockFace->vertices[5], coords[0]);
        break;

        case BOTTOM:
            setTexCoord(&blockFace->vertices[0], coords[1]);
            setTexCoord(&blockFace->vertices[1], coords[2]);
            setTexCoord(&blockFace->vertices[2], coords[3]);  // bottom
            setTexCoord(&blockFace->vertices[3], coords[1]);
            setTexCoord(&blockFace->vertices[4], coords[3]);
            setTexCoord(&blockFace->vertices[5], coords[0]);
        break;

        case LEFT:
            setTexCoord(&blockFace->vertices[0], coords[3]);
            setTexCoord(&blockFace->vertices[1], coords[0]);
            setTexCoord(&blockFace->vertices[2], coords[1]);  // left
            setTexCoord(&blockFace->vertices[3], coords[3]);
            setTexCoord(&blockFace->vertices[4], coords[1]);
            setTexCoord(&blockFace->vertices[5], coords[2]);
        break;

        case RIGHT:
            setTexCoord(&blockFace->vertices[0], coords[3]);
            setTexCoord(&blockFace->vertices[1], coords[0]);
            setTexCoord(&blockFace->vertices[2], coords[1]);  // right
            setTexCoord(&blockFace->vertices[3], coords[3]);
            setTexCoord(&blockFace->vertices[4], coords[1]);
            setTexCoord(&blockFace->vertices[5], coords[2]);
        break;

        case FRONT:
            setTexCoord(&blockFace->vertices[0], coords[0]);
            setTexCoord(&blockFace->vertices[1], coords[1]);
            setTexCoord(&blockFace->vertices[2], coords[2]);  // front
            setTexCoord(&blockFace->vertices[3], coords[0]);
            setTexCoord(&blockFace->vertices[4], coords[2]);
            setTexCoord(&blockFace->vertices[5], coords[3]);
        break;

        case BACK:
            setTexCoord(&blockFace->vertices[0], coords[3]);
            setTexCoord(&blockFace->vertices[1], coords[2]);
            setTexCoord(&blockFace->vertices[2], coords[1]);
            setTexCoord(&blockFace->vertices[3], coords[3]);  // back
            setTexCoord(&blockFace->vertices[4], coords[1]);
            setTexCoord(&blockFace->vertices[5], coords[0]);
        break;
    }
}

static void initBlockFaceVertices(BlockFace* blockFace) {
    switch(blockFace->direction) {
        case TOP: {
            float vertices[] = {
               -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 1.0f, // 0
                0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 1
                0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 0.0f, // 6      // top
               -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 1.0f, // 0
                0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 0.0f, // 6
               -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 1.0f, 1.0f, // 7         
            };
            memcpy(blockFace->vertices, vertices, sizeof(Vertex) * BLOCK_FACE_VERTEX_COUNT);
            genTextureCoords(blockFace);
        }
        break;

        case BOTTOM: {
            float vertices[] = {
                0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2
               -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 0.0f, 0.0f, // 3
               -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 4      // bottom
                0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2
               -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 4
                0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 5
            };
            memcpy(blockFace->vertices, vertices, sizeof(Vertex) * BLOCK_FACE_VERTEX_COUNT);
            genTextureCoords(blockFace);
        }
        break;

        case LEFT: {
            float vertices[] = {
               -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
               -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 3
               -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 4      // left
               -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
               -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 4
               -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 7
            };
            memcpy(blockFace->vertices, vertices, sizeof(Vertex) * BLOCK_FACE_VERTEX_COUNT);
            genTextureCoords(blockFace);
        }
        break;

        case RIGHT: {
            float vertices[] = {
                0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 1.0f, // 1
                0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 1.0f, // 2
                0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 0.0f, // 5      // right
                0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 1.0f, // 1
                0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 0.0f, // 5
                0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 0.0f, // 6
            };
            memcpy(blockFace->vertices, vertices, sizeof(Vertex) * BLOCK_FACE_VERTEX_COUNT);
            genTextureCoords(blockFace);
        }
        break;

        case FRONT: {
            float vertices[] = {
                -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 4
                 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 5
                 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 6      // front
                -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 4
                 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 6
                -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 7
            };
            memcpy(blockFace->vertices, vertices, sizeof(Vertex) * BLOCK_FACE_VERTEX_COUNT);
            genTextureCoords(blockFace);
        }
        break;

        case BACK: {
            float vertices[] = {
               -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
                0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 1
                0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2      // back  
               -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
                0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2
               -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 3 
            };
            memcpy(blockFace->vertices, vertices, sizeof(Vertex) * BLOCK_FACE_VERTEX_COUNT);
            genTextureCoords(blockFace);
        }
        break;
    }
}

void initBlockFace(BlockFace* blockFace, uint16_t type, uint16_t direction) {
    blockFace->direction = direction;
    blockFace->type = type;
    blockFace->shouldRender = false;
    initBlockFaceVertices(blockFace);
}

void changeBlockFaceType(BlockFace* blockFace, uint16_t type) {
    blockFace->type = type;
    genTextureCoords(blockFace);
}