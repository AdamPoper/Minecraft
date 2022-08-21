#include "renderer.h"

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