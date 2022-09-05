#include "world.h"

World* initWorld() {
    World* world = (World*)malloc(sizeof(World) * 1);
    initWindow(&world->window, (vec2){WORLD_VIEW_WIDTH, WORLD_VIEW_HEIGHT}, "Minecraft!");
    initRenderer(&world->renderer, &world->window);
    world->window.setWindowBackGroundColor((vec4){0.3f, 0.5f, 0.9f, 1.0f});
    world->countChunks = VISIBLE_CHUNKS;
    genWorld(world);
    return world;
}

void genWorld(World* world) {
    for(int i = 0; i < VISIBLE_CHUNKS; i++) {
        initChunk(&world->chunks[i]);
    }
    vec3 chunkPos;
    vec3 blockPos;
    chunkPos[0] = 0.0f;
    chunkPos[1] = 0.0f;
    chunkPos[2] = 0.0f;
    uint32_t chunkIndex = 0;
    for(int x = 0; x < VISIBLE_CHUNKS / 2; x++) {        
        for(int z = 0; z < VISIBLE_CHUNKS / 2; z++) {
            memcpy(world->chunks[chunkIndex++].position, chunkPos, sizeof(float) * 3);
            chunkPos[2] += (float)CHUNK_LENGTH;
        }
        chunkPos[0] += (float)CHUNK_WIDTH;
        chunkPos[2] = 0.0f;
    }
    for(int c = 0; c < VISIBLE_CHUNKS; c++) {
        memcpy(blockPos, world->chunks[c].position, sizeof(float) * 3);
        uint32_t blockIndex = 0;
        for(int x = 0; x < CHUNK_WIDTH; x++) {
            blockPos[0] += 1.0f;
            for(int z = 0; z < CHUNK_LENGTH; z++) {
                blockPos[2] += 1.0f;
                for(int y = 0; y < CHUNK_HEIGHT; y++) {
                    blockPos[1] += 1.0f;
                    translateBlockByVectorTransform(&world->chunks[c].blocks[blockIndex], blockPos);
                    changeBlockType(&world->chunks[c].blocks[blockIndex], BLOCK_DIRT);
                    blockIndex++;
                }
                blockPos[1] = world->chunks[c].position[1];
            }
            blockPos[2] = world->chunks[c].position[2];
        }
        Block** blocksToRender;
        uint32_t numberOfBlocksToRender = 0;
        blocksToRender = (Block**)malloc(sizeof(Block*) * world->chunks[c].countBlocks);
        optimizeChunk(&world->chunks[c], blocksToRender, &numberOfBlocksToRender);
        for(int i = 0; i < numberOfBlocksToRender; i++) {
            rendererPushBlock(&world->renderer, blocksToRender[i]);
        }
        free(blocksToRender);
    }    
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