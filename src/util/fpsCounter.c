#include "fpsCounter.h"

void updateFps(FpsCounter* fps)
{
    double currentTime = glfwGetTime();
    fps->numFrames++;
    if(currentTime - fps->lastTime >= 1.0)
    {
        fps->fps = (double)fps->numFrames / (currentTime - fps->lastTime);
        fps->numFrames = 0;
        fps->lastTime += 1.0;
    }
}

void initFps(FpsCounter* fps)
{
    fps->numFrames = 0;
    fps->fps = 0.0;
    fps->lastTime = glfwGetTime();
}