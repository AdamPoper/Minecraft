#include "world.h"

World* initWorld() {
    World* world = (World*)malloc(sizeof(World) * 1);
    initWindow(&world->window, (vec2){WORLD_VIEW_WIDTH, WORLD_VIEW_HEIGHT}, "Minecraft!");
    initRenderer(&world->renderer, &world->window);
    world->window.setWindowBackGroundColor((vec4){0.3f, 0.5f, 0.9f, 1.0f});
    genWorld(world);
    return world;
}

void genWorld(World* world) {
    world->countChunks = 1;
    Chunk* chunk = createChunks(world->countChunks);
    world->chunks = chunk;
    vec3 chunkPos;
    vec3 blockPos;
    chunkPos[0] = 0.0f;
    chunkPos[1] = 0.0f;
    chunkPos[2] = 0.0f;
    memcpy(blockPos, chunkPos, sizeof(float) * 3);
    uint32_t blockIndex = 0;
#if 1
    for(int x = 0; x < CHUNK_WIDTH; x++) {
        blockPos[0] += 1.0f;
        for(int z = 0; z < CHUNK_LENGTH; z++) {
            blockPos[2] += 1.0f;
            for(int y = 0; y < CHUNK_HEIGHT; y++) {
                blockPos[1] += 1.0f;
                translateBlockByVectorTransform(&world->chunks->blocks[blockIndex], blockPos);
                blockIndex++;
            }
            blockPos[1] = 0.0f;
        }
        blockPos[2] = 0.0f;
    }
    for(int i = 0; i < world->chunks->countBlocks; i++) {
        rendererPushBlock(&world->renderer, &world->chunks->blocks[i]);
    }
    destroyChunks(world->chunks, world->countChunks);
#endif
}

void onWorldUpdate(World* world) {    
    TimeStep ts; 
    FpsCounter fps;
    initFps(&fps);
    while(isWindowOpen(&world->window)) {
        updateFps(&fps);
        tsEnd(&ts);
        tsStart(&ts);
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