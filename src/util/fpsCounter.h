#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <GLFW/glfw3.h>

typedef struct 
{
    uint32_t numFrames;
    double fps;
    double lastTime;
} FpsCounter;

void updateFps(FpsCounter* fps);
void initFps(FpsCounter* fps);
#endif