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
    Block* block = createBlock(BLOCK_DIRT);
    world->blocks = block;
    rendererPushBlock(&world->renderer, block);
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
    free(world->blocks);
    free(world->chunks);
    free(world);
}