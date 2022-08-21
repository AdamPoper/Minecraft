#include "vertexArray.h"

void vaoBind(VertexArray* vao) {
    glBindVertexArray(vao->renderId);
}

VertexArray vaoCreate() {
    VertexArray vao = {
        .numAttribs = 0,
        .stride = 0,
        .counts = NULL
    };
    glGenVertexArrays(1, &vao.renderId);
    vaoBind(&vao);
    return vao;
}

void pushVertexAttrib(VertexArray* vao, uint32_t count) {
    uint32_t* newCounts = 
        (uint32_t*)malloc(sizeof(uint32_t) * vao->numAttribs+1);
    if(vao->numAttribs != 0) {
        for(int i = 0; i < vao->numAttribs; i++)
            newCounts[i] = vao->counts[i];            
        free(vao->counts);    
    }   
    newCounts[vao->numAttribs] = count;
    vao->counts = newCounts;
    vao->stride += sizeof(float) * count;
    vao->numAttribs++;
}

void enableAttribs(VertexArray vao) {
    uint32_t offset = 0;
    for(int i = 0; i < vao.numAttribs; i++)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, vao.counts[i], 
            GL_FLOAT, GL_FALSE, vao.stride, (const void*)offset);
        offset += sizeof(float) * vao.counts[i];
    }
}

void vaoDestroy(VertexArray* vao) {
    free(vao->counts);
}