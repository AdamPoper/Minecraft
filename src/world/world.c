#include "world.h"

#define _calc_3d_index(_x, _y, _z, _width, _height) ((_z*_width+_x)+(_width*_height*_y))

void initWorld(World* world) {
    initWindow(&world->window, (vec2){WORLD_VIEW_WIDTH, WORLD_VIEW_HEIGHT}, "Minecraft!");
    initRenderer(&world->renderer, &world->window);
    
    world->window.setWindowBackGroundColor((vec4){0.3f, 0.5f, 0.9f, 1.0f});
    world->countChunks = VISIBLE_CHUNKS;

    uint32_t chunk_width_count = (uint32_t) sqrt((double) VISIBLE_CHUNKS),
    chunk_length_count = (uint32_t) sqrt((double) VISIBLE_CHUNKS);

    initNoise(&world->noise, (vec2){CHUNK_WIDTH * chunk_width_count, CHUNK_LENGTH * chunk_length_count});
    genWorld(world);
}

static void initChunkPositions(World* world, vec3 startChunkPos, uint32_t chunkCount, uint32_t chunkIndex) {
    vec3 chunkPos;
    memcpy(chunkPos, startChunkPos, sizeof(float) * 3);
    uint32_t chunks_xz = (uint32_t) sqrt((double)chunkCount);
    for(int x = 0; x < chunks_xz; x++) {
        for(int z = 0; z < chunks_xz; z++) {
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
    for (int i = 0; i < numberOfBlocksToRender; i++) {
        rendererPushBlock(&world->renderer, blocksToRender[i]);
    }
    free(blocksToRender);
}

static void initChunkBlockPositions(World* world, uint32_t chunkStartIndex, uint32_t chunkEndIndex) {
    vec3 blockPos;
    for (int c = chunkStartIndex; c < chunkEndIndex; c++) {
        memcpy(blockPos, world->chunks[c].position, sizeof(float) * 3);
        uint32_t blockIndex = 0;
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_LENGTH; z++) {
                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    translateBlockByVectorTransform(&world->chunks[c].blocks[blockIndex], blockPos);
                    blockIndex++;
                    blockPos[0] += 1.0f;
                }
                blockPos[2] += 1.0f;
                blockPos[0] = world->chunks[c].position[0];
            }
            blockPos[1] += 1.0f;
            blockPos[2] = world->chunks[c].position[2];
        }
    }
}

static void generateChunks(World* world) {
    vec3 chunkPos;
    chunkPos[0] = 0.0f;
    chunkPos[1] = 0.0f;
    chunkPos[2] = 0.0f;

    initChunkPositions(world, chunkPos, VISIBLE_CHUNKS, 0);
    initChunkBlockPositions(world, 0, VISIBLE_CHUNKS);    

    for (int i = 0; i < VISIBLE_CHUNKS; i++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int z = 0; z < CHUNK_LENGTH; z++) {
                Block* block = &world->chunks[i].blocks[
                    _calc_3d_index(x, 0, z, CHUNK_WIDTH, CHUNK_LENGTH)
                ];

                uint32_t noise_x = block->position[0];
                uint32_t noise_z = block->position[2];

                float raw_noise_value = getNoise(&world->noise, noise_x, noise_z);
                uint32_t noise_value = (uint32_t)((float) CHUNK_HEIGHT * raw_noise_value);

                for (int y = 0; y < noise_value; y++) {
                    uint32_t index = _calc_3d_index(x, y, z, CHUNK_WIDTH, CHUNK_LENGTH);
                    block = &world->chunks[i].blocks[index];

                    if (y < CHUNK_HEIGHT / 2) {
                        changeBlockType(block, BLOCK_STONE);
                    } else {
                        uint16_t block_type = BLOCK_DIRT;
                        if (y == noise_value - 1) {
                            block_type = BLOCK_DIRT_GRASS;
                        }

                        changeBlockType(block, block_type);
                    }
                }
            }
        }
    }

    for(int i = 0; i < VISIBLE_CHUNKS; i++) {
        optimizeWorldChunk(world, i);
    }
}

void genWorld(World* world) {
    for(int i = 0; i < VISIBLE_CHUNKS; i++) {
        initChunk(&world->chunks[i]);
    }
    generateChunks(world);
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
        // printf("FPS: %f\n", fps.fps);
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