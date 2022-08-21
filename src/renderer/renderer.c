#include "renderer.h"

void initRenderer(Renderer* renderer, Window* window) {
    renderer->window = window;
    renderer->vao = vaoCreate();
    renderer->vbo = vboCreate();
    createTextureAtlas(&renderer->atlas, "res/textures/atlas.png");

    pushVertexAttrib(&renderer->vao, 3); // position
    pushVertexAttrib(&renderer->vao, 2); // tex coords
    enableAttribs(renderer->vao);

    Shader* vertexShader = createShader(GL_VERTEX_SHADER, "res/shaders/vertexShader.shader");
    Shader* fragmentShader = createShader(GL_FRAGMENT_SHADER, "res/shaders/fragmentShader.shader");
    renderer->shaderProgram = createShaderProgram(vertexShader, fragmentShader);
    shaderFree(vertexShader);
    shaderFree(fragmentShader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawRenderer(Renderer* renderer) {
    bindTextureAtlas(&renderer->atlas);
    setUniform1i(renderer->shaderProgram, renderer->atlas.openGLUniformId, 0);
    renderVertices(
        renderer->window,
        &renderer->vao,
        &renderer->vbo,
        renderer->shaderProgram
    );
}

void renderVertices(Window* window, VertexArray* vao, VertexBuffer* vbo, uint32_t shaderProgram) {
    int w, h;
    mat4 model;
    Camera* cam = &window->camera;
    glm_mat4_identity(model);
    glfwGetFramebufferSize(window->window, &w, &h);
    cam->height = (float)h;
    cam->width  = (float)w;
    updateCamera(&window->camera);
    setMatrix4fv(shaderProgram, "u_projection", cam->projection);
    setMatrix4fv(shaderProgram, "u_view", cam->view);
    glUseProgram(shaderProgram);
    glBindVertexArray(vao->renderId);
    glBindBuffer(vbo->type, vbo->renderID);
    glBufferData(vbo->type, sizeof(Vertex) * vbo->count, (const void*)vbo->data, GL_STATIC_DRAW); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    setMatrix4fv(shaderProgram, "u_model", model);
    glDrawArrays(GL_TRIANGLES, 0, vbo->count);
}

void rendererPushBlock(Renderer* renderer, Block* block) {
    vboPushBlock(&renderer->vbo, block);
}