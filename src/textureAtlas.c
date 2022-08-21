#include "textureAtlas.h"

void createTextureAtlas(TextureAtlas* atlas, const char* filepath) {
    atlas->textureFilePath = filepath;
    atlas->openGLUniformId = "u_texture";
    stbi_set_flip_vertically_on_load(1);
    atlas->textureBuffer = stbi_load(
        atlas->textureFilePath,
        &atlas->texWidth,
        &atlas->texHeight,
        &atlas->bpp,
        4
    );
    glGenTextures(1, &atlas->texId);
    glBindTexture(GL_TEXTURE_2D, atlas->texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
        atlas->texWidth, atlas->texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
        atlas->textureBuffer
    );
    glBindTexture(GL_TEXTURE_2D, 0);

    if(atlas->textureBuffer)
        stbi_image_free(atlas->textureBuffer);
}

void bindTextureAtlas(TextureAtlas* atlas) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, atlas->texId);
}