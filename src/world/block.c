#include "block.h"

static void setTexCoord(Vertex* vertex, vec2 texCoord) {
    vertex->texCoord[0] = texCoord[0];
    vertex->texCoord[1] = texCoord[1];
}

static void genDirtGrassBlock(Vertex* vertices) {
    float allDirtX = 1;
    float allDirtY = 2;
    float dirtGrassX = 2;
    float dirtGrassY = 2;
    float grassX = 0;
    float grassY = 2;

    vec2 allDirtCoords[4];
    vec2 dirtGrassCoords[4];
    vec2 grassCoords[4];

    allDirtCoords[0][0] = (allDirtX * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 0
    allDirtCoords[0][1] = (allDirtY * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 0, 0
    allDirtCoords[1][0] = ((allDirtX + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 0
    allDirtCoords[1][1] = (allDirtY * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 1, 0
    allDirtCoords[2][0] = ((allDirtX + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 1
    allDirtCoords[2][1] = ((allDirtY + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 1, 1
    allDirtCoords[3][0] = (allDirtX * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 1
    allDirtCoords[3][1] = ((allDirtY + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 0, 1

    dirtGrassCoords[0][0] = (dirtGrassX * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 0
    dirtGrassCoords[0][1] = (dirtGrassY * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 0, 0
    dirtGrassCoords[1][0] = ((dirtGrassX + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 0
    dirtGrassCoords[1][1] = (dirtGrassY * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 1, 0
    dirtGrassCoords[2][0] = ((dirtGrassX + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 1
    dirtGrassCoords[2][1] = ((dirtGrassY + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 1, 1
    dirtGrassCoords[3][0] = (dirtGrassX * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 1
    dirtGrassCoords[3][1] = ((dirtGrassY + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 0, 1

    grassCoords[0][0] = (grassX * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 0
    grassCoords[0][1] = (grassY * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 0, 0
    grassCoords[1][0] = ((grassX + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 0
    grassCoords[1][1] = (grassY * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 1, 0
    grassCoords[2][0] = ((grassX + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 1
    grassCoords[2][1] = ((grassY + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 1, 1
    grassCoords[3][0] = (grassX * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 1
    grassCoords[3][1] = ((grassY + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 0, 1

    // vertices
    setTexCoord(&vertices[0],  dirtGrassCoords[3]);
    setTexCoord(&vertices[1],  dirtGrassCoords[2]);
    setTexCoord(&vertices[2],  dirtGrassCoords[1]);
    setTexCoord(&vertices[3],  dirtGrassCoords[3]);  // back
    setTexCoord(&vertices[4],  dirtGrassCoords[1]);
    setTexCoord(&vertices[5],  dirtGrassCoords[0]);

    setTexCoord(&vertices[6],  allDirtCoords[1]);
    setTexCoord(&vertices[7],  allDirtCoords[2]);
    setTexCoord(&vertices[8],  allDirtCoords[3]);  // bottom
    setTexCoord(&vertices[9],  allDirtCoords[1]);
    setTexCoord(&vertices[10], allDirtCoords[3]);
    setTexCoord(&vertices[11], allDirtCoords[0]);

    setTexCoord(&vertices[12], dirtGrassCoords[3]);
    setTexCoord(&vertices[13], dirtGrassCoords[0]);
    setTexCoord(&vertices[14], dirtGrassCoords[1]);  // right
    setTexCoord(&vertices[15], dirtGrassCoords[3]);
    setTexCoord(&vertices[16], dirtGrassCoords[1]);
    setTexCoord(&vertices[17], dirtGrassCoords[2]);

    setTexCoord(&vertices[18], dirtGrassCoords[0]);
    setTexCoord(&vertices[19], dirtGrassCoords[1]);
    setTexCoord(&vertices[20], dirtGrassCoords[2]);  // front
    setTexCoord(&vertices[21], dirtGrassCoords[0]);
    setTexCoord(&vertices[22], dirtGrassCoords[2]);
    setTexCoord(&vertices[23], dirtGrassCoords[3]);

    setTexCoord(&vertices[24], dirtGrassCoords[3]);
    setTexCoord(&vertices[25], dirtGrassCoords[0]);
    setTexCoord(&vertices[26], dirtGrassCoords[1]);  // left
    setTexCoord(&vertices[27], dirtGrassCoords[3]);
    setTexCoord(&vertices[28], dirtGrassCoords[1]);
    setTexCoord(&vertices[29], dirtGrassCoords[2]);

    setTexCoord(&vertices[30], grassCoords[1]);
    setTexCoord(&vertices[31], grassCoords[2]);
    setTexCoord(&vertices[32], grassCoords[3]);  // top
    setTexCoord(&vertices[33], grassCoords[1]);
    setTexCoord(&vertices[34], grassCoords[3]);
    setTexCoord(&vertices[35], grassCoords[0]);
}

static void generateTextureCoords(uint32_t type, Vertex* vertices) {
    vec2 coords[4];
    float x = 0.0f;
    float y = 0.0f;
    switch(type)
    {
        case BLOCK_DIRT:
            x = 1;
            y = 2;                       
        break;
        case BLOCK_STONE:
            x = 2;
            y = 1;
        break;
        case BLOCK_GRASS:
            x = 0;
            y = 2;
        break;
        case BLOCK_SAND:
            x = 1;
            y = 0;
        break;
        case BLOCK_WOOD_PLANK:
            x = 1;
            y = 1;
        break;
        case BLOCK_WOOD_OAK:
            x = 0;
            y = 1;
        break;
        case BLOCK_DIRT_GRASS:
            genDirtGrassBlock(vertices);
            return;
        break;
        case BLOCK_COBBLE_STONE:
            x = 0;
            y = 0;
        break;
        case BLOCK_GLASS:
            x = 2;
            y = 0;
        break;
        default:
            printf("no block");
    }
    coords[0][0] = (x * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 0
    coords[0][1] = (y * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 0, 0
    coords[1][0] = ((x + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 0
    coords[1][1] = (y * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;      // 1, 0
    coords[2][0] = ((x + 1) * BLOCK_TEX_SIZE) / ATLAS_WIDTH; // 1, 1
    coords[2][1] = ((y + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 1, 1
    coords[3][0] = (x * BLOCK_TEX_SIZE) / ATLAS_WIDTH;       // 0, 1
    coords[3][1] = ((y + 1) * BLOCK_TEX_SIZE) / ATLAS_HEIGHT;// 0, 1
    
    setTexCoord(&vertices[0],  coords[3]);
    setTexCoord(&vertices[1],  coords[2]);
    setTexCoord(&vertices[2],  coords[1]);
    setTexCoord(&vertices[3],  coords[3]);  // back
    setTexCoord(&vertices[4],  coords[1]);
    setTexCoord(&vertices[5],  coords[0]);

    setTexCoord(&vertices[6],  coords[1]);
    setTexCoord(&vertices[7],  coords[2]);
    setTexCoord(&vertices[8],  coords[3]);  // bottom
    setTexCoord(&vertices[9],  coords[1]);
    setTexCoord(&vertices[10], coords[3]);
    setTexCoord(&vertices[11], coords[0]);

    setTexCoord(&vertices[12], coords[3]);
    setTexCoord(&vertices[13], coords[0]);
    setTexCoord(&vertices[14], coords[1]);  // right
    setTexCoord(&vertices[15], coords[3]);
    setTexCoord(&vertices[16], coords[1]);
    setTexCoord(&vertices[17], coords[2]);

    setTexCoord(&vertices[18], coords[0]);
    setTexCoord(&vertices[19], coords[1]);
    setTexCoord(&vertices[20], coords[2]);  // front
    setTexCoord(&vertices[21], coords[0]);
    setTexCoord(&vertices[22], coords[2]);
    setTexCoord(&vertices[23], coords[3]);

    setTexCoord(&vertices[24], coords[3]);
    setTexCoord(&vertices[25], coords[0]);
    setTexCoord(&vertices[26], coords[1]);  // left
    setTexCoord(&vertices[27], coords[3]);
    setTexCoord(&vertices[28], coords[1]);
    setTexCoord(&vertices[29], coords[2]);

    setTexCoord(&vertices[30], coords[1]);
    setTexCoord(&vertices[31], coords[2]);
    setTexCoord(&vertices[32], coords[3]);  // top
    setTexCoord(&vertices[33], coords[1]);
    setTexCoord(&vertices[34], coords[3]);
    setTexCoord(&vertices[35], coords[0]);
}


Block* createBlock(uint32_t type)
{
    Block* block = (Block*)malloc(sizeof(Block) * 1);    
    block->type = type;

    float vertices[] = {
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 1
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2      // back  
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 3 

         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 0.0f, 0.0f, // 3
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 4      // bottom
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 2
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 4
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 5

         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 1.0f, // 1
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 1.0f, // 2
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 0.0f, // 5      // right
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 1.0f, // 1
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 0.0f, // 5
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 0.0f, // 6
 
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 4
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 5
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 6      // front
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 4
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 6
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 7
 
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 0.0f, 0.0f, // 3
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 4      // left
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 0.0f, 1.0f, // 0
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 1.0f, 0.0f, // 4
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 7
 
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 1.0f, // 0
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[2][0], coords[2][1], // 1.0f, 1.0f, // 1
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 0.0f, // 6      // top
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, // coords[1][0], coords[1][1], // 0.0f, 1.0f, // 0
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[3][0], coords[3][1], // 1.0f, 0.0f, // 6
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // coords[0][0], coords[0][1], // 1.0f, 1.0f, // 7        
    };
    generateTextureCoords(block->type, vertices);
    memcpy(block->vertices, vertices, sizeof(Vertex) * BLOCK_VERTEX_COUNT);
    return block;
}

void destroyBlocks(Block** blocks, size_t count) {
    for(int i = 0; i < count; i++) {
        free(blocks[i]);        
    }
}

void translateBlock(Block* block) {
    for(int i = 0; i < BLOCK_VERTEX_COUNT; i++) {
        block->vertices[i].position[0] += block->position[0];
        block->vertices[i].position[1] += block->position[1];
        block->vertices[i].position[2] += block->position[2];
    }
}