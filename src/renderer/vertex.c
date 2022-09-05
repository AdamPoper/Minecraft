#include "vertex.h"

void printVertex(Vertex* v) {
    printf("Pos: (%f, %f, %f) TexCoord: (%f, %f)\n", 
        v->position[0],
        v->position[1],
        v->position[2],
        v->texCoord[0],
        v->texCoord[1]
    );
}