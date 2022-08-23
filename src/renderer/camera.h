#ifndef CAMERA_H
#define CAMERA_H

#include "cglm/cglm.h"
#include "cglm/affine-mat.h"
#include "cglm/vec3.h"
#include "cglm/types.h"
#include "cglm/cam.h"

#include <math.h>

#define PI 3.14159f
#define radians(d) (d*PI/180.0f)

#define assignVec3(dest, src) \
    dest[0] = src[0]; \
    dest[1] = src[1]; \
    dest[2] = src[2]; \

typedef struct 
{
    vec3 position;
    vec3 target;
    vec3 up;    
    vec3 direction;
    vec3 front;
    mat4 view;
    mat4 projection;
    float fov;
    float yaw;
    float pitch;
    int firstMouse;
    float lastX;
    float lastY;
    float speed;
    float width;
    float height;
} Camera;

void initCamera(Camera* cam, float w, float h);
void updateCamera(Camera* cam);
void moveCameraForward(Camera* cam, float ts);
void moveCameraBackward(Camera* cam, float ts);
void cameraMouseMove(Camera* cam, float x, float y);
void strafeCameraRight(Camera* cam, float ts);
void strafeCameraLeft(Camera* cam, float ts);
void moveCameraUp(Camera* cam, float ts);
#endif