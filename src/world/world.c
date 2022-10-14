#include "world.h"

uint32_t calc3dIndex(uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height) {    
    return ((z*width+x)+(width*height*y));
}

World* initWorld() {
    World* world = (World*)malloc(sizeof(World) * 1);
    initWindow(&world->window, (vec2){WORLD_VIEW_WIDTH, WORLD_VIEW_HEIGHT}, "Minecraft!");
    initRenderer(&world->renderer, &world->window);
    world->window.setWindowBackGroundColor((vec4){0.3f, 0.5f, 0.9f, 1.0f});
    world->countChunks = VISIBLE_CHUNKS;
    initNoise(&world->noise, (vec2){CHUNK_WIDTH * 2.0f, CHUNK_LENGTH * 2.0f});
    genWorld(world);
    return world;
}

static void initChunkPositions(World* world, vec3 startChunkPos, uint32_t chunkCount, uint32_t chunkIndex) {
    vec3 chunkPos;
    memcpy(chunkPos, startChunkPos, sizeof(float) * 3);
    for(int x = 0; x < chunkCount / 4; x++) {        
        for(int z = 0; z < chunkCount / 4; z++) {
            memcpy(world->chunks[chunkIndex++].position, chunkPos, sizeof(float) * 3);
            chunkPos[2] += (float)CHUNK_LENGTH;
        }
        chunkPos[0] += (float)CHUNK_WIDTH;
        chunkPos[2] = 0.0f;
    }
}

static void optimizeWorldChunk(World* world, uint32_t chunkIndex) {
    Block** blocksToRender;
    uint32_t numberOfBlocksToRender = 0;
    blocksToRender = (Block**)malloc(sizeof(Block*) * world->chunks[chunkIndex].countBlocks);
    optimizeChunk(&world->chunks[chunkIndex], blocksToRender, &numberOfBlocksToRender);
    for(int i = 0; i < numberOfBlocksToRender; i++) {
        rendererPushBlock(&world->renderer, blocksToRender[i]);
    }
    free(blocksToRender);
}

static void initChunkBlockPositions(World* world, uint32_t chunkStartIndex, uint32_t chunkEndIndex) {
    vec3 blockPos;
    for(int c = chunkStartIndex; c < chunkEndIndex; c++) {
        memcpy(blockPos, world->chunks[c].position, sizeof(float) * 3);
        uint32_t blockIndex = 0;
        for(int y = 0; y < CHUNK_WIDTH; y++) {
            blockPos[1] += 1.0f;
            for(int z = 0; z < CHUNK_LENGTH; z++) {
                blockPos[2] += 1.0f;
                for(int x = 0; x < CHUNK_HEIGHT; x++) {
                    blockPos[0] += 1.0f;
                    translateBlockByVectorTransform(&world->chunks[c].blocks[blockIndex], blockPos);
                    blockIndex++;
                }
                blockPos[0] = world->chunks[c].position[0];
            }
            blockPos[2] = world->chunks[c].position[2];
        }
    }
}

static void generateLevel2Chunks(World* world) {
    vec3 chunkPos;
    chunkPos[0] = 0.0f;
    chunkPos[1] = (float)CHUNK_HEIGHT;
    chunkPos[2] = 0.0f;
    uint32_t lvl2ChunkCount = VISIBLE_CHUNKS / 2;
    uint32_t chunkIndex = lvl2ChunkCount;
    PerlinNoise noise;
    initNoise(&noise, (vec2){(lvl2ChunkCount * CHUNK_LENGTH), (lvl2ChunkCount * CHUNK_WIDTH)});
    initChunkPositions(world, chunkPos, lvl2ChunkCount, chunkIndex);
    initChunkBlockPositions(world, lvl2ChunkCount, world->countChunks);
    uint32_t countChunks = world->countChunks;
    for(int c = lvl2ChunkCount; c < countChunks; c++) {
        for(int x = 0; x < CHUNK_WIDTH; x++) {
            for(int z = 0; z < CHUNK_LENGTH; z++) {
                Block* b = &world->chunks[c].blocks[
                    calc3dIndex(x, 0, z, CHUNK_WIDTH, CHUNK_LENGTH)
                ];
                float noiseX = b->position[0];
                float noiseY = b->position[2];
                float rawNoiseValue = getNoise(&noise, (uint32_t)noiseX, (uint32_t)noiseY);
                uint32_t noiseValue = (uint32_t)((float)CHUNK_HEIGHT * rawNoiseValue);
                for(int y = 0; y < noiseValue; y++) {
                    uint32_t blockType = BLOCK_DIRT;
                    if(y == noiseValue - 1) {
                        blockType = BLOCK_DIRT_GRASS;
                    }
                    changeBlockType(
                        &world->chunks[c].blocks[
                            calc3dIndex(x, y, z, CHUNK_WIDTH, CHUNK_HEIGHT)
                        ],
                        blockType
                    );
                }
            }
        }
    }
    for(int i = lvl2ChunkCount; i < world->countChunks; i++) {
        optimizeWorldChunk(world, i);
    }
}

static void generateLevel1Chunks(World* world) {
    vec3 chunkPos;
    chunkPos[0] = 0.0f;
    chunkPos[1] = 0.0f;
    chunkPos[2] = 0.0f;
    uint32_t lvl1ChunkCount = VISIBLE_CHUNKS / 2;
    uint32_t chunkIndex = 0;    
    initChunkPositions(world, chunkPos, lvl1ChunkCount, chunkIndex);
    initChunkBlockPositions(world, 0, lvl1ChunkCount);    
    for(int i = 0; i < lvl1ChunkCount; i++) {
        for(int j = 0; j < world->chunks[i].countBlocks; j++) {
            changeBlockType(&world->chunks[i].blocks[j], BLOCK_STONE);
        }
    }
    for(int i = 0; i < lvl1ChunkCount; i++) {
        optimizeWorldChunk(world, i);
    }
}

void generateTestChunk(World* world) {
    PerlinNoise noise;
    initNoise(&noise, (vec2){CHUNK_LENGTH, CHUNK_WIDTH});
    Chunk* chunk = &world->chunks[0];
    vec3 pos;
    pos[0] = 0.0f;
    pos[1] = 0.0f;
    pos[2] = 0.0f;
    initChunkPositions(world, pos, 1, 0);
    initChunkBlockPositions(world, 0, 1);
    uint32_t halfCount = CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT / 2;
    uint32_t halfHeight = CHUNK_HEIGHT / 2;
    uint32_t index = 0;
    for(int i = 0; i < halfCount; i++) {
        changeBlockType(&chunk->blocks[i], BLOCK_STONE);
        index++;
    }
    for(int x = 0; x < CHUNK_WIDTH; x++) {
        for(int z = 0; z < CHUNK_LENGTH; z++) {
            float rawNoise = getNoise(&noise, x, z);
            uint32_t noiseHeight = (uint32_t)((float)(CHUNK_HEIGHT) * rawNoise);        
            for(int y = halfHeight; y < halfHeight + noiseHeight; y++) {
                changeBlockType(
                    &chunk->blocks[calc3dIndex(x, y, z, CHUNK_WIDTH, CHUNK_HEIGHT)], 
                    BLOCK_DIRT
                );
                index++;
            }
        }
    }
    optimizeWorldChunk(world, 0);
}

void genWorld(World* world) {
    for(int i = 0; i < VISIBLE_CHUNKS; i++) {
        initChunk(&world->chunks[i]);
    }
    generateLevel1Chunks(world);
    generateLevel2Chunks(world);
    destroyChunks(world->chunks, world->countChunks);
}

void onWorldUpdate(World* world) {
    TimeStep ts; 
    FpsCounter fps;
    initFps(&fps);
    while(isWindowOpen(&world->window)) {
        updateFps(&fps);
        tsEnd(&ts);
        tsStart(&ts);
        printf("FPS: %f\n", fps.fps);
        if(isKeyPressed(&world->window, GLFW_KEY_W))
            moveCameraForward(&world->window.camera, ts.time);
        if(isKeyPressed(&world->window, GLFW_KEY_S))
            moveCameraBackward(&world->window.camera, ts.time);
        if(isKeyPressed(&world->window, GLFW_KEY_D))
            strafeCameraRight(&world->window.camera, ts.time);       
        if(isKeyPressed(&world->window, GLFW_KEY_A))
            strafeCameraLeft(&world->window.camera, ts.time);
        if(isKeyPressed(&world->window, GLFW_KEY_SPACE))
            moveCameraUp(&world->window.camera, ts.time);
        drawRenderer(&world->renderer);
        updateWindow(&world->window);
    }    
}

void onWorldEnd(World* world) {
    destroyRenderer(&world->renderer);
    destroyChunks(world->chunks, world->countChunks);
    free(world);
}