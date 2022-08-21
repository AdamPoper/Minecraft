#ifndef VERTEX_H
#define VERTEX_H

#include "cglm/cglm.h"
#include "cglm/vec2.h"
#include "cglm/vec3.h"
#include "cglm/types.h"

typedef struct {
    vec3 position;
    // vec4 color;
    vec2 texCoord;
} Vertex;


#endif