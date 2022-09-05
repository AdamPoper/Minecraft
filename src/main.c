#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "world/world.h"

int main() {
    World* world = initWorld();
    onWorldUpdate(world);
    onWorldEnd(world);  
}
