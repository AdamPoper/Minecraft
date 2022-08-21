#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <glad/glad.h>
#include "stb_image/stb_image.h"

typedef struct {
    const char* textureFilePath;
    const char* openGLUniformId;
    uint8_t* textureBuffer;
    uint32_t texWidth, texHeight;
    uint32_t texId;
    uint32_t bpp;
} TextureAtlas;

void createTextureAtlas(TextureAtlas* atlas, const char* filepath);
void bindTextureAtlas(TextureAtlas* atlas);

#endif