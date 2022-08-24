#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "renderer/window.h"
#include "renderer/renderer.h"
#include "util/timestep.h"
#include "util/fpsCounter.h"
#include "world/block.h"
#include "world/world.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int main() {
    World* world = initWorld();
    onWorldUpdate(world);
    onWorldEnd(world);  
}
