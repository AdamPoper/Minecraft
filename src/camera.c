#include "camera.h"

void initCamera(Camera* cam, float w, float h)
{
    cam->fov        = radians(90.0f);
    cam->firstMouse = 1;
    cam->width      = w;
    cam->height     = h;
    cam->lastX      = w / 2.0f;
    cam->lastY      = h / 2.0f;
    cam->speed      = 3.0f;
    cam->yaw        = -90.0f;
    cam->pitch      = 0.0f;

    vec3 pos = {0.0f, 0.0f, 3.0f};
    vec3 target = {0.0f, 0.0f, 0.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    vec3 front = {0.0f, 0.0f, -1.0f};

    assignVec3(cam->position, pos);
    assignVec3(cam->target, target);
    assignVec3(cam->up, up);
    assignVec3(cam->front, front);

    glm_mat4_identity(cam->view);
    glm_mat4_identity(cam->projection);
}

void updateCamera(Camera* cam)
{
    vec3 posPlusFront;
    glm_vec3_add(cam->position, cam->front, posPlusFront);
    glm_lookat(cam->position, posPlusFront, cam->up, cam->view);
    glm_perspective(cam->fov, 
        cam->width / cam->height, 0.1f, 100.0f, cam->projection);
}

void moveCameraForward(Camera* cam, float ts)
{
    vec3 frontScale;
    float scaler = ts * cam->speed;
    glm_vec3_scale(cam->front, scaler, frontScale);
    glm_vec3_add(cam->position, frontScale, cam->position);
}

void moveCameraBackward(Camera* cam, float ts)
{
    vec3 frontScale;
    float scaler = ts * cam->speed;
    glm_vec3_scale(cam->front, scaler, frontScale);
    glm_vec3_sub(cam->position, frontScale, cam->position);
}

void strafeCameraRight(Camera* cam, float ts)
{
    float scaler = ts * cam->speed;
    vec3 crossed;
    glm_vec3_cross(cam->front, cam->up, crossed);
    glm_vec3_normalize(crossed);
    glm_vec3_scale(crossed, scaler, crossed);
    glm_vec3_add(cam->position, crossed, cam->position);    
}

void strafeCameraLeft(Camera* cam, float ts)
{
    float scaler = ts * cam->speed;
    vec3 crossed;
    glm_vec3_cross(cam->front, cam->up, crossed);
    glm_vec3_normalize(crossed);
    glm_vec3_scale(crossed, scaler, crossed);
    glm_vec3_sub(cam->position, crossed, cam->position);    
}

void moveCameraUp(Camera* cam, float ts)
{
    // float scaler = ts * cam->speed;
    // vec3 crossed;
    // glm_vec3_cross(cam->front, cam->up, crossed);
    // glm_vec3_normalize(crossed);
    // glm_vec3_scale(crossed, scaler, crossed);
    // // glm_vec3_add(cam->position, crossed, cam->position);
    // cam->position[1] += crossed[1];
}

void cameraMouseMove(Camera* cam, float xpos, float ypos)
{
    if(cam->firstMouse)
    {
        cam->lastX = xpos;
        cam->lastY = ypos; 
        cam->firstMouse = 0;
    }

    float xoffset = xpos - cam->lastX;
    float yoffset = cam->lastY - ypos;
    cam->lastX = xpos;
    cam->lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->yaw += xoffset;
    cam->pitch += yoffset;

    cam->pitch = cam->pitch > 89.0f ? 89.0f : cam->pitch;
    cam->pitch = cam->pitch < -89.0f ? -89.0f : cam->pitch;

    vec3 direction;
    direction[0] = cos(radians(cam->yaw)) * cos(radians(cam->pitch));
    direction[1] = sin(radians(cam->pitch));
    direction[2] = sin(radians(cam->yaw)) * cos(radians(cam->pitch));
    glm_vec3_normalize_to(direction, cam->front);
}