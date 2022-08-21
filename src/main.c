#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "renderer/window.h"
#include "renderer/shader.h"
#include "renderer/vertexArray.h"
#include "renderer/buffer.h"
#include "renderer/renderer.h"
#include "util/timestep.h"
#include "util/fpsCounter.h"
#include "block.h"
#include "stb_image/stb_image.h"
#include "textureAtlas.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int main() {
    Window window;
    initWindow(&window, (vec2){WINDOW_WIDTH, WINDOW_HEIGHT}, "Minecraft");
    window.setWindowBackGroundColor((vec4){0.3f, 0.5f, 0.9f, 1.0f});

    TextureAtlas textureAtlas;
    createTextureAtlas(&textureAtlas, "res/textures/atlas.png");

    Shader* vertexShader = createShader(GL_VERTEX_SHADER, "res/shaders/vertexShader.shader");
    Shader* fragmentShader = createShader(GL_FRAGMENT_SHADER, "res/shaders/fragmentShader.shader");
    uint32_t shaderProgram = createShaderProgram(vertexShader, fragmentShader);    
    shaderFree(vertexShader);
    shaderFree(fragmentShader);

    Block* block = createBlock(BLOCK_DIRT);

    VertexArray vao = vaoCreate();
    VertexBuffer vbo = vboCreate();
    pushVertexAttrib(&vao, 3); // position    
    pushVertexAttrib(&vao, 2); // tex coords
    enableAttribs(vao);    

    vboPushBlock(&vbo, block);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
        bindTextureAtlas(&textureAtlas);
        setUniform1i(shaderProgram, textureAtlas.openGLUniformId, 0);
        renderVertices(&window, &vao, &vbo, shaderProgram);
        updateWindow(&window);
    }    
}
