#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "world/world.h"
#include "util/perlinNoise.h"

int main() {
    World* world = (World*) malloc(sizeof(World) * 1);
    initWorld(world);
    onWorldUpdate(world);
    onWorldEnd(world);
}
