#ifndef WORLD_H
#define WORLD_H

#include "../renderer/renderer.h"
#include "../renderer/window.h"
#include "../util/fpsCounter.h"
#include "../util/perlinNoise.h"
#include "../util/timestep.h"
#include "chunk.h"

#define WORLD_VIEW_WIDTH 1920
#define WORLD_VIEW_HEIGHT 1080
#define VISIBLE_CHUNKS 36

typedef struct {
    Chunk chunks[VISIBLE_CHUNKS];
    Renderer renderer;
    Window window;
    uint32_t countChunks;
    PerlinNoise noise;
} World;

World* initWorld();
void genWorld(World* world);
void onWorldUpdate(World* world);
void onWorldEnd(World* world);

#endif