#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "renderer/window.h"
#include "renderer/renderer.h"
#include "util/timestep.h"
#include "util/fpsCounter.h"
#include "block.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int main() {
    Window window;
    initWindow(&window, (vec2){WINDOW_WIDTH, WINDOW_HEIGHT}, "Minecraft");
    window.setWindowBackGroundColor((vec4){0.3f, 0.5f, 0.9f, 1.0f});

    Renderer renderer;
    initRenderer(&renderer, &window);

    Block* block = createBlock(BLOCK_DIRT);

    rendererPushBlock(&renderer, block);

    TimeStep ts; 
    FpsCounter fps;
    initFps(&fps);
    while(isWindowOpen(&window)) {
        updateFps(&fps);
        tsEnd(&ts);
        tsStart(&ts);
        if(isKeyPressed(&window, GLFW_KEY_W))
            moveCameraForward(&window.camera, ts.time);
        if(isKeyPressed(&window, GLFW_KEY_S))
            moveCameraBackward(&window.camera, ts.time);
        if(isKeyPressed(&window, GLFW_KEY_D))
            strafeCameraRight(&window.camera, ts.time);       
        if(isKeyPressed(&window, GLFW_KEY_A))
            strafeCameraLeft(&window.camera, ts.time);
        if(isKeyPressed(&window, GLFW_KEY_SPACE))
            moveCameraUp(&window.camera, ts.time);
        drawRenderer(&renderer);
        updateWindow(&window);
    }    
}
